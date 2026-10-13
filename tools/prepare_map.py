#!/usr/bin/env python3

###
# Prepares the CodeWarrior link map shipped on the Kirby's Return to Dream Land
# disc (files/iuk.MAP) for decomp-toolkit's initial analysis.
#
# The map matches the retail DOL, but decomp-toolkit cannot consume it as-is:
#
# - It was produced with code merging enabled, so it opens with ~16,000
#   "--> duplicated code" messages instead of a symbol closure.
# - The ~4,400 game objects (src.a) are listed without paths, and most share
#   their file name with other objects (218 ModelDesc.o, 175 Custom.o, ...).
#   The map gives no direct way to tell which .text/.data/.sdata2/... pieces
#   belong to the same translation unit.
#
# This script rebuilds that association and writes a cleaned map in which every
# translation unit has a unique, path-like name:
#
# 1. Every section contribution is paired up with the others of its translation
#    unit. Candidates always share the same object name and must respect the
#    link order (which is identical in every section). Ambiguity is resolved
#    with references recovered from the DOL: code referencing a section-local
#    symbol, .ctors entries pointing at __sinit functions, jump tables and
#    vtables pointing back into .text, and so on.
# 2. Game translation units are given a directory derived from the C++
#    namespaces of the symbols they define (scn::step::hero::Hero ->
#    scn/step/hero/Hero.cpp). SDK and middleware units are named after the
#    library they came from.
#
# Usage:
#   python tools/prepare_map.py orig/SUKE01/files/iuk.MAP orig/SUKE01/sys/main.dol \
#       -o build/SUKE01/iuk.clean.MAP --report build/SUKE01/units.txt
#
# This is one step of tools/setup_version.py, which generates the symbols and
# splits of a game version from scratch. See docs/map.md.
###

import argparse
import bisect
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, NamedTuple, Optional, Tuple

GAME_LIB = "src.a"
LINKER_GENERATED = "Linker Generated Symbol File"

# Sections whose contents are present in the DOL and may hold pointers.
POINTER_SECTIONS = (".ctors", ".rodata", ".data", ".sdata", ".sdata2")
# Order in which sections are aligned against the translation unit list.
# .text comes first, as nearly every translation unit has code.
ALIGN_ORDER = (
    ".text",
    ".ctors",
    ".data",
    ".rodata",
    ".sdata2",
    ".sdata",
    ".sbss",
    ".bss",
    ".sbss2",
)

SECTION_RE = re.compile(r"^(\S+) section layout\s*$")
ENTRY_RE = re.compile(
    r"^  ([0-9a-f]{8}) ([0-9a-f]{6}) ([0-9a-f]{8}) ([0-9a-f]{8}) +(?:(\d+) )?(.*)$"
)
ENTRY_OF_RE = re.compile(r"^(.*?) \(entry of (.*)\)$")


###
# Map parsing
###


class Symbol:
    __slots__ = ("name", "addr", "size", "align", "entry_of", "fields")

    def __init__(self, name, addr, size, align, entry_of, fields):
        self.name: str = name
        self.addr: int = addr
        self.size: int = size
        self.align: Optional[str] = align
        self.entry_of: Optional[str] = entry_of
        self.fields: Tuple[str, str, str, str] = fields


class Contrib:
    """One object file's contribution to one output section."""

    __slots__ = (
        "section",
        "index",
        "lib",
        "obj",
        "addr",
        "size",
        "header",
        "symbols",
        "unit",
    )

    def __init__(self, section, index, lib, obj, addr, size, header):
        self.section: str = section
        self.index: int = index
        self.lib: str = lib
        self.obj: str = obj
        self.addr: int = addr
        self.size: int = size
        # (name, align, fields) of the section header line, if any
        self.header: Optional[Tuple[str, Optional[str], Tuple[str, str, str, str]]] = header
        self.symbols: List[Symbol] = []
        self.unit: Optional["Unit"] = None

    @property
    def key(self) -> Tuple[str, str]:
        return (self.lib, self.obj)

    @property
    def end(self) -> int:
        return self.addr + self.size


class MapFile:
    def __init__(self):
        self.entry_line: str = ""
        self.sections: List[str] = []  # in order of appearance (may repeat)
        self.layout: Dict[str, List[Contrib]] = {}
        self.tail: List[str] = []  # memory map + linker generated symbols
        self.memory_map: Dict[str, Tuple[int, int]] = {}
        self.linker_symbols: Dict[str, int] = {}


def split_unit(text: str) -> Tuple[str, str]:
    text = text.strip()
    if text == LINKER_GENERATED:
        return ("", LINKER_GENERATED)
    parts = text.split(" ", 1)
    if len(parts) == 2 and parts[0].endswith(".a"):
        return (parts[0], parts[1].strip())
    return ("", text)


