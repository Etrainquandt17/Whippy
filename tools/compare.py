#!/usr/bin/env python3
"""Compiles one source file and compares its functions and data with the original object.

    python tools/compare.py SUKE01 src/storage/ArenaGameData.cpp
    python tools/compare.py all src/storage/ArenaGameData.cpp -f isCleared
    python tools/compare.py SUKE01 src/info/common/WiiButton.cpp -p "WiiButton::hold"
    python tools/compare.py all src

Needs a configured and built tree (python configure.py && ninja), because the
original objects and the compiler flags are taken from it. It does not touch the
build: the source is compiled to a temporary file.
"""

import argparse
import itertools
import json
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, NamedTuple, Optional, Set, Tuple

ROOT = Path(__file__).resolve().parent.parent
REFERENCE = "src/storage/ArenaGameData.cpp"
OBJDUMP = ROOT / "build" / "binutils" / "powerpc-eabi-objdump.exe"

R_PPC_ADDR32, R_PPC_REL24, R_PPC_REL14, R_PPC_EMB_SDA21 = 1, 10, 11, 109
MASKS = {R_PPC_ADDR32: 0, R_PPC_REL24: 0xFC000003, R_PPC_REL14: 0xFFFF0003, R_PPC_EMB_SDA21: 0xFFE00000}


LOST = "(small data)"
UNNAMED = re.compile(r"(\d+)(@unnamed@\w+?)_prt_cpp@")


LOCAL_CLASS = re.compile(r"\$(\d+)(\w+?)(?:_prt)?_cpp")


def lowest_serial(names) -> int:
    """Returns the lowest serial number among the local classes named in an object's symbols."""
    serials = [int(m.group(1)) for name in names for m in LOCAL_CLASS.finditer(name)]
    return min(serials) if serials else 0


def plain(name: str, base: int = 0) -> str:
    """Returns a symbol name without what differs between the original's compilation and ours.

    MetaFortress compiled its rewritten copy of a file, X_prt.cpp, and the file
    name is part of every symbol in an unnamed namespace. A class local to a
    function is named Class$<serial><File>_cpp, with a serial number that
    depends on everything the compiler saw before it; only its distance from
    the object's lowest serial is kept, which still tells overloads apart.
    """
    name = UNNAMED.sub(lambda m: f"{int(m.group(1)) - 4}{m.group(2)}_cpp@", name)
    if name.startswith("__sinit_") and name.endswith("_prt_cpp"):
        name = name[: -len("_prt_cpp")] + "_cpp"
    at = 0
    while True:
        m = LOCAL_CLASS.search(name, at)
        if not m:
            return name
        at = m.end()
        replaced = False
        for start in range(m.start() - 1, 0, -1):
            if name[start].isdigit() or not name[start - 1].isdigit():
                continue
            run = re.search(r"\d+$", name[:start])
            for skip in range(len(run.group())):
                if int(run.group()[skip:]) == m.end() - start:
                    replacement = f"{name[start : m.start()]}${int(m.group(1)) - base}{m.group(2)}_cpp"
                    name = name[: run.start() + skip] + replacement + name[m.end() :]
                    at = run.start() + skip + len(replacement)
                    replaced = True
                    break
            if replaced:
                break


class Function(NamedTuple):
    code: bytes
    targets: Tuple[Tuple[int, str], ...]
    section: str = ""


class Link(dict):
    """The folded functions of a version, and the names the original link kept anywhere or dropped as unused."""

    kept: Set[str] = set()
    unused: Set[str] = set()
    # Functions the original link replaced by a branch to a look-alike, with their size before that.
    branches: Dict[str, int] = {}


