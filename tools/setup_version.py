#!/usr/bin/env python3

###
# Generates config/<VERSION> for a version of the game from its DOL and link map.
#
# Every retail disc carries the link map of its own build (files/iuk.MAP), so
# each version gets its symbols and splits first hand instead of having them
# ported from another version. This script runs the whole procedure:
#
# 1. Clean the link map and give every translation unit a unique name
#    (tools/prepare_map.py).
# 2. Locate MetaFortress inline data, which decomp-toolkit must not treat as
#    instructions (tools/metafortress.py).
# 3. Let decomp-toolkit import the map and write symbols.txt and splits.txt.
# 4. Apply the corrections the import cannot make on its own (see below).
# 5. Write config.yml and build.sha1.
#
# Usage:
#   python tools/setup_version.py SUKE01
#
# Expects orig/<VERSION>/sys/main.dol and orig/<VERSION>/files/iuk.MAP, and
# decomp-toolkit in build/tools (run `python configure.py && ninja` for any
# existing version, or pass --dtk). Existing files in config/<VERSION> are
# overwritten. See docs/map.md.
###

import argparse
import hashlib
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

import metafortress
import prepare_map

MW_COMMENT_VERSION = 15
LDSCRIPT_TEMPLATE = "config/ldscript.lcf"

SYMBOL_RE = re.compile(r"^(\S+) = (\S+):0x([0-9A-F]{8}); // (.*)$")