def parse_map(path: Path) -> MapFile:
    result = MapFile()
    section: Optional[str] = None
    in_tail = False
    with open(path, "r", encoding="latin-1", newline="") as f:
        lines = f.read().replace("\r\n", "\n").split("\n")

    for line in lines:
        if in_tail:
            result.tail.append(line)
            continue
        if line.startswith("Link map of "):
            result.entry_line = line.rstrip()
            continue
        if line.startswith("Memory map:"):
            in_tail = True
            result.tail.append(line)
            continue
        m = SECTION_RE.match(line)
        if m:
            section = m.group(1)
            result.sections.append(section)
            result.layout.setdefault(section, [])
            continue
        if section is None:
            # Code merging messages
            continue
        m = ENTRY_RE.match(line)
        if not m:
            # Column headers, blank lines and UNUSED (stripped) symbols
            continue
        off, size, addr, file_off, align, rest = m.groups()
        if "\t" not in rest:
            if rest.strip() != "*fill*":
                raise ValueError(f"Unexpected map line: {line!r}")
            continue
        sym_part, unit_part = rest.split("\t", 1)
        sym_part = sym_part.strip()
        lib, obj = split_unit(unit_part)
        fields = (off, size, addr, file_off)
        contribs = result.layout[section]

        is_header = sym_part == section or sym_part.startswith(section + "$")
        if is_header:
            contribs.append(
                Contrib(section, len(contribs), lib, obj, int(addr, 16), int(size, 16), (sym_part, align, fields))
            )
            continue

        if not contribs or contribs[-1].key != (lib, obj):
            # extabindex entries have no section header line
            contribs.append(Contrib(section, len(contribs), lib, obj, int(addr, 16), 0, None))
        contrib = contribs[-1]
        entry_of = None
        m = ENTRY_OF_RE.match(sym_part)
        name = sym_part
        if m:
            name, entry_of = m.group(1), m.group(2)
        if " " in name:
            raise ValueError(f"Symbol name contains whitespace: {line!r}")
        sym = Symbol(name, int(addr, 16), int(size, 16), align, entry_of, fields)
        contrib.symbols.append(sym)
        if contrib.header is None:
            contrib.size = max(contrib.size, sym.addr + sym.size - contrib.addr)

    # Parse the tail for section addresses and linker generated symbols
    mode = None
    for line in result.tail:
        if line.startswith("Memory map:"):
            mode = "memory"
            continue
        if line.startswith("Linker generated symbols:"):
            mode = "symbols"
            continue
        parts = line.split()
        if mode == "memory" and len(parts) == 4:
            try:
                result.memory_map[parts[0]] = (int(parts[1], 16), int(parts[2], 16))
            except ValueError:
                pass
        elif mode == "symbols" and len(parts) == 2:
            try:
                result.linker_symbols[parts[0]] = int(parts[1], 16)
            except ValueError:
                pass
    return result


###
# DOL access
###


class Dol:
    def __init__(self, path: Path):
        self.data = path.read_bytes()
        offs = struct.unpack_from(">18I", self.data, 0x00)
        addrs = struct.unpack_from(">18I", self.data, 0x48)
        sizes = struct.unpack_from(">18I", self.data, 0x90)
        self.segments = sorted(
            (addrs[i], sizes[i], offs[i]) for i in range(18) if sizes[i] != 0
        )

    def offset(self, addr: int, size: int) -> Optional[int]:
        for seg_addr, seg_size, seg_off in self.segments:
            if seg_addr <= addr and addr + size <= seg_addr + seg_size:
                return seg_off + (addr - seg_addr)
        return None

    def words(self, addr: int, size: int) -> Tuple[int, ...]:
        """Returns the big-endian words in [addr, addr+size), rounded inwards."""
        start = (addr + 3) & ~3
        count = (addr + size - start) // 4
        if count <= 0:
            return ()
        off = self.offset(start, count * 4)
        if off is None:
            return ()
        return struct.unpack_from(f">{count}I", self.data, off)


###
# Reference analysis
###


class AddressIndex:
    """Maps addresses to section contributions and symbols."""

    def __init__(self, layout: Dict[str, List[Contrib]]):
        self.contribs: List[Contrib] = []
        for section, contribs in layout.items():
            self.contribs.extend(c for c in contribs if c.size > 0 and c.obj != LINKER_GENERATED)
        self.contribs.sort(key=lambda c: c.addr)
        self.starts = [c.addr for c in self.contribs]
        self.sym_starts: Dict[int, List[int]] = {}
        self.syms: Dict[int, List[Symbol]] = {}
        for c in self.contribs:
            syms = sorted(c.symbols, key=lambda s: (s.addr, -s.size))
            self.syms[id(c)] = syms
            self.sym_starts[id(c)] = [s.addr for s in syms]

    def find(self, addr: int) -> Optional[Contrib]:
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0:
            return None
        c = self.contribs[i]
        if addr < c.end:
            return c
        return None

    def find_symbol(self, contrib: Contrib, addr: int) -> Optional[Symbol]:
        starts = self.sym_starts[id(contrib)]
        syms = self.syms[id(contrib)]
        i = bisect.bisect_right(starts, addr) - 1
        while i >= 0:
            s = syms[i]
            if s.addr <= addr < s.addr + max(s.size, 1):
                return s
            if s.addr + s.size < addr - 0x10000:
                break
            i -= 1
        return None


def sign16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


# D-form load/store opcodes (lwz..stfdu, plus lmw/stmw)
LOAD_STORE_OPS = frozenset(range(32, 56))
# Of those, the ones that write a general purpose register
GPR_LOAD_OPS = frozenset((32, 33, 34, 35, 40, 41, 42, 43, 46))