def merged(version: str) -> Dict[str, str]:
    """Returns, for each function the original link folded into a look-alike, one name for the whole group.

    A call to a folded function goes to whichever copy survived, so the original
    object names that one. See docs/code_merging.md.
    """
    group: Dict[str, str] = {}
    unused: Set[str] = set()
    sizes: Dict[str, int] = {}
    branches: Dict[str, int] = {}

    def find(name: str) -> str:
        while group.setdefault(name, name) != name:
            group[name] = group[group[name]]
            name = group[name]
        return name

    path = ROOT / "orig" / version / "files" / "iuk.MAP"
    if path.is_file():
        with open(path, encoding="utf-8", errors="replace") as map_file:
            for line in map_file:
                if line.startswith("--> duplicated code"):
                    m = re.match(r"--> duplicated code: symbol (\S+) is duplicated by (\S+), size = (\d+)", line)
                    if m:
                        group[find(m.group(1))] = find(m.group(2))
                        sizes[m.group(1)] = int(m.group(3))
                elif line.startswith("--> the function") and "will be replaced by a branch" in line:
                    name = line.split()[3]
                    branches[name] = sizes.get(name, 0)
                elif line.startswith("  UNUSED"):
                    fields = line.split()
                    if len(fields) > 4:
                        unused.add(fields[4])
    found = Link({name: find(name) for name in list(group)})
    found.unused = unused
    found.branches = branches
    symbols = ROOT / "config" / version / "symbols.txt"
    if symbols.is_file():
        found.kept = set(re.findall(r"^(\S+) = ", symbols.read_text(encoding="utf-8"), re.M))
    return found


def group_name(folded: Dict[str, str], name: str) -> str:
    # Where several symbols share a name, symbols.txt tells them apart by address.
    plain = re.sub(r"_8[0-9A-F]{7}$", "", name)
    return folded.get(name) or folded.get(plain) or name


def versions() -> List[str]:
    text = (ROOT / "configure.py").read_text(encoding="utf-8")
    block = re.search(r"^VERSIONS = \[(.*?)\]", text, re.S | re.M)
    return re.findall(r'"(\w+)"', block.group(1)) if block else []


def unit_command(version: str, cplusplus: bool, unit: Optional[str], mw_version: Optional[str]) -> Optional[Tuple[Path, str]]:
    """Returns the compiler and the flags configure.py gives a unit, from the list it writes for this purpose."""
    path = ROOT / "build" / "unit_flags.json"
    if unit is None or not path.is_file():
        return None
    try:
        listed = json.loads(path.read_text(encoding="utf-8"))
    except ValueError:
        return None
    entry = listed["units"].get(unit)
    if entry is None:
        return None
    flags = list(entry["cflags"])
    if not any(flag.startswith("-lang") for flag in flags):
        flags.insert(0, "-lang=c++" if cplusplus else "-lang=c")
    text = " ".join(flags).replace(listed["version"], version)
    text = re.sub(r"-DBUILD_VERSION=\d+", f"-DBUILD_VERSION={versions().index(version)}", text)
    compiler = ROOT / "build" / "compilers" / (mw_version or entry["mw_version"]) / "mwcceppc.exe"
    return compiler, text


def compile_command(version: str, cplusplus: bool) -> Tuple[Path, str]:
    """Returns the compiler and the flags the build uses for game code."""
    text = (ROOT / "build.ninja").read_text(encoding="utf-8").replace("$\n", "")
    wanted = REFERENCE.replace("/", "\\\\")
    edge = re.search(rf"^build \S+: mwcc\w* +{wanted}.*\n((?:  .*\n)+)", text, re.M)
    if not edge:
        sys.exit(f"no compile step for {REFERENCE} in build.ninja (run configure.py)")
    variables = dict(re.findall(r"^  (\w+) = (.*)$", edge.group(1), re.M))
    flags = re.sub(r" +", " ", variables["cflags"])
    configured = re.search(r"-DVERSION_(\w+)", flags).group(1)
    flags = flags.replace(configured, version)
    flags = re.sub(r"-DBUILD_VERSION=\d+", f"-DBUILD_VERSION={versions().index(version)}", flags)
    if not cplusplus:
        flags = flags.replace("-lang=c++", "-lang=c")
    compiler = ROOT / "build" / "compilers" / variables["mw_version"].replace("\\", "/") / "mwcceppc.exe"
    return compiler, flags