def run_dtk(dtk: Path, config: Path, out_dir: Path) -> None:
    result = subprocess.run(
        [str(dtk), "dol", "split", str(config), str(out_dir)],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.returncode != 0:
        sys.stdout.write(result.stdout)
        sys.exit(f"decomp-toolkit failed on {config}")


def write_config(
    path: Path,
    version: str,
    dol_hash: str,
    symbols: Path,
    splits: Path,
    blobs: List[Tuple[int, int]],
    map_path: Optional[Path] = None,
) -> None:
    force_active: List[str] = []
    if symbols.is_file():
        names = re.findall(rf"^({metafortress.RESPONSE}\S*) = ", symbols.read_text(encoding="utf-8"), re.M)
        force_active = sorted(set(names))
    lines = [
        "# See config/config.example.yml for documentation.",
        f"object_base: orig/{version}",
        "object: sys/main.dol",
        f"hash: {dol_hash}",
        f"symbols: {symbols.as_posix()}",
        f"splits: {splits.as_posix()}",
    ]
    if map_path is not None:
        lines.append(f"map: {map_path.as_posix()}")
    lines += [
        f"mw_comment_version: {MW_COMMENT_VERSION}",
        "# Every function and its size is known from the link map. decomp-toolkit's own",
        "# search for function boundaries has nothing to add, and it trips over",
        "# MetaFortress data that happens to decode as a branch.",
        "quick_analysis: true",
        "# The stock linker script lacks the game's stack guard region.",
        f"ldscript_template: {LDSCRIPT_TEMPLATE}",
        "",
    ]
    if force_active:
        lines += [
            "# The MetaFortress response is reached through computed jumps only, and its",
            "# pointer object is never read. Without this the linker drops both.",
            "force_active:",
            *(f"- {name}" for name in force_active),
            "",
        ]
    lines += [
        "# MetaFortress inline data. These words sit in the middle of protected",
        "# functions and are not instructions, so nothing in them is a relocation.",
        f"# Generated with `python tools/metafortress.py {version} --yaml`.",
        "block_relocations:",
    ]
    for start, end in blobs:
        lines.append(f"- source: .text:0x{start:08X}")
        lines.append(f"  end: .text:0x{end:08X}")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


###
# Corrections to splits.txt
###


def fix_splits(path: Path, symbols_path: Path) -> None:
    lines = path.read_text(encoding="utf-8").split("\n")

    # Section alignment. decomp-toolkit guesses the smallest alignment that
    # reproduces each section's address. The layout actually follows 32 bytes
    # throughout, raised by any symbol that asks for more (.bss holds one that
    # is aligned to 128).
    max_align: Dict[str, int] = {}
    for line in symbols_path.read_text(encoding="utf-8").split("\n"):
        m = SYMBOL_RE.match(line)
        if m:
            a = re.search(r"\balign:(\d+)", m.group(4))
            if a:
                max_align[m.group(2)] = max(max_align.get(m.group(2), 0), int(a.group(1)))
    assert lines[0] == "Sections:", lines[0]
    i = 1
    while lines[i].startswith("\t"):
        m = re.match(r"^(\t(\S+)\s+type:\S+) align:\d+$", lines[i])
        assert m, lines[i]
        if m.group(2) != ".init":
            lines[i] = f"{m.group(1)} align:{max(32, max_align.get(m.group(2), 0))}"
        i += 1

    # __init_cpp_exceptions.cpp places its entries in named subsections of
    # .ctors and .dtors, which the linker sorts ahead of everything else.
    renames = {".ctors": [".ctors$10"], ".dtors": [".dtors$10", ".dtors$15"]}
    start = lines.index("Runtime/__init_cpp_exceptions.cpp:")
    i = start + 1
    while lines[i].startswith("\t"):
        section = lines[i].split()[0]
        if section in renames:
            assert "rename:" not in lines[i], lines[i]
            lines[i] += f" rename:{renames[section].pop(0)}"
        i += 1
    assert not any(renames.values()), renames
    path.write_text("\n".join(lines), encoding="utf-8", newline="\n")


###
# Corrections to symbols.txt
###


# MetroTRK's file access stubs are hand-written assembly. The map lists them as
# sizeless entry points of their object's .text, one after the other.
ASSEMBLY_STUBS = ("TRKAccessFile", "TRKOpenFile", "TRKCloseFile", "TRKPositionFile")


# The runtime's register save and restore routines have an entry point per
# register (r14/f14 to r31/f31, four bytes apart). The map only lists the ones
# the game happens to use; compiled code may call any of them.
REGISTER_SLEDS = {
    "__save_fpr": "_savefpr_",
    "__restore_fpr": "_restfpr_",
    "__save_gpr": "_savegpr_",
    "__restore_gpr": "_restgpr_",
}


def fix_symbols(path: Path) -> None:
    lines: List[str] = []
    for line in path.read_text(encoding="utf-8").split("\n"):
        m = SYMBOL_RE.match(line)
        if m and m.group(1).startswith(tuple(REGISTER_SLEDS.values())):
            continue  # re-added in full below
        lines.append(line)
        if m and m.group(1) in REGISTER_SLEDS and "type:function" in m.group(4):
            base = int(m.group(3), 16)
            for reg in range(14, 32):
                address = base + (reg - 14) * 4
                lines.append(f"{REGISTER_SLEDS[m.group(1)]}{reg} = {m.group(2)}:0x{address:08X}; // type:label scope:global")

    parsed = [SYMBOL_RE.match(line) for line in lines]
    for i, m in enumerate(parsed):
        if not m:
            continue
        name, section, address, attrs = m.groups()
        if name in ASSEMBLY_STUBS:
            # Turn the label into a function that runs up to the next symbol
            assert attrs == "type:label scope:global", lines[i]
            following = parsed[i + 1]
            assert following and following.group(2) == section, lines[i + 1]
            size = int(following.group(3), 16) - int(address, 16)
            assert 0 < size <= 0x20, lines[i]
            lines[i] = f"{name} = {section}:0x{address}; // type:function size:0x{size:X} scope:global"
        elif name.startswith("dcpl_") and "_mfort" in name and "noreloc" not in attrs.split():
            # MetaFortress constants are opaque; nothing in them is a pointer.
            lines[i] += " noreloc"
    path.write_text("\n".join(lines), encoding="utf-8", newline="\n")


ASM_HEADER_RE = re.compile(r"^# (\S+):0x[0-9A-Fa-f]+ \| 0x([0-9A-Fa-f]+) \| size: 0x[0-9A-Fa-f]+")
ASM_SYMBOL_RE = re.compile(r'^\.(?:obj|fn|sym) ("[^"]+"|\S+?),\s*(\w+)')
ASM_POINTER_RE = re.compile(r'^\t\.4byte\s+("[^"]+"|[^\s+]+)\+0x[0-9A-Fa-f]+\s*$')


def find_false_pointers(asm_dir: Path) -> Set[Tuple[str, int]]:
    """
    Finds data symbols that decomp-toolkit took for pointers but are not.

    Any data word that happens to hold the address of something becomes a
    relocation. Real pointers go to the start of a symbol or stay within their
    own translation unit; a word that lands in the middle of another unit's
    symbol is a number that merely looks like an address (codec tables, bit
    masks, floating point constants). The one legitimate exception in this game
    are jump tables left behind by duplicate template instantiations, which
    point into the copy of the function that survived in another unit.

    Returns the (section, address) of each offending symbol.
    """
    files = sorted(asm_dir.rglob("*.s"))
    texts: Dict[Path, List[str]] = {}
    exported: Dict[str, Tuple[str, str]] = {}  # name -> (unit, section)
    for path in files:
        unit = path.relative_to(asm_dir).as_posix()
        lines = path.read_text(encoding="utf-8", errors="replace").split("\n")
        texts[path] = lines
        section = None
        for line in lines:
            m = ASM_HEADER_RE.match(line)
            if m:
                section = m.group(1)
                continue
            m = ASM_SYMBOL_RE.match(line)
            if m and section is not None and m.group(2) != "local":
                exported[m.group(1).strip('"')] = (unit, section)

    result: Set[Tuple[str, int]] = set()
    for path in files:
        unit = path.relative_to(asm_dir).as_posix()
        lines = texts[path]
        own = set()
        for line in lines:
            m = ASM_SYMBOL_RE.match(line)
            if m:
                own.add(m.group(1).strip('"'))
        section = None
        address = 0
        for line in lines:
            m = ASM_HEADER_RE.match(line)
            if m:
                section, address = m.group(1), int(m.group(2), 16)
                continue
            if section in (None, ".text", ".init"):
                continue
            m = ASM_POINTER_RE.match(line)
            if not m:
                continue
            target = m.group(1).strip('"')
            if target in own or target not in exported:
                continue
            target_unit, target_section = exported[target]
            jump_table = (
                section == ".data"
                and target_section == ".text"
                and not prepare_map.is_library_unit(unit)
                and not prepare_map.is_library_unit(target_unit)
            )
            if not jump_table:
                result.add((section, address))
    return result


def mark_noreloc(path: Path, symbols: Set[Tuple[str, int]]) -> int:
    lines = path.read_text(encoding="utf-8").split("\n")
    remaining = set(symbols)
    marked = 0
    for i, line in enumerate(lines):
        m = SYMBOL_RE.match(line)
        if not m:
            continue
        key = (m.group(2), int(m.group(3), 16))
        attrs = m.group(4).split()
        if key in remaining and "type:object" in attrs:
            remaining.discard(key)
            if "noreloc" not in attrs:
                lines[i] = line + " noreloc"
                marked += 1
    if remaining:
        sys.exit("No symbol found for: " + ", ".join(f"{s}:0x{a:08X}" for s, a in sorted(remaining)))
    path.write_text("\n".join(lines), encoding="utf-8", newline="\n")
    return marked


def main() -> None:
    parser = argparse.ArgumentParser(description="Generates config/<VERSION> from a DOL and its link map.")
    parser.add_argument("version", type=str.upper, help="game ID, e.g. SUKE01")
    parser.add_argument("--dtk", type=Path, help="path to the decomp-toolkit binary (default: build/tools)")
    parser.add_argument("--output", type=Path, help="write the result here instead of config/<VERSION>")
    args = parser.parse_args()

    version: str = args.version
    dol_path = Path("orig") / version / "sys" / "main.dol"
    map_path = Path("orig") / version / "files" / "iuk.MAP"
    for path in (dol_path, map_path, Path(LDSCRIPT_TEMPLATE)):
        if not path.is_file():
            sys.exit(f"{path} not found (run this from the project root)")
    dtk = args.dtk or Path("build") / "tools" / ("dtk.exe" if sys.platform == "win32" else "dtk")
    if not dtk.is_file():
        sys.exit(f"{dtk} not found. Build any existing version once to download it, or pass --dtk.")

    config_dir = Path("config") / version
    work = Path("build") / version / "setup"
    if work.exists():
        shutil.rmtree(work)
    work.mkdir(parents=True)
    symbols = work / "symbols.txt"
    splits = work / "splits.txt"
    config = work / "config.yml"

    dol_data = dol_path.read_bytes()
    dol_hash = hashlib.sha1(dol_data).hexdigest()
    blobs = metafortress.find_inline_data(dol_data)

    print(f"[1/4] Preparing {map_path}")
    clean_map = Path("build") / version / "iuk.clean.MAP"
    prepare_map.prepare(map_path, dol_path, clean_map, Path("build") / version / "units.txt")

    print("[2/4] Importing the map with decomp-toolkit")
    write_config(config, version, dol_hash, symbols, splits, blobs, map_path=clean_map)
    run_dtk(dtk, config, work / "out")
    fix_splits(splits, symbols)
    fix_symbols(symbols)
    blobs = sorted(metafortress.Analysis(dol_data, symbols).inline)

    print("[3/4] Looking for numbers mistaken for pointers")
    write_config(config, version, dol_hash, symbols, splits, blobs)
    run_dtk(dtk, config, work / "out")
    marked = mark_noreloc(symbols, find_false_pointers(work / "out" / "asm"))
    run_dtk(dtk, config, work / "out")
    left = find_false_pointers(work / "out" / "asm")
    if left:
        sys.exit("Still mistaken for pointers: " + ", ".join(f"{s}:0x{a:08X}" for s, a in sorted(left)))
    print(f"{marked} symbols marked noreloc, on top of the MetaFortress constants")

    print("[4/4] Writing the configuration")
    out_dir: Path = args.output or config_dir
    out_dir.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(symbols, out_dir / "symbols.txt")
    shutil.copyfile(splits, out_dir / "splits.txt")
    write_config(out_dir / "config.yml", version, dol_hash, config_dir / "symbols.txt", config_dir / "splits.txt", blobs)
    (out_dir / "build.sha1").write_text(f"{dol_hash}  build/{version}/main.dol\n", encoding="utf-8", newline="\n")
    shutil.rmtree(work)
    print(f"Wrote {out_dir}")
    if args.output is None:
        print(f"Add {version} to VERSIONS in configure.py if it is new, then:")
        print(f"  python configure.py --version {version} && ninja")


if __name__ == "__main__":
    main()