def scan_code_refs(words: Tuple[int, ...], func_starts: frozenset, base_addr: int, sda: int, sda2: int) -> List[int]:
    """
    Finds addresses referenced by a run of PowerPC code: small data accesses
    relative to r13/r2, and addresses built from a lis + addi/ori/load/store pair.
    This is a linear scan without control flow analysis, which is plenty for
    gathering evidence.
    """
    targets: List[int] = []
    hi: Dict[int, int] = {}
    addr = base_addr
    for w in words:
        if addr in func_starts:
            hi.clear()
        addr += 4
        op = w >> 26
        if op == 15:  # addis
            rd = (w >> 21) & 31
            ra = (w >> 16) & 31
            if ra == 0:
                hi[rd] = (w & 0xFFFF) << 16
            else:
                hi.pop(rd, None)
        elif op == 14:  # addi
            rd = (w >> 21) & 31
            ra = (w >> 16) & 31
            if ra == 13:
                targets.append(sda + sign16(w & 0xFFFF))
            elif ra == 2:
                targets.append(sda2 + sign16(w & 0xFFFF))
            elif ra != 0 and ra in hi:
                targets.append((hi[ra] + sign16(w & 0xFFFF)) & 0xFFFFFFFF)
            hi.pop(rd, None)
        elif op in LOAD_STORE_OPS:
            rd = (w >> 21) & 31
            ra = (w >> 16) & 31
            if ra == 13:
                targets.append(sda + sign16(w & 0xFFFF))
            elif ra == 2:
                targets.append(sda2 + sign16(w & 0xFFFF))
            elif ra in hi:
                targets.append((hi[ra] + sign16(w & 0xFFFF)) & 0xFFFFFFFF)
            if op in GPR_LOAD_OPS:
                hi.pop(rd, None)
        elif op == 24:  # ori
            rs = (w >> 21) & 31
            ra = (w >> 16) & 31
            if rs in hi:
                targets.append(hi[rs] | (w & 0xFFFF))
            hi.pop(ra, None)
        elif op == 18 or op == 16 or (op == 19 and ((w >> 1) & 0x3FF) in (16, 528)):
            # b/bl, bc, bclr/bcctr: volatile registers do not survive calls,
            # and anything after an unconditional branch is a new block.
            if op == 18 and (w & 1) == 0:
                hi.clear()
            elif op == 19 and ((w >> 21) & 0x14) == 0x14 and (w & 1) == 0:
                hi.clear()
            elif w & 1:
                for reg in (0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12):
                    hi.pop(reg, None)
        elif hi:
            # Anything else: assume both register fields may be clobbered
            hi.pop((w >> 21) & 31, None)
            if op == 31 or 20 <= op <= 29:
                hi.pop((w >> 16) & 31, None)
    return targets


def is_local_name(name: str, name_counts: Counter) -> bool:
    """Whether a symbol can only be referenced from its own translation unit."""
    return (
        name.startswith("@")
        or name.startswith("__sinit_")
        or "@unnamed@" in name
        or "$" in name
        or name_counts[name] > 1
    )


class References:
    """Reference counts between section contributions, keyed by id(contrib)."""

    def __init__(self):
        # (id(a), id(b)) -> [strong, weak], with a < b by address
        self.pairs: Dict[Tuple[int, int], List[int]] = {}
        self.by_contrib: Dict[int, Dict[int, List[int]]] = defaultdict(dict)

    def add(self, src: Contrib, dst: Contrib, strong: bool) -> None:
        if src is dst:
            return
        a, b = (src, dst) if src.addr < dst.addr else (dst, src)
        entry = self.pairs.get((id(a), id(b)))
        if entry is None:
            entry = [0, 0]
            self.pairs[(id(a), id(b))] = entry
            self.by_contrib[id(a)][id(b)] = entry
            self.by_contrib[id(b)][id(a)] = entry
        entry[0 if strong else 1] += 1

    def get(self, a: Contrib, b: Contrib) -> Tuple[int, int]:
        entry = self.by_contrib.get(id(a), {}).get(id(b))
        return (entry[0], entry[1]) if entry else (0, 0)


def analyze_references(map_file: MapFile, dol: Dol) -> References:
    index = AddressIndex(map_file.layout)
    name_counts: Counter = Counter()
    for contribs in map_file.layout.values():
        for c in contribs:
            for s in c.symbols:
                name_counts[s.name] += 1

    sda = map_file.linker_symbols["_SDA_BASE_"]
    sda2 = map_file.linker_symbols["_SDA2_BASE_"]
    text_addr, text_size = map_file.memory_map[".text"]
    text_end = text_addr + text_size
    refs = References()

    def record(src: Contrib, target: int) -> None:
        dst = index.find(target)
        if dst is None or dst is src:
            return
        # Only references between objects of the same name are of interest
        if dst.key != src.key:
            return
        sym = index.find_symbol(dst, target)
        strong = sym is not None and is_local_name(sym.name, name_counts)
        refs.add(src, dst, strong)

    # Interesting keys: only those that are ambiguous need analysis, but the
    # scan is cheap enough to simply run over all game code.
    for section in (".init", ".text"):
        for c in map_file.layout.get(section, []):
            if c.lib != GAME_LIB:
                continue
            words = dol.words(c.addr, c.size)
            starts = frozenset(s.addr for s in c.symbols)
            for target in scan_code_refs(words, starts, (c.addr + 3) & ~3, sda, sda2):
                record(c, target)

    for section in POINTER_SECTIONS:
        for c in map_file.layout.get(section, []):
            if c.lib != GAME_LIB:
                continue
            for w in dol.words(c.addr, c.size):
                if w & 3 or not (0x80004000 <= w < 0x81800000):
                    continue
                if text_addr <= w < text_end:
                    # Pointers into code only count when they hit a function start
                    dst = index.find(w)
                    if dst is None or dst.key != c.key:
                        continue
                    sym = index.find_symbol(dst, w)
                    if sym is None or sym.addr != w:
                        continue
                    refs.add(c, dst, is_local_name(sym.name, name_counts))
                else:
                    record(c, w)
    return refs


###
# Translation unit reconstruction
###