def functions(path: Path, folded: Dict[str, str]) -> Dict[str, Function]:
    """Returns the functions of an object, with every relocated field cleared.

    Calls and branches that stay inside their function are resolved first, so
    that an object with a relocation on one compares equal to one without.
    """
    data = path.read_bytes()
    shoff, = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    sections = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]

    def string(table: int, offset: int) -> str:
        start = sections[table][4] + offset
        return data[start : data.index(b"\0", start)].decode("utf-8", "replace")

    symtab = next(s for s in sections if s[1] == 2)
    symbols = []
    for i in range(symtab[5] // 16):
        name, value, size, info, _, shndx = struct.unpack_from(">IIIBBH", data, symtab[4] + i * 16)
        # MetaFortress compiled its rewritten copy of a file, X_prt.cpp, and the
        # file name is part of every symbol in an unnamed namespace.
        symbols.append((string(symtab[6], name), value, size, info, shndx))
    base = lowest_serial(symbol[0] for symbol in symbols)
    spelled = {plain(symbol[0], base): symbol[0] for symbol in symbols}
    symbols = [(plain(symbol[0], base), *symbol[1:]) for symbol in symbols]

    def grouped(name: str) -> str:
        # The link map spells a folded function the way the original object does.
        raw = spelled.get(name, name)
        group = group_name(folded, raw)
        if group == raw and "@unnamed@" in name:
            # The map has the original's X_prt_cpp spelling, a compiled object does not.
            by_plain = getattr(folded, "by_plain", None)
            if by_plain is None:
                by_plain = {plain(key): value for key, value in folded.items() if "@unnamed@" in key}
                try:
                    folded.by_plain = by_plain  # type: ignore[attr-defined]
                except AttributeError:
                    pass
            group = by_plain.get(name, raw)
        return name if group == raw else group

    held: Dict[int, Dict[int, str]] = {}
    for name, value, size, info, shndx in symbols:
        if info & 0xF == 1 and size and name and name[0] not in "@." and not name.startswith(("lbl_", "...")):
            for address in range(value, value + size):
                held.setdefault(shndx, {})[address] = name

    found = {}
    for index, section in enumerate(sections):
        if section[1] != 1 or not section[2] & 4:
            continue
        code = bytearray(data[section[4] : section[4] + section[5]])
        inside = sorted((value, size, name) for name, value, size, info, shndx in symbols if shndx == index and info & 0xF == 2 and size)

        def owner(offset: int) -> Optional[Tuple[int, int, str]]:
            return next((f for f in inside if f[0] <= offset < f[0] + f[1]), None)

        targets: Dict[str, List[Tuple[int, str]]] = {name: [] for _, _, name in inside}
        relocated = set()
        for rela in sections:
            if rela[1] != 4 or rela[7] != index:
                continue
            for i in range(rela[5] // 12):
                offset, info, addend = struct.unpack_from(">IIi", data, rela[4] + i * 12)
                kind, (name, value, _, _, shndx) = info & 0xFF, symbols[info >> 8]
                at = offset & ~3
                function = owner(at)
                if not function:
                    continue
                word, = struct.unpack_from(">I", code, at)
                relocated.add(at)
                local = shndx == index and function[0] <= value + addend < function[0] + function[1]
                if kind in (R_PPC_REL24, R_PPC_REL14) and local:
                    field = ~MASKS[kind] & 0xFFFFFFFF
                    struct.pack_into(">I", code, at, word & MASKS[kind] | (value + addend - at) & field)
                    continue
                struct.pack_into(">I", code, at, word & MASKS.get(kind, 0xFFFF0000))
                if shndx != index and (not name or name[0] in "@." or name.startswith(("lbl_", "..."))):
                    # The compiler may address a unit's statics through one anchor per section.
                    name = held.get(shndx, {}).get(value + addend, "(data)") if name.startswith("...") else "(data)"
                elif shndx == index and owner(value + addend):
                    name = owner(value + addend)[2]
                # A static local carries a number that depends on what was compiled before it.
                name = re.sub(r"\$\d+$", "$", name)
                targets[function[2]].append((at - function[0], grouped(name)))
        for at in range(0, len(code) - 3, 4):
            word, = struct.unpack_from(">I", code, at)
            function = owner(at)
            if at in relocated or not function:
                continue
            # r13 and r2 only ever hold the small data bases. The split objects
            # lack the relocation where inline data, read as code, seemed to
            # change the register first.
            if (word >> 26 == 14 or 32 <= word >> 26 <= 55) and (word >> 16) & 31 in (2, 13):
                struct.pack_into(">I", code, at, word & MASKS[R_PPC_EMB_SDA21])
                targets[function[2]].append((at - function[0], LOST))
            if word >> 26 != 18:
                continue
            target = at + ((word & 0x03FFFFFC) ^ 0x02000000) - 0x02000000
            if not function[0] <= target < function[0] + function[1]:
                struct.pack_into(">I", code, at, word & 0xFC000003)
                callee = owner(target)
                targets[function[2]].append((at - function[0], grouped(callee[2]) if callee else "(unknown)"))
        for value, size, name in inside:
            found[name] = Function(bytes(code[value : value + size]), tuple(sorted(targets[name])), string(shstrndx, section[0]))
    return found


class Data(NamedTuple):
    size: int
    contents: Optional[bytes]
    targets: Tuple[Tuple[int, str, int], ...]
    weak: bool = False
    some_weak: bool = False


def data_sections(path: Path, folded: Dict[str, str]) -> Dict[str, Data]:
    """Returns the sections of an object that are not code, with every relocated word cleared."""
    data = path.read_bytes()
    shoff, = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    sections = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]

    def string(table: int, offset: int) -> str:
        start = sections[table][4] + offset
        return data[start : data.index(b"\0", start)].decode("utf-8", "replace")

    names = [string(shstrndx, section[0]) for section in sections]
    symtab = next(s for s in sections if s[1] == 2)
    symbols = []
    for i in range(symtab[5] // 16):
        name, value, size, info, _, shndx = struct.unpack_from(">IIIBBH", data, symtab[4] + i * 16)
        symbols.append((string(symtab[6], name), value, size, info, shndx))
    base = lowest_serial(symbol[0] for symbol in symbols)
    spelled = {plain(symbol[0], base): symbol[0] for symbol in symbols}
    symbols = [(plain(symbol[0], base), *symbol[1:]) for symbol in symbols]

    def grouped(name: str) -> str:
        # The link map spells a folded function the way the original object does.
        raw = spelled.get(name, name)
        group = group_name(folded, raw)
        if group == raw and "@unnamed@" in name:
            # The map has the original's X_prt_cpp spelling, a compiled object does not.
            by_plain = getattr(folded, "by_plain", None)
            if by_plain is None:
                by_plain = {plain(key): value for key, value in folded.items() if "@unnamed@" in key}
                try:
                    folded.by_plain = by_plain  # type: ignore[attr-defined]
                except AttributeError:
                    pass
            group = by_plain.get(name, raw)
        return name if group == raw else group

    def target(symbol: int, addend: int) -> Tuple[str, int]:
        name, value, _, _, shndx = symbols[symbol]
        if not 0 < shndx < len(sections):
            return grouped(name), addend
        if sections[shndx][2] & 4:
            inside = [s for s in symbols if s[4] == shndx and s[3] & 0xF == 2 and s[2] and s[1] <= value + addend < s[1] + s[2]]
            if inside:
                return grouped(inside[0][0]), value + addend - inside[0][1]
        return names[shndx], value + addend

    found: Dict[str, Data] = {}
    for index, section in enumerate(sections):
        if section[1] not in (1, 8) or not section[2] & 2 or section[2] & 4 or not section[5]:
            continue
        inside = [s for s in symbols if s[4] == index and s[3] & 0xF == 1]
        weak = bool(inside) and all(s[3] >> 4 == 2 for s in inside)
        some_weak = any(s[3] >> 4 == 2 for s in inside)
        if section[1] == 8:
            found[names[index]] = Data(section[5], None, (), weak, some_weak)
            continue
        contents = bytearray(data[section[4] : section[4] + section[5]])
        targets = []
        for rela in sections:
            if rela[1] != 4 or rela[7] != index:
                continue
            for i in range(rela[5] // 12):
                offset, info, addend = struct.unpack_from(">IIi", data, rela[4] + i * 12)
                struct.pack_into(">I", contents, offset, 0)
                targets.append((offset, *target(info >> 8, addend)))
        found[names[index]] = Data(section[5], bytes(contents), tuple(sorted(targets)), weak, some_weak)
    return found


WEAK_DATA = "holds weak data (strings and tables of inline functions) that the link drops where another unit has it"


def data_states(original: Dict[str, Data], compiled: Dict[str, Data]) -> Dict[str, str]:
    """Says, per data section, how the compiled one compares. The original's may end in padding."""
    found = {}
    for name in sorted(set(original) | set(compiled)):
        mine, theirs = compiled.get(name), original.get(name)
        if mine is None:
            found[name] = f"not in the compiled object (0x{theirs.size:X} bytes)"
        elif theirs is None and mine.weak:
            found[name] = "matches"
        elif theirs is None:
            found[name] = f"not in the original object (0x{mine.size:X} bytes compiled)"
        elif mine.size > theirs.size and mine.some_weak:
            found[name] = WEAK_DATA
        elif mine.size > theirs.size:
            found[name] = f"differs (0x{mine.size:X} bytes, original has 0x{theirs.size:X})"
        elif mine.contents is None or theirs.contents is None:
            found[name] = "matches" if theirs.size - mine.size < 8 else f"0x{mine.size:X} of 0x{theirs.size:X} bytes"
        else:
            wrong = next((i for i in range(mine.size) if mine.contents[i] != theirs.contents[i]), None)
            mine_targets = mine.targets
            their_targets = tuple(t for t in theirs.targets if t[0] < mine.size)
            if wrong is None and mine_targets != their_targets:
                wrong = min(t[0] for t in set(mine_targets) ^ set(their_targets))
                found[name] = f"differs at +0x{wrong:X} (what the word points to)"
            elif wrong is not None:
                found[name] = f"differs at +0x{wrong & ~3:X}"
            elif theirs.size - mine.size < 8 and not any(theirs.contents[mine.size :]):
                found[name] = "matches"
            else:
                found[name] = f"matches the first 0x{mine.size:X} of 0x{theirs.size:X} bytes"
    return found


def listing(path: Path, name: str, code: bytes) -> List[str]:
    """Returns one function's disassembly with addresses made relative to it and inline data shown as data."""
    text = subprocess.run([str(OBJDUMP), "-d", "-r", "-M", "broadway", "--no-show-raw-insn", str(path)], capture_output=True, text=True).stdout
    lines: List[str] = []
    start = None
    base = lowest_serial(re.findall(r"^[0-9a-f]+ <(.+)>:$", text, re.M))
    for line in text.splitlines():
        header = re.match(r"^([0-9a-f]+) <(.+)>:$", line)
        if header:
            start = int(header.group(1), 16) if plain(header.group(2), base) == name else None
        elif start is not None and line.strip():
            reloc = re.match(r"^\s+[0-9a-f]+: (R_PPC_\w+)\s+(.+)$", line)
            if reloc:
                if lines:
                    symbol, _, addend = reloc.group(2).partition("+0x")
                    if symbol == name:
                        symbol = addend or "0"
                    elif re.match(r"^(@|\.|lbl_)", symbol):
                        symbol = "(data)"
                    lines[-1] = re.sub(r" ?\b[0-9a-f]+$", "", lines[-1]) + " " + symbol
                continue
            body = re.sub(r"^\s*[0-9a-f]+:\s*", "", line).strip()

            def relative(m: "re.Match[str]") -> str:
                return f"{int(m.group(1), 16) - start:x}"

            body = re.sub(r"\b([0-9a-f]+) <[^>]*>", relative, body)
            lines.append(re.sub(r"\s+", " ", body))
    for i, line in enumerate(lines):
        skip = re.match(r"^bl ([0-9a-f]+)$", line)
        if skip and i < int(skip.group(1), 16) // 4 <= min(i + 0x41, len(lines)):
            for j in range(i + 1, int(skip.group(1), 16) // 4):
                lines[j] = f".long 0x{int.from_bytes(code[j * 4 : j * 4 + 4], 'big'):08x}"
    return lines


MW_VERSION: Optional[str] = None


def build(version: str, source: Path, extra: str, out: Path, unit: Optional[str] = None) -> Optional[str]:
    """Compiles a source the way the build would. Returns the compiler's complaint, if any."""
    if unit is None:
        try:
            unit = source.resolve().relative_to(ROOT / "src").with_suffix("").as_posix()
        except ValueError:
            unit = None
    compiler, flags = unit_command(version, source.suffix != ".c", unit, MW_VERSION) or compile_command(version, source.suffix != ".c")
    command = f'"{ROOT / "build" / "tools" / "sjiswrap.exe"}" "{compiler}" {flags} {extra} -c "{source}" -o "{out}"'
    result = subprocess.run(command, capture_output=True, text=True, cwd=ROOT)
    return (result.stdout + result.stderr).strip() if result.returncode else None


ABSENT = "the unit is not in this version"


def has_unit(version: str, unit: str) -> bool:
    """Returns whether a version's splits name the unit. A few units exist in one version only."""
    splits = (ROOT / "config" / version / "splits.txt").read_text(encoding="utf-8")
    return any(line.startswith(unit + ".") and line.rstrip().endswith(":") for line in splits.splitlines())


def original_object(version: str, unit: str) -> Path:
    path = ROOT / "build" / version / "obj" / (unit + ".o")
    if not path.is_file():
        sys.exit(f"{path} not found: is {unit} a unit of {version}, and has the build been run?")
    return path


def same_targets(a: Tuple[Tuple[int, str], ...], b: Tuple[Tuple[int, str], ...]) -> bool:
    return len(a) == len(b) and all(x[0] == y[0] and (x[1] == y[1] or LOST in (x[1], y[1])) for x, y in zip(a, b))


FOLDED = "folded into a look-alike by the original link"
ELSEWHERE = "kept in another unit by the original link"
UNUSED_STATE = "unused, dropped by the original link"
BRANCH = "replaced by a branch to a look-alike by the original link"
NOT_COUNTED = (FOLDED, ELSEWHERE, UNUSED_STATE, BRANCH)


def states(original: Dict[str, Function], compiled: Dict[str, Function], folded: Dict[str, str]) -> Dict[str, str]:
    found = {}
    for name, mine in compiled.items():
        theirs = original.get(name)
        if theirs is None:
            if name in folded:
                found[name] = FOLDED
            elif name in getattr(folded, "kept", ()):
                found[name] = ELSEWHERE
            elif name in getattr(folded, "unused", ()):
                found[name] = UNUSED_STATE
            else:
                found[name] = "not in the original object"
        elif len(theirs.code) == 4 and getattr(folded, "branches", {}).get(name) == len(mine.code):
            found[name] = BRANCH
        elif mine.code != theirs.code:
            found[name] = f"differs ({len(mine.code) // 4} instructions, original has {len(theirs.code) // 4})"
        elif not same_targets(mine.targets, theirs.targets):
            wrong = sorted(set(mine.targets) ^ set(theirs.targets))
            found[name] = "same code, other symbols referenced: " + ", ".join(f"+0x{offset:X} {symbol}" for offset, symbol in wrong[:6])
        else:
            found[name] = "matches"
    return found


def compare(version: str, source: Path, unit: str, show: Optional[str], extra: str) -> bool:
    original_path = original_object(version, unit)
    with tempfile.TemporaryDirectory() as tmp:
        compiled_path = Path(tmp) / "compiled.o"
        error = build(version, source, extra, compiled_path, unit)
        if error:
            print(f"{version}: does not compile")
            print(error)
            return False
        folded = merged(version)
        original = functions(original_path, folded)
        compiled = functions(compiled_path, folded)
        found = states(original, compiled, folded)
        for name, state in found.items():
            print(f"{version}: {state:10} {name}")
            if show is not None and show in name and state != "matches" and name in original:
                a, b = listing(original_path, name, original[name].code), listing(compiled_path, name, compiled[name].code)
                print(f"      {'original':40} compiled")
                for i in range(max(len(a), len(b))):
                    x, y = a[i] if i < len(a) else "", b[i] if i < len(b) else ""
                    print(f"   {'  ' if x == y else '!='} {x:40} {y}")
        data = data_states(data_sections(original_path, folded), data_sections(compiled_path, folded))
        for name, state in data.items():
            print(f"{version}: {name:10} {state}")
        matched = sum(state == "matches" for state in found.values())
        counted = sum(state not in NOT_COUNTED for state in found.values())
        branches = sum(state == BRANCH for state in found.values())
        # Only the order inside a section is the compiler's; the sections' own order is the linker script's.
        mine_order = sorted((name for name in compiled if name in original), key=lambda name: compiled[name].section)
        their_order = sorted((name for name in original if name in compiled), key=lambda name: original[name].section)
        misplaced = next((i for i in range(len(mine_order)) if mine_order[i] != their_order[i]), None)
        if misplaced is not None:
            print(f"{version}: the functions are in another order: the original has {their_order[misplaced]} where this has {mine_order[misplaced]}")
        print(f"{version}: {matched} of {counted} compiled functions match; the unit has {len(original) - branches}" + (f" and {branches} branches" if branches else ""))
        if matched == counted and misplaced is None and not set(original) - set(compiled) and all(state in ("matches", WEAK_DATA) for state in data.values()):
            if WEAK_DATA in data.values():
                print(f"{version}: the unit is complete as far as this can tell: every function matches, and only a link can check data that holds weak copies")
            else:
                print(f"{version}: the unit is complete: every function and every data section matches")
        return matched == counted


def permute(version: str, source: Path, unit: str, text: str, extra: str) -> None:
    """Tries every order of one function's local declarations.

    The compiler hands out registers to locals in an order that depends on how
    they are declared, in ways that are easier to search than to predict.
    volatile locals stay where they are: their order fixes the stack layout.
    """
    lines = source.read_text(encoding="utf-8").split("\n")
    first = next((i for i, line in enumerate(lines) if text in line and line.rstrip().endswith("{")), None)
    if first is None:
        sys.exit(f"no line that contains {text!r} and opens a function")
    block = []
    for i in range(first + 1, len(lines)):
        if not re.match(r"^\s+[\w:<>,*&\s]+[\s*&]\w+(\[\w*\])?( = [^;]+)?;\s*$", lines[i]):
            break
        block.append(i)
    movable = [i for i in block if not lines[i].lstrip().startswith("volatile")]
    if not 2 <= len(movable) <= 7:
        sys.exit(f"{len(movable)} declarations to reorder; this handles 2 to 7")
    folded = merged(version)
    original = functions(original_object(version, unit), folded)
    best: Dict[int, List[str]] = {}
    with tempfile.TemporaryDirectory() as tmp:
        trial, compiled_path = Path(tmp) / source.name, Path(tmp) / "compiled.o"
        for order in itertools.permutations(movable):
            changed = list(lines)
            for slot, index in zip(movable, order):
                changed[slot] = lines[index]
            trial.write_text("\n".join(changed), encoding="utf-8", newline="\n")
            if build(version, trial, extra, compiled_path, unit):
                continue
            matched = sum(state == "matches" for state in states(original, functions(compiled_path, folded), folded).values())
            best.setdefault(matched, []).append("  ".join(lines[index].strip() for index in order))
    if not best:
        sys.exit("no order compiles")
    most = max(best)
    print(f"{version}: at most {most} functions match, with {len(best[most])} of {sum(len(v) for v in best.values())} orders:")
    for order in best[most][:12]:
        print("   ", order)


def survey(chosen: List[str], root: Path, extra: str) -> bool:
    """Compares every source below a directory and prints what does not match."""
    total = matched = 0
    for version in chosen:
        folded = merged(version)
        with tempfile.TemporaryDirectory() as tmp:
            compiled_path = Path(tmp) / "compiled.o"
            for source in sorted(p for p in root.rglob("*") if p.suffix in (".c", ".cpp")):
                shown = source.relative_to(ROOT).as_posix()
                unit = source.relative_to(ROOT / "src").with_suffix("").as_posix()
                if build(version, source, extra, compiled_path):
                    print(f"{version}: {shown}: does not compile")
                    total += 1
                    continue
                found = states(functions(original_object(version, unit), folded), functions(compiled_path, folded), folded)
                found = {name: state for name, state in found.items() if state not in NOT_COUNTED}
                total += len(found)
                matched += sum(state == "matches" for state in found.values())
                for name, state in found.items():
                    if state != "matches":
                        print(f"{version}: {shown}: {state.split(':')[0]}: {name}")
    print(f"{matched} of {total} compiled functions match")
    return matched == total


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("version", help="game ID such as SUKE01, or all")
    parser.add_argument("source", type=Path, help="source file to compile, or a directory below src/ to check every file in it")
    parser.add_argument("-u", "--unit", help="unit to compare with, e.g. storage/ArenaGameData (default: from the path below src/)")
    parser.add_argument("-f", "--function", metavar="NAME", help="show the disassembly of differing functions whose symbol contains NAME (empty for all)")
    parser.add_argument("-p", "--permute", metavar="TEXT", help="try every order of the local declarations in the function whose opening line contains TEXT")
    parser.add_argument("--flags", default="", help="extra compiler flags, for experiments")
    parser.add_argument("--mw", metavar="VERSION", help="compiler version to use instead of the unit's, e.g. Wii/1.0")
    args = parser.parse_args()
    global MW_VERSION
    MW_VERSION = args.mw

    source = args.source.resolve()
    chosen = versions() if args.version.lower() == "all" else [args.version.upper()]
    if source.is_dir():
        sys.exit(0 if survey(chosen, source, args.flags) else 1)
    unit = args.unit
    if not unit:
        try:
            unit = source.relative_to(ROOT / "src").with_suffix("").as_posix()
        except ValueError:
            sys.exit("the source is not below src/; name the unit with -u")
    if args.permute:
        permute(chosen[0], source, unit, args.permute, args.flags)
        return
    results = []
    for version in chosen:
        if len(chosen) > 1 and not has_unit(version, unit):
            print(f"{version}: {ABSENT}")
            continue
        results.append(compare(version, source, unit, args.function, args.flags))
    sys.exit(0 if results and all(results) else 1)


if __name__ == "__main__":
    main()
