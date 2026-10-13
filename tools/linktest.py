#!/usr/bin/env python3
"""Links one version by hand in a scratch directory, with chosen units compiled from source in place of the split
objects, and says whether the DOL still comes out identical. On a difference it names the symbols that differ.

Usage: linktest.py VERSION [--unit path/Unit ...] [--out DIR] [--cache DIR] [--obj DIR] [--lcf FILE]
                           [--ldflags "..."] [--extra FILE ...]

The object list, the linker and its flags are those of build.ninja, so run configure.py and a build first.
Nothing in config/ or configure.py is touched.
"""
import argparse
import bisect
import hashlib
import os
import re
import struct
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import compare  # noqa: E402

SCRATCH = ROOT / "build" / "linktest"
EXTENSIONS = (".cpp", ".c", ".cp")
# mwldeppc.exe can end in an access violation for no reason but the size of the environment it was started with.
# The same link passes with a variable more or less, so a link that ends this way is run again with one added.
LINKER_FAULT = 0xC0000005
PADDING = ("", "x" * 24, "x" * 40)


def source_of(unit: str) -> Optional[Path]:
    for extension in EXTENSIONS:
        path = ROOT / "src" / (unit + extension)
        if path.is_file():
            return path
    return None


def unit_name(text: str) -> str:
    """Takes src/a/B.cpp, a/B.cpp or a/B."""
    text = text.replace("\\", "/")
    if text.startswith("src/"):
        text = text[4:]
    for extension in EXTENSIONS:
        if text.endswith(extension):
            return text[: -len(extension)]
    return text


def ninja() -> Tuple[str, List[str], str, str]:
    """Returns the configured version, the link's objects, the linker and its flags."""
    text = (ROOT / "build.ninja").read_text(encoding="utf-8").replace("$\n", "")
    configured = re.search(r"^configure_args = .*--version (\w+)", text, re.M).group(1)
    objects = re.search(rf"^build build\\{configured}\\main\.elf: link (.*?) \|", text, re.M).group(1).split()
    linker = "build\\compilers\\" + re.search(r"^mw_version = (.+)$", text, re.M).group(1).strip() + "\\mwldeppc.exe"
    flags = re.search(r"^ldflags = (.+)$", text, re.M).group(1).strip()
    return configured, objects, linker, flags


def dol_sections(dol: bytes) -> List[Tuple[int, int, int]]:
    found = []
    for i in range(18):
        (offset,) = struct.unpack_from(">I", dol, i * 4)
        (address,) = struct.unpack_from(">I", dol, 0x48 + i * 4)
        (size,) = struct.unpack_from(">I", dol, 0x90 + i * 4)
        if size:
            found.append((address, offset, size))
    return sorted(found)


def differences(version: str, dol: Path) -> List[int]:
    """Returns the address of every word of a DOL that differs from the original, in address order."""
    a = (ROOT / "orig" / version / "sys" / "main.dol").read_bytes()
    b = dol.read_bytes()
    found = []
    for address, offset, size in dol_sections(a):
        for at in range(offset, min(offset + size, len(b)), 4):
            if a[at : at + 4] != b[at : at + 4]:
                found.append(address + at - offset)
    return found


def unit_ranges(version: str) -> List[Tuple[int, int, str, str]]:
    """Returns (start, end, section, unit) for every range in splits.txt, by address."""
    found = []
    unit = None
    for line in (ROOT / "config" / version / "splits.txt").read_text(encoding="utf-8").splitlines():
        if line and not line[0].isspace() and line.endswith(":"):
            unit = line[:-1]
        elif unit:
            m = re.match(r"\s+(\S+)\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
            if m:
                found.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1), unit))
    return sorted(found)