class Unit:
    """A translation unit: one object file as seen across all sections."""

    __slots__ = ("lib", "obj", "contribs", "name")

    def __init__(self, lib: str, obj: str):
        self.lib = lib
        self.obj = obj
        self.contribs: Dict[str, Contrib] = {}
        self.name: str = ""

    @property
    def key(self) -> Tuple[str, str]:
        return (self.lib, self.obj)

    @property
    def stem(self) -> str:
        return obj_stem(self.obj)

    def add(self, contrib: Contrib) -> None:
        assert contrib.section not in self.contribs, (self.obj, contrib.section)
        self.contribs[contrib.section] = contrib
        contrib.unit = self


def obj_stem(obj: str) -> str:
    name = obj.replace("\\", "/").rsplit("/", 1)[-1]
    if name.endswith(".o"):
        name = name[:-2]
    return name


class MatchNote(NamedTuple):
    """A section that was assigned to its translation unit on thin evidence."""

    contrib: Contrib
    # Set when link order ruled out a unit that references the section more
    passed_over: Optional[Unit]


# Scoring
SCORE_BASE = 1  # same name, consistent order, no other evidence
SCORE_STRONG = 40  # reference to a symbol private to the translation unit
SCORE_WEAK = 2  # reference to a symbol that may be shared
SCORE_WEAK_CAP = 20
SCORE_NAMESPACE = 12  # symbols belong to the same classes/namespaces
SCORE_UNIQUE = 500  # the only objects with that name


class Fenwick:
    """Prefix maximum over (score, pair index)."""

    def __init__(self, n: int):
        self.n = n
        self.tree: List[Tuple[int, int]] = [(0, -1)] * (n + 1)

    def update(self, i: int, value: Tuple[int, int]) -> None:
        i += 1
        while i <= self.n:
            if value > self.tree[i]:
                self.tree[i] = value
            i += i & -i

    def query(self, i: int) -> Tuple[int, int]:
        """Maximum over [0, i)."""
        best = (0, -1)
        while i > 0:
            if self.tree[i] > best:
                best = self.tree[i]
            i -= i & -i
        return best


def qualifier_set(symbols: List[Symbol]) -> frozenset:
    result = set()
    for s in symbols:
        comps = symbol_qualifier(s.name)
        if comps:
            result.add("::".join(comps))
    return frozenset(result)


def align_section(
    units: List[Unit],
    contribs: List[Contrib],
    refs: References,
    stats: Counter,
    notes: List[MatchNote],
) -> List[Unit]:
    """
    Assigns each contribution of a section to a translation unit, creating new
    units for those that match none. Returns the updated unit list (link order).
    """
    section = contribs[0].section if contribs else ""
    by_key: Dict[Tuple[str, str], List[int]] = defaultdict(list)
    for ui, unit in enumerate(units):
        if section not in unit.contribs:
            by_key[unit.key].append(ui)
    key_count = Counter(c.key for c in contribs)

    unit_quals: Dict[int, frozenset] = {}

    def unit_qualifiers(ui: int) -> frozenset:
        q = unit_quals.get(ui)
        if q is None:
            syms: List[Symbol] = []
            for c in units[ui].contribs.values():
                syms.extend(c.symbols)
            q = qualifier_set(syms)
            unit_quals[ui] = q
        return q

    # Candidate pairs
    pairs: List[Tuple[int, int, int, int]] = []  # (contrib idx, unit idx, score, evidence class)
    for ci, c in enumerate(contribs):
        candidates = by_key.get(c.key, [])
        if not candidates:
            continue
        own_quals = qualifier_set(c.symbols)
        unique = len(candidates) == 1 and key_count[c.key] == 1
        for ui in candidates:
            strong = weak = 0
            for other in units[ui].contribs.values():
                s, w = refs.get(c, other)
                strong += s
                weak += w
            score = SCORE_BASE
            evidence = 0
            if strong:
                score += SCORE_STRONG + min(strong, 10)
                evidence = 3
            if weak:
                score += min(weak * SCORE_WEAK, SCORE_WEAK_CAP)
                evidence = max(evidence, 2)
            if own_quals:
                shared = len(own_quals & unit_qualifiers(ui))
                if shared:
                    score += max(1, SCORE_NAMESPACE * shared // len(own_quals))
                    evidence = max(evidence, 1)
            if unique:
                score += SCORE_UNIQUE
            pairs.append((ci, ui, score, evidence))

    # Heaviest chain that is increasing in both contribution and unit order.
    # Sorting unit indices descending within a contribution keeps a
    # contribution from being chained with itself.
    order = sorted(range(len(pairs)), key=lambda p: (pairs[p][0], -pairs[p][1]))
    tree = Fenwick(len(units))
    best_score = [0] * len(pairs)
    prev = [-1] * len(pairs)
    for p in order:
        ci, ui, score, _ = pairs[p]
        before, before_pair = tree.query(ui)
        best_score[p] = before + score
        prev[p] = before_pair
        tree.update(ui, (best_score[p], p))
    matched: Dict[int, int] = {}  # contrib idx -> pair idx
    if pairs:
        p = max(range(len(pairs)), key=lambda i: best_score[i])
        while p != -1:
            matched[pairs[p][0]] = p
            p = prev[p]

    # Diagnostics: was the best supported candidate chosen?
    best_for: Dict[int, Tuple[int, int]] = {}
    for p, (ci, ui, score, evidence) in enumerate(pairs):
        if ci not in best_for or (score, -ui) > (pairs[best_for[ci][0]][2], -pairs[best_for[ci][0]][1]):
            best_for[ci] = (p, evidence)

    # Apply
    result: List[Tuple[float, Unit]] = [(float(i), u) for i, u in enumerate(units)]
    last_ui = -1
    pending: List[Contrib] = []

    def flush(next_ui: int) -> None:
        # Unmatched contributions become new units. They belong somewhere
        # between the units of their neighbours in this section; prefer the
        # spot that keeps file names sorted, as they are within a directory.
        for n, c in enumerate(pending):
            unit = Unit(c.lib, c.obj)
            unit.add(c)
            key = sort_key(unit.stem)
            slot = last_ui + 1
            for p in range(last_ui + 1, min(next_ui, len(units) - 1) + 1):
                if p > 0 and sort_key(units[p - 1].stem) < key < sort_key(units[p].stem):
                    slot = p
                    break
            result.append((slot - 1 + (n + 1) / (len(pending) + 1), unit))
        pending.clear()

    for ci, c in enumerate(contribs):
        p = matched.get(ci)
        if p is None:
            # No object of that name left where link order would allow it
            pending.append(c)
            stats[f"{section}: new unit"] += 1
            continue
        _, ui, score, evidence = pairs[p]
        flush(ui)
        last_ui = ui
        units[ui].add(c)
        label = ("order only", "namespace", "weak refs", "strong refs")[evidence]
        if score >= SCORE_UNIQUE:
            label = "unique name"
        stats[f"{section}: matched ({label})"] += 1
        bp, _ = best_for[ci]
        if pairs[bp][1] != ui and pairs[bp][2] > score:
            notes.append(MatchNote(c, units[pairs[bp][1]]))
        elif evidence == 0 and score < SCORE_UNIQUE:
            notes.append(MatchNote(c, None))
    flush(len(units))

    result.sort(key=lambda t: t[0])
    return [u for _, u in result]


def build_units(map_file: MapFile, refs: References, stats: Counter, notes: List[MatchNote]) -> List[Unit]:
    """Reconstructs the translation units (in link order) of the game library."""
    units: List[Unit] = []
    for section in ALIGN_ORDER:
        contribs = [c for c in map_file.layout.get(section, []) if c.lib == GAME_LIB]
        if not contribs:
            continue
        if section == ".text":
            for c in contribs:
                unit = Unit(c.lib, c.obj)
                unit.add(c)
                units.append(unit)
            continue
        units = align_section(units, contribs, refs, stats, notes)
    for section, contribs in map_file.layout.items():
        for c in contribs:
            if c.lib == GAME_LIB and c.unit is None:
                raise ValueError(f"Unhandled section {section} for {c.obj}")
    return units


###
# Naming
###


def parse_qualifier(name: str, pos: int) -> Optional[Tuple[List[str], int]]:
    """Parses a CodeWarrior qualified name (Q<n><len><name>... or <len><name>)."""
    count = 1
    if pos < len(name) and name[pos] == "Q":
        if pos + 1 >= len(name) or not name[pos + 1].isdigit():
            return None
        count = int(name[pos + 1])
        pos += 2
    comps: List[str] = []
    for _ in range(count):
        start = pos
        while pos < len(name) and name[pos].isdigit():
            pos += 1
        if pos == start:
            return None
        length = int(name[start:pos])
        if length == 0 or pos + length > len(name):
            return None
        comps.append(name[pos : pos + length])
        pos += length
    return comps, pos


def symbol_qualifier(name: str) -> Optional[List[str]]:
    """
    Returns the namespace/class components a mangled symbol is declared in,
    e.g. ["scn", "arena", "Main"] for __ct__Q33scn5arena4MainFv.
    """
    start = 1
    while True:
        i = name.find("__", start)
        if i == -1:
            return None
        pos = i + 2
        while pos < len(name) and name[pos] == "_":
            pos += 1
        parsed = parse_qualifier(name, pos)
        if parsed is not None:
            comps, end = parsed
            # Must be followed by a function signature, or end the name
            if end == len(name) or name[end] in "FC@":
                return comps
        start = i + 1


def is_namespace_component(comp: str) -> bool:
    # HAL's convention: namespaces are lowercase, types are UpperCamelCase
    return comp[:1].islower() and "<" not in comp and "@" not in comp


# Namespaces that belong to libraries rather than to a game source directory
FOREIGN_NAMESPACES = frozenset(("nw4r", "std"))

# Directory inference weights
DIR_STRONG = 6.0  # a symbol of a class named after the file, or in its anonymous namespace
DIR_WEAK = 1.0  # any other symbol
DIR_SWITCH = 3.0  # cost of changing directory between neighbours
DIR_DESCEND = 2.5  # ... when entering a subdirectory (files are linked before subdirectories)
DIR_UNSORTED = 12.0  # cost of staying in a directory while breaking its file order


def namespace_votes(unit: Unit) -> Tuple[Counter, Counter]:
    """Tallies the namespaces of the symbols a translation unit defines."""
    strong: Counter = Counter()
    weak: Counter = Counter()
    stem = unit.stem
    for contrib in unit.contribs.values():
        for sym in contrib.symbols:
            comps = symbol_qualifier(sym.name)
            if not comps:
                continue
            ns: List[str] = []
            rest = list(comps)
            while rest and is_namespace_component(rest[0]):
                ns.append(rest.pop(0))
            if ns and ns[0] in FOREIGN_NAMESPACES:
                continue
            owner = rest[0].split("<")[0] if rest else None
            anonymous = any(c.startswith("@unnamed@") for c in comps)
            if anonymous and not ns:
                # Anonymous namespace at file scope: says nothing about the directory
                continue
            if owner == stem or anonymous:
                strong["/".join(ns)] += 1
            else:
                weak["/".join(ns)] += 1
    return strong, weak


def sort_key(stem: str) -> str:
    # Objects are linked in file name order within a directory, compared the
    # way NTFS orders directory entries (case folded to upper case).
    return stem.upper()


def infer_directories(units: List[Unit]) -> List[str]:
    """
    Labels every translation unit with a source directory.

    The game is linked one directory at a time, files sorted by name, and its
    namespaces mirror its directories. Each unit votes with the namespaces of
    its symbols; a Viterbi pass then picks the labelling that best agrees with
    the votes while keeping directories contiguous and sorted.
    """
    count = len(units)
    votes = [namespace_votes(u) for u in units]

    def emission(i: int, directory: str) -> float:
        strong, weak = votes[i]
        score = 0.0
        if strong[directory]:
            score += DIR_STRONG + min(strong[directory], 8) * 0.5
        if weak[directory]:
            score += DIR_WEAK + min(weak[directory], 8) * 0.25
        return score

    def top(i: int) -> List[str]:
        return [d for d, _ in votes[i][0].most_common(2)]

    # Candidate directories: a unit's own, plus those of the nearest
    # neighbours with strong evidence (so that units without it can inherit),
    # plus the parents of what follows (files are linked before subdirectories).
    forward: List[List[str]] = []
    for i in range(count):
        own = top(i)
        forward.append(own if own else (forward[i - 1] if i else []))
    backward: List[List[str]] = [[] for _ in range(count)]
    for i in range(count - 1, -1, -1):
        own = top(i)
        backward[i] = own if own else (backward[i + 1] if i + 1 < count else [])
    states: List[List[str]] = []
    for i in range(count):
        strong, weak = votes[i]
        cands = dict.fromkeys(list(strong) + list(weak))
        if i:
            cands.update(dict.fromkeys(forward[i - 1]))
        if i + 1 < count:
            cands.update(dict.fromkeys(backward[i + 1]))
            cands.update(dict.fromkeys(d.rpartition("/")[0] for d in backward[i + 1]))
        if not cands:
            cands[""] = None
        states.append(list(cands))

    keys = [sort_key(u.stem) for u in units]
    banned: List[set] = [set() for _ in range(count)]

    def label() -> List[str]:
        best: List[Dict[str, float]] = []
        back: List[Dict[str, Optional[str]]] = []
        for i in range(count):
            scores: Dict[str, float] = {}
            links: Dict[str, Optional[str]] = {}
            for d in [s for s in states[i] if s not in banned[i]] or [""]:
                e = emission(i, d)
                if i == 0:
                    scores[d] = e
                    links[d] = None
                    continue
                choice = None
                choice_score = float("-inf")
                for p, p_score in best[i - 1].items():
                    if p == d:
                        cost = 0.0 if keys[i - 1] < keys[i] else DIR_UNSORTED
                    elif p == "" or d.startswith(p + "/"):
                        cost = DIR_DESCEND
                    else:
                        cost = DIR_SWITCH
                    total = p_score - cost
                    # Ties favour changing directory as late as possible
                    if total > choice_score or (total == choice_score and p != d):
                        choice_score = total
                        choice = p
                scores[d] = choice_score + e
                links[d] = choice
            best.append(scores)
            back.append(links)

        labels = [""] * count
        current: Optional[str] = max(best[-1], key=lambda d: best[-1][d])
        for i in range(count - 1, -1, -1):
            assert current is not None
            labels[i] = current
            current = back[i][current]
        return labels

    def find_runs(labels: List[str]) -> List[Tuple[int, int]]:
        runs: List[Tuple[int, int]] = []  # [start, end)
        for i in range(count):
            if runs and labels[runs[-1][0]] == labels[i]:
                runs[-1] = (runs[-1][0], i + 1)
            else:
                runs.append((i, i + 1))
        return runs

    while True:
        result = label()

        # A directory is linked in one go. Units that interrupt a directory
        # without disturbing its file order live in it too, whatever their
        # namespace says.
        runs = find_runs(result)
        for r in range(1, len(runs) - 1):
            start, end = runs[r]
            outer = result[runs[r - 1][0]]
            if outer != result[runs[r + 1][0]] or outer == result[start]:
                continue
            if all(keys[i - 1] < keys[i] for i in range(start, end + 1)):
                for i in range(start, end):
                    result[i] = outer

        # Where a directory still shows up more than once, keep the run that
        # has the most going for it and label again without the others.
        by_dir: Dict[str, List[Tuple[int, int]]] = defaultdict(list)
        for start, end in find_runs(result):
            by_dir[result[start]].append((start, end))
        changed = False
        for directory, dir_runs in by_dir.items():
            if len(dir_runs) < 2:
                continue
            keep = max(dir_runs, key=lambda r: (sum(emission(i, directory) for i in range(*r)), r[1] - r[0], -r[0]))
            for run in dir_runs:
                if run != keep:
                    for i in range(*run):
                        banned[i].add(directory)
                        changed = True
        if not changed:
            return result


# Library name -> directory. Anything else in <name>.a form is an SDK library.
LIBRARY_DIRS = {
    "Runtime.PPCEABI.H.a": "Runtime",
    "MSL_C.PPCEABI.bare.H.a": "MSL_C",
    "MSL_C++.PPCEABI.bare.H.a": "MSL_C++",
    "TRK_Hollywood_Revolution.a": "MetroTRK",
    "homebuttonLib.a": "homebuttonLib",
    "nrel.a": "nrel",
    "libMobiclip.a": "Mobiclip",
    "libms.a": "libms",
}
# Objects linked directly, outside of any library
LOOSE_OBJECT_DIRS = {
    "snd_adpcm.o": "nw4r/snd",
}
# Top-level directories of everything that is not game code
LIBRARY_ROOTS = frozenset(
    ("Runtime", "MSL_C", "MSL_C++", "MetroTRK", "RVL_SDK", "nw4r", "homebuttonLib", "nrel", "Mobiclip", "libms")
)


def is_library_unit(name: str) -> bool:
    return name.split("/", 1)[0] in LIBRARY_ROOTS
# Path prefixes (as recorded by the original build machines) to strip
BUILD_PATH_MARKERS = (
    "\\PowerPC_EABI_Support\\MSL\\",
    "\\metrotrk\\metrotrk\\",
)
RUNTIME_CPP = frozenset(("New", "NMWException", "Gecko_ExceptionPPC", "__init_cpp_exceptions"))
SDK_CPP = frozenset(("__ppc_eabi_init",))
ASSEMBLY = frozenset(("__exception", "targsupp"))
HBM_NW4R_PREFIXES = ("lyt_", "ut_", "math_", "db_", "snd_")
HBM_SOUND = frozenset(("mix", "seq", "syn", "synctrl", "synenv", "synmix", "synpitch", "synsample", "synvoice"))

MANGLED_RE = re.compile(r"[^_]__(?:Q\d|C?F[A-Za-z]|\d+[A-Za-z_])")


def has_cpp_symbols(unit: Unit) -> bool:
    for contrib in unit.contribs.values():
        for sym in contrib.symbols:
            if sym.name.startswith("__sinit_") or "@unnamed@" in sym.name or MANGLED_RE.search(sym.name):
                return True
    return False


def library_unit_name(unit: Unit) -> str:
    lib, obj = unit.lib, unit.obj
    stem = unit.stem
    cpp = has_cpp_symbols(unit)
    if lib == "":
        directory = LOOSE_OBJECT_DIRS.get(obj, "")
        ext = ".cpp" if cpp or directory.startswith("nw4r/") else ".c"
        return f"{directory}/{stem}{ext}" if directory else stem + ext

    if lib in ("MSL_C.PPCEABI.bare.H.a", "MSL_C++.PPCEABI.bare.H.a", "TRK_Hollywood_Revolution.a"):
        rel = obj
        for marker in BUILD_PATH_MARKERS:
            i = rel.find(marker)
            if i != -1:
                rel = rel[i + len(marker) :]
        rel = rel.replace("\\", "/")
        rel = rel[:-2] if rel.endswith(".o") else rel
        if lib == "TRK_Hollywood_Revolution.a":
            ext = ".s" if stem in ASSEMBLY else ".c"
            return f"MetroTRK/{rel}{ext}"
        return rel + (".cpp" if lib.startswith("MSL_C++") else ".c")

    if lib == "Runtime.PPCEABI.H.a":
        return f"Runtime/{stem}{'.cpp' if stem in RUNTIME_CPP else '.c'}"
    if lib == "homebuttonLib.a":
        if stem.startswith(HBM_NW4R_PREFIXES):
            return f"homebuttonLib/nw4hbm/{stem.split('_', 1)[0]}/{stem}.cpp"
        if stem in HBM_SOUND:
            return f"homebuttonLib/sound/{stem}{'.cpp' if cpp else '.c'}"
        return f"homebuttonLib/{stem}{'.cpp' if cpp else '.c'}"
    if lib in LIBRARY_DIRS:
        return f"{LIBRARY_DIRS[lib]}/{stem}{'.cpp' if cpp else '.c'}"
    if lib.startswith("libnw4r_") and lib.endswith(".a"):
        return f"nw4r/{lib[len('libnw4r_'):-2]}/{stem}.cpp"
    if lib.endswith(".a"):
        return f"RVL_SDK/{lib[:-2]}/{stem}{'.cpp' if stem in SDK_CPP else '.c'}"
    raise ValueError(f"Don't know how to name {lib} {obj}")


def name_units(game_units: List[Unit], library_units: List[Unit], renamed: List[str]) -> List[str]:
    """Names all units. Returns the inferred directory of each game unit."""
    for unit in library_units:
        unit.name = library_unit_name(unit)

    directories = infer_directories(game_units)
    used: Dict[str, Unit] = {u.name.lower(): u for u in library_units}
    if len(used) != len(library_units):
        raise ValueError("Library unit names are not unique")
    for unit, directory in zip(game_units, directories):
        # Everything in the game library is C++, bar a few plain C sources
        has_symbols = any(c.symbols for c in unit.contribs.values())
        ext = ".c" if has_symbols and not has_cpp_symbols(unit) and unit.stem != "Main" else ".cpp"
        base = f"{directory}/{unit.stem}" if directory else unit.stem
        name = base + ext
        n = 2
        while name.lower() in used:
            name = f"{base}_{n}{ext}"
            n += 1
        if n > 2:
            renamed.append(f"{name}: directory could not be told apart from {base}{ext}")
        unit.name = name
        used[name.lower()] = unit
    return directories


def build_library_units(map_file: MapFile) -> List[Unit]:
    """Units of everything but the game library; object names are unique there."""
    units: Dict[Tuple[str, str], Unit] = {}
    for section, contribs in map_file.layout.items():
        for c in contribs:
            if c.lib == GAME_LIB or c.obj == LINKER_GENERATED:
                continue
            unit = units.get(c.key)
            if unit is None:
                unit = units[c.key] = Unit(c.lib, c.obj)
            if section in unit.contribs:
                # .dtors$10 and .dtors$15 of __init_cpp_exceptions.o
                if not (c.header and "$" in c.header[0]):
                    raise ValueError(f"{c.lib} {c.obj} appears twice in {section}")
                c.unit = unit
                continue
            unit.add(c)
    return list(units.values())


###
# Output
###


def write_map(map_file: MapFile, path: Path) -> Tuple[int, int]:
    """
    Writes the cleaned map. Returns the number of contributions written and
    the number of empty ones that were left out.
    """
    written = skipped = 0
    out: List[str] = [map_file.entry_line, ""]
    for section, contribs in map_file.layout.items():
        if not contribs:
            continue
        out.append("")
        out.append(f"{section} section layout")
        out.append("  Starting        Virtual  File")
        out.append("  address  Size   address  offset")
        out.append("  ---------------------------------")
        for c in contribs:
            if c.obj == LINKER_GENERATED:
                unit_name = LINKER_GENERATED
            else:
                assert c.unit is not None and c.unit.name
                unit_name = c.unit.name
                if c.size == 0 and not c.symbols:
                    # Objects whose code was stripped or merged away entirely
                    skipped += 1
                    continue
                written += 1
            if c.header is not None:
                name, align, fields = c.header
                if c.obj != LINKER_GENERATED:
                    # decomp-toolkit expects a plain section name here.
                    # (.ctors$10 and friends are restored as renames in splits.txt.)
                    name = section
                out.append("  %s %s %s %s %2s %s \t%s" % (*fields, align or "", name, unit_name))
            for sym in c.symbols:
                name = sym.name
                if sym.entry_of is not None:
                    name = f"{name} (entry of {sym.entry_of})"
                out.append("  %s %s %s %s %2s %s \t%s" % (*sym.fields, sym.align or "", name, unit_name))
        out.append("")
    out.append("")
    out.extend(map_file.tail)
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="latin-1", newline="\n") as f:
        f.write("\n".join(out))
    return written, skipped