def describe(version: str, addresses: List[int], limit: int = 20) -> List[str]:
    """Names the symbols and units that hold the given addresses."""
    ranges = unit_ranges(version)
    symbols = []
    text = (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8")
    for m in re.finditer(r"^(\S+) = \.\w+:0x([0-9A-F]+);", text, re.M):
        symbols.append((int(m.group(2), 16), m.group(1)))
    symbols.sort()
    starts = [s[0] for s in symbols]
    lines: List[str] = []
    last = None
    for address in addresses:
        i = bisect.bisect_right(starts, address) - 1
        name = symbols[i][1] if i >= 0 else "?"
        if name != last:
            if len(lines) == limit:
                lines.append("...")
                break
            unit = next((r[3] for r in ranges if r[0] <= address < r[1]), "?")
            lines.append(f"0x{address:08X} {name}+0x{address - symbols[i][0]:X} in {unit}")
        last = name
    return lines


MAP_LINE = re.compile(r"^  [0-9a-f]{8} ([0-9a-f]{6}) ([0-9a-f]{8}) [0-9a-f]{8} +\d+ (\S+) \t(.*)$")


def map_symbols(path: Path) -> List[Tuple[int, int, str, str]]:
    """Returns (address, size, name, object) for every symbol a link map places, in address order."""
    found = []
    with open(path, encoding="utf-8", errors="replace") as map_file:
        for line in map_file:
            m = MAP_LINE.match(line)
            if m and not m.group(3).startswith("."):
                found.append((int(m.group(2), 16), int(m.group(1), 16), m.group(3), m.group(4).split("\\")[-1].strip()))
    return sorted(set(found))


def first_shift(version: str, scratch_map: Path, limit: int = 6) -> List[str]:
    """Names the first symbols a scratch link placed elsewhere than the original link did."""
    original = map_symbols(ROOT / "orig" / version / "files" / "iuk.MAP")
    scratch = map_symbols(scratch_map)
    count: Dict[str, int] = {}
    for _, _, name, _ in original + scratch:
        count[name] = count.get(name, 0) + 1
    # A numbered name (@1234) means something else in every object, so only names both maps hold once can be compared.
    where = {name: address for address, _, name, _ in original if count[name] == 2 and not re.fullmatch(r"@\d+", name)}
    lines: List[str] = []
    previous = None
    shift = 0
    for address, size, name, obj in scratch:
        if name in where and where[name] - address != shift:
            shift = where[name] - address
            before = f", after {previous[2]} (size 0x{previous[1]:X}, {previous[3]})" if previous else ""
            lines.append(f"0x{address:08X} {name} ({obj}) is at 0x{where[name]:08X} in the original{before}")
            if len(lines) == limit:
                break
        previous = (address, size, name, obj)
    return lines


FOLD_LINE = re.compile(r"^--> (?:duplicated code: symbol (\S+) is duplicated by (\S+),|the function (\S+) will be replaced by a branch to (\S+))")


def folds(path: Path) -> Dict[str, str]:
    """Returns the look-alike each folded function of a link map was folded into."""
    found: Dict[str, str] = {}
    with open(path, encoding="utf-8", errors="replace") as map_file:
        for line in map_file:
            m = FOLD_LINE.match(line)
            if m:
                found[m.group(1) or m.group(3)] = m.group(2) or m.group(4)
    return found


def fold_differences(version: str, scratch_map: Path, units: List[str], limit: int = 12) -> List[str]:
    """Names the functions of the compiled units that a scratch link folded otherwise than the original link did."""
    original = folds(ROOT / "orig" / version / "files" / "iuk.MAP")
    scratch = folds(scratch_map)
    # The split objects no longer hold what the original folded away, so only the compiled units can be compared.
    compiled = {unit.replace("/", "_") + ".o" for unit in units}
    placed = {name for _, _, name, obj in map_symbols(scratch_map) if obj in compiled}
    lines: List[str] = []
    for name in sorted(set(scratch) | (placed & set(original)), key=lambda n: (n not in placed, n)):
        was, now = original.get(name), scratch.get(name)
        if was == now or now == name:
            continue
        if was is None:
            lines.append(f"{name}: folded into {now} here, kept whole by the original")
        elif now is None:
            lines.append(f"{name}: kept whole here, folded into {was} by the original")
        else:
            lines.append(f"{name}: folded into {now} here, into {was} by the original")
    return lines[:limit] + ([f"... and {len(lines) - limit} more"] if len(lines) > limit else [])


def link(
    version: str,
    units: List[str],
    out: Path,
    cache: Optional[Path] = None,
    obj: Optional[Path] = None,
    lcf: Optional[str] = None,
    ldflags: str = "",
    extra: Tuple[str, ...] = (),
    cflags: str = "",
) -> Tuple[bool, str, List[int]]:
    """Links into `out`. Returns whether the DOL is identical, the tools' output, and the differing addresses."""
    out = out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    configured, objects, linker, flags = ninja()
    if configured != version:
        # The versions do not have the same units, so one's object list does not serve the other.
        return False, f"build.ninja is configured for {configured}: run configure.py --version {version} and build first", []
    for unit in units:
        source = source_of(unit)
        if source is None:
            return False, f"{unit}: no source", []
        compiled = (cache or out) / (unit.replace("/", "_") + ".o")
        compiled.parent.mkdir(parents=True, exist_ok=True)
        if not (cache and compiled.is_file()):
            error = compare.build(version, source, cflags, compiled, unit)
            if error:
                return False, f"{unit}: does not compile\n{error}", []
        split = f"build\\{version}\\obj\\" + unit.replace("/", "\\") + ".o"
        built = f"build\\{version}\\src\\" + unit.replace("/", "\\") + ".o"
        wanted = split if split in objects else built
        if wanted not in objects:
            return False, f"{unit} is not in the link", []
        objects[objects.index(wanted)] = str(compiled)
    if obj:
        prefix = f"build\\{version}\\obj\\"
        objects = [str(obj.resolve() / o[len(prefix) :]) if o.startswith(prefix) else o for o in objects]
    objects += list(extra)
    missing = [o for o in objects if not (ROOT / o).is_file()]
    if missing:
        return False, f"{len(missing)} objects are missing, build {version} first: {missing[0]}", []
    rsp = out / "main.rsp"
    rsp.write_text("\n".join(objects) + "\n", encoding="utf-8")
    elf, dol = out / "main.elf", out / "main.dol"
    script = lcf or f"build\\{version}\\ldscript.lcf"
    command = f'{linker} {flags} {ldflags} -lcf "{script}" -o "{elf}" @"{rsp}"'
    for padding in PADDING:
        env = dict(os.environ, MWLD_PADDING=padding) if padding else None
        result = subprocess.run(command, capture_output=True, text=True, cwd=ROOT, env=env)
        if result.returncode != LINKER_FAULT:
            break
    text = (result.stdout + result.stderr).strip()
    if result.returncode:
        return False, text + "\nlink failed", []
    subprocess.run([str(ROOT / "build" / "tools" / "dtk.exe"), "elf2dol", str(elf), str(dol)], check=True)
    original = ROOT / "orig" / version / "sys" / "main.dol"
    if hashlib.sha1(dol.read_bytes()).digest() == hashlib.sha1(original.read_bytes()).digest():
        return True, text, []
    return False, text, differences(version, dol)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("version")
    parser.add_argument("--unit", "-u", action="append", default=[], help="unit to compile from source (src/a/B.cpp or a/B)")
    parser.add_argument("--out", type=Path, help="scratch directory (default: build/linktest/VERSION)")
    parser.add_argument("--cache", type=Path, help="directory of compiled objects to reuse")
    parser.add_argument("--obj", type=Path, help="take the split objects from this directory")
    parser.add_argument("--lcf", help="linker script (default: build/VERSION/ldscript.lcf)")
    parser.add_argument("--ldflags", default="", help="further linker flags")
    parser.add_argument("--extra", action="append", default=[], help="further object to link")
    parser.add_argument("--flags", default="", help='further compiler flags for the units, as --flags=" -common on"')
    parser.add_argument("--map", action="store_true", help="on a difference, compare the link map with the original's")
    args = parser.parse_args()
    units = [unit_name(u) for u in args.unit]
    out = args.out or SCRATCH / args.version
    scratch_map = out.resolve() / "main.map"
    flags = args.ldflags + (f' -map "{scratch_map}"' if args.map else "")
    same, text, addresses = link(
        args.version, units, out, args.cache, args.obj, args.lcf, flags, tuple(args.extra), args.flags
    )
    # A source's copy of a function the linker script names is dropped with a warning: expected (docs/code_merging.md).
    blocks = re.split(r"(?=^### )", text, flags=re.M)
    expected = "also defined as a linker generated symbol"
    shown = "".join(b for b in blocks if expected not in re.sub(r"\s*\n#\s*", " ", b)).strip()
    if shown:
        print("\n".join(shown.splitlines()[:60]))
    if same:
        print("identical")
        return
    if addresses:
        print(f"DIFFERENT: {len(addresses)} words, first at 0x{addresses[0]:08X}")
        print("\n".join(describe(args.version, addresses)))
        if args.map:
            print("first symbols placed elsewhere:")
            print("\n".join(first_shift(args.version, scratch_map)) or "none: the layout is the original's")
            print("functions folded otherwise than in the original:")
            print("\n".join(fold_differences(args.version, scratch_map, units)) or "none")
    sys.exit(1)


if __name__ == "__main__":
    main()