def write_report(
    path: Path,
    game_units: List[Unit],
    library_units: List[Unit],
    directories: List[str],
    stats: Counter,
    notes: List[MatchNote],
    renamed: List[str],
) -> None:
    lines: List[str] = []
    lines.append("# Translation units reconstructed from the link map, in link order.")
    lines.append("# <unit name> <- <library> <object> [sections]. Units marked (empty) left no code or data.")
    lines.append("")
    lines.append("## Matching of game object sections")
    for key in sorted(stats):
        lines.append(f"{key:<50} {stats[key]}")
    lines.append("")
    if notes:
        lines.append("## Sections assigned on thin evidence")
        for note in notes:
            c = note.contrib
            assert c.unit is not None
            where = f"{c.unit.name}: {c.section} @ {c.addr:08X}"
            if note.passed_over is not None:
                lines.append(f"{where}, though {note.passed_over.name} references it more (link order rules that one out)")
            else:
                lines.append(f"{where}, by object name and link order alone")
        lines.append("")
    if renamed:
        lines.append("## Units renamed to stay unique")
        lines.extend(renamed)
        lines.append("")
    without_evidence = []
    for unit, directory in zip(game_units, directories):
        strong, weak = namespace_votes(unit)
        if not strong[directory] and not weak[directory]:
            without_evidence.append(unit.name)
    lines.append("## Game units whose directory was inferred from their neighbours alone")
    lines.extend(without_evidence)
    lines.append("")

    def describe(unit: Unit) -> str:
        sections = " ".join(f"{s}:{c.addr:08X}+{c.size:X}" for s, c in unit.contribs.items() if c.size or c.symbols)
        source = f"{unit.lib} {unit.obj}".strip()
        return f"{unit.name:<64} <- {source}  [{sections or '(empty)'}]"

    lines.append("## Libraries")
    for unit in library_units:
        lines.append(describe(unit))
    lines.append("")
    lines.append(f"## Game ({GAME_LIB})")
    for unit in game_units:
        lines.append(describe(unit))
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")


def prepare(map_path: Path, dol_path: Path, output: Path, report: Optional[Path] = None) -> None:
    """Writes the cleaned map (and optionally the unit report) for a link map and its DOL."""
    map_file = parse_map(map_path)
    for name in ("_SDA_BASE_", "_SDA2_BASE_"):
        if name not in map_file.linker_symbols:
            sys.exit(f"{map_path}: missing linker generated symbol {name}")
    dol = Dol(dol_path)

    refs = analyze_references(map_file, dol)
    stats: Counter = Counter()
    notes: List[MatchNote] = []
    renamed: List[str] = []
    game_units = build_units(map_file, refs, stats, notes)
    library_units = build_library_units(map_file)
    directories = name_units(game_units, library_units, renamed)

    written, skipped = write_map(map_file, output)
    if report:
        write_report(report, game_units, library_units, directories, stats, notes, renamed)

    print(f"{len(library_units)} library units, {len(game_units)} game units in {len(set(directories))} directories")
    print(f"{written} section contributions written, {skipped} empty ones dropped")
    if notes:
        print(f"{len(notes)} sections assigned on thin evidence" + (f", see {report}" if report else ""))
    if renamed:
        print(f"{len(renamed)} unit names needed a suffix to stay unique")
    print(f"Wrote {output}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Prepares iuk.MAP for decomp-toolkit.")
    parser.add_argument("map", type=Path, help="original link map (files/iuk.MAP)")
    parser.add_argument("dol", type=Path, help="original executable (sys/main.dol)")
    parser.add_argument("-o", "--output", type=Path, required=True, help="cleaned map to write")
    parser.add_argument("--report", type=Path, help="write the reconstructed unit list here")
    args = parser.parse_args()
    prepare(args.map, args.dol, args.output, args.report)


if __name__ == "__main__":
    main()
