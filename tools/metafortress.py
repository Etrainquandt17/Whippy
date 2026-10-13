#!/usr/bin/env python3

###
# Finds and examines the MetaFortress protection in a build of the game.
#
# MetaFortress is an anti-tamper product that rewrites selected source files
# before they are compiled. A protected function carries data in the middle of
# its instructions, reached with
#
#     bl      skip        ; lr = address of the data
#     .4byte  ...
#   skip:
#     mflr    rX
#
# and uses it to checksum other code, to probe the console, or to keep a set of
# hidden variables consistent. See docs/metafortress.md.
#
# Nothing here is specific to one check: each protected function is run in a
# small PowerPC interpreter that follows every path, tracks which values come
# from inline data, and reports what the function does with them.
#
# Usage:
#   python tools/metafortress.py SUKE01                   # summary
#   python tools/metafortress.py SUKE01 --list            # one line per finding
#   python tools/metafortress.py SUKE01 --json out.json
#   python tools/metafortress.py SUKE01 --yaml            # block_relocations for config.yml
#   python tools/metafortress.py SUKE01 --verify mod.dol  # which checksums fail in mod.dol
#   python tools/metafortress.py SUKE01 --seal mod.dol out.dol
#   python tools/metafortress.py SUKE01 --words out.h     # inline data as macros, for the build
#   python tools/metafortress.py SUKE01 --source SYMBOL   # a protected function as a starting point for its source
#
# --verify and --seal expect a DOL with the layout of the original: bytes may
# differ, addresses may not.
###

import argparse
import bisect
import json
import multiprocessing
import re
import struct
import sys
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Sequence, Set, Tuple

# Largest run of inline data to accept. The biggest one in the retail game is 152 bytes.
MAX_BLOB_SIZE = 0x100

MASK = 0xFFFFFFFF
UNKNOWN, INLINE, CHECKED, RESULT = 1, 2, 4, 8
STACK_LOW, STACK_TOP, STACK_HIGH = 0x7E000000, 0x7F000000, 0x7F100000
LOW_MEMORY_END = 0x80003F00
# Bus and CPU clock speed, which ordinary timing code reads.
OS_CLOCK_WORDS = (0x800000F8, 0x800000FC)
MAX_STEPS = 30_000_000
RESPONSE = "MFortressDefaultResponseVariant_1"

Function = Tuple[int, int, str]


def text_sections(data: bytes) -> List[Tuple[int, int, int]]:
    """Returns (address, size, file offset) of each text section of a DOL."""
    offsets = struct.unpack_from(">7I", data, 0x00)
    addresses = struct.unpack_from(">7I", data, 0x48)
    sizes = struct.unpack_from(">7I", data, 0x90)
    return [(addresses[i], sizes[i], offsets[i]) for i in range(7) if sizes[i]]


def _branch_target(word: int, index: int) -> int:
    displacement = word & 0x03FFFFFC
    if displacement & 0x02000000:
        displacement -= 0x04000000
    return index + displacement // 4


def _ends_function(word: int) -> bool:
    return word in (0x4E800020, 0x4E800420, 0) or (word >> 26 == 18 and not word & 1)


def find_inline_data(data: bytes) -> List[Tuple[int, int]]:
    """Returns the [start, end) address range of each run of inline data, from the DOL alone."""
    blobs: List[Tuple[int, int]] = []
    for address, size, offset in text_sections(data):
        words = struct.unpack_from(f">{size // 4}I", data, offset)
        for i, word in enumerate(words):
            if word >> 26 != 18 or word & 3 != 1:
                continue
            target = _branch_target(word, i)
            if not i + 2 <= target <= i + 1 + MAX_BLOB_SIZE // 4 or target >= len(words):
                continue
            # A call skips the data and lands on mflr. Three runs are skipped without
            # being read at all; those are told from a call to a nearby function by
            # what precedes the target.
            if words[target] & 0xFC1FFFFF == 0x7C0802A6 or not _ends_function(words[target - 1]):
                blobs.append((address + i * 4 + 4, address + target * 4))
    return blobs


def find_skips(start: int, words: Sequence[int]) -> List[Tuple[int, int]]:
    """Returns the inline data of one function: whatever a call into the function itself jumps over."""
    found = []
    for i, word in enumerate(words):
        if word >> 26 == 18 and word & 3 == 1:
            target = _branch_target(word, i)
            if i < target < len(words):
                found.append((start + i * 4 + 4, start + target * 4))
    return found


class Dol:
    def __init__(self, data: bytes) -> None:
        self.data = bytearray(data)
        offsets = struct.unpack_from(">18I", data, 0x00)
        addresses = struct.unpack_from(">18I", data, 0x48)
        sizes = struct.unpack_from(">18I", data, 0x90)
        self.sections = sorted((a, s, o, i < 7) for i, (o, a, s) in enumerate(zip(offsets, addresses, sizes)) if s)
        self._starts = [s[0] for s in self.sections]

    def find(self, address: int) -> Tuple[Optional[int], bool]:
        """Returns the file offset of an address and whether it is in a text section."""
        i = bisect.bisect_right(self._starts, address) - 1
        if i >= 0:
            start, size, offset, text = self.sections[i]
            if address < start + size:
                return offset + address - start, text
        return None, False

    def write32(self, address: int, value: int) -> None:
        offset, _ = self.find(address)
        assert offset is not None, hex(address)
        struct.pack_into(">I", self.data, offset, value)


class Symbols:
    def __init__(self, path: Path) -> None:
        self.functions: List[Function] = []
        self.address: Dict[str, int] = {}
        self.hidden: List[Tuple[int, int, str]] = []
        for line in path.read_text(encoding="utf-8").splitlines():
            m = re.match(r"(\S+) = \.(\w+):0x([0-9A-F]+); // type:(\w+)(?: size:0x([0-9A-F]+))?", line)
            if not m:
                continue
            name, address, size = m.group(1), int(m.group(3), 16), int(m.group(5) or "0", 16)
            self.address.setdefault(name, address)
            if m.group(4) == "function" and m.group(2) in ("text", "init"):
                self.functions.append((address, size, name))
            elif name.startswith("dcpl_") and "_mfort" in name:
                self.hidden.append((address, size, name))
        self.functions.sort()

    def hidden_at(self, address: int) -> Optional[str]:
        for start, size, name in self.hidden:
            if start <= address < start + size:
                return name
        return None


def _signed16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


def _signed32(value: int) -> int:
    return value - 0x100000000 if value & 0x80000000 else value


def _mask(begin: int, end: int) -> int:
    bits = (MASK >> begin) ^ ((MASK >> end) >> 1)
    return bits if begin <= end else ~bits & MASK


def _rotate(value: int, count: int) -> int:
    count &= 31
    return ((value << count) | (value >> (32 - count))) & MASK if count else value


def _sign_cr(value: int) -> int:
    return 2 if value == 0 else 8 if value & 0x80000000 else 4


class _State:
    __slots__ = ("r", "t", "o", "cr", "crt", "lr", "lrt", "lro", "ctr", "ctrt", "ca", "cat", "mem", "memo", "pc", "path", "forced", "site")

    @staticmethod
    def at(pc: int, stack: int) -> "_State":
        st = _State()
        st.r, st.t, st.o = [0] * 32, [UNKNOWN] * 32, [0] * 32
        st.r[1], st.t[1] = stack, 0
        st.cr, st.crt = [0] * 8, [UNKNOWN] * 8
        st.lr, st.lrt, st.lro = 0, UNKNOWN, 0
        st.ctr, st.ctrt, st.ca, st.cat = 0, UNKNOWN, 0, UNKNOWN
        st.mem, st.memo = {}, {}
        st.pc, st.path, st.forced, st.site = pc, 0, False, 0
        return st

    def copy(self) -> "_State":
        st = _State()
        st.r, st.t, st.o = self.r[:], self.t[:], self.o[:]
        st.cr, st.crt = self.cr[:], self.crt[:]
        st.lr, st.lrt, st.lro = self.lr, self.lrt, self.lro
        st.ctr, st.ctrt, st.ca, st.cat = self.ctr, self.ctrt, self.ca, self.cat
        st.mem, st.memo = dict(self.mem), dict(self.memo)
        st.pc, st.path, st.forced, st.site = self.pc, self.path, self.forced, self.site
        return st


_LOGIC = {28: "and", 60: "andc", 124: "nor", 284: "eqv", 316: "xor", 412: "orc", 476: "nand"}
_INDEXED_LOADS = {23: (4, False), 55: (4, True), 87: (1, False), 119: (1, True), 279: (2, False), 311: (2, True), 343: (2, False), 375: (2, True), 534: (4, False), 790: (2, False)}
_INDEXED_STORES = {151: (4, False), 183: (4, True), 215: (1, False), 247: (1, True), 407: (2, False), 439: (2, True), 662: (4, False), 918: (2, False)}
_NO_EFFECT = {535, 599, 663, 727, 983, 1014, 86, 54, 278, 246, 470, 982, 598, 854, 4, 146, 512, 210}
_VOLATILE = (0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)


class Explorer:
    """Runs one function along every path and records what it does with its inline data.

    Each register and stack byte carries a value and a set of flags: UNKNOWN
    (depends on something outside the function), INLINE (derived from inline
    data), CHECKED (read through an address that was derived from inline data)
    and RESULT (a comparison of a CHECKED value with an INLINE one). A branch
    on an UNKNOWN condition is followed both ways, once per target.
    """

    def __init__(self, dol: Dol, function: Function, symbols: Symbols) -> None:
        self.dol = dol
        self.start, self.size, self.name = function
        self.end = self.start + self.size
        offset, _ = dol.find(self.start)
        self.words = struct.unpack_from(f">{self.size // 4}I", dol.data, offset)
        self.blobs = find_skips(self.start, self.words)
        self.blob_at_call = {blob[0] - 4: blob for blob in self.blobs}
        self.blob_starts = [blob[0] for blob in self.blobs]
        save = symbols.address.get("__save_gpr", 0)
        restore = symbols.address.get("__restore_gpr", 0)
        self.save = range(save, save + 0x4C)
        self.restore = range(restore, restore + 0x4C)
        self.ios_open = symbols.address.get("IOS_Open")
        self.owner: Dict[int, int] = {}
        self.revisits: Dict[int, int] = {}
        self.paths = 1
        self.steps = 0
        self.reads: Dict[int, List[int]] = {}
        self.compares: Dict[int, Tuple[str, int, int, int, int]] = {}
        self.jumps: Dict[int, Tuple[int, bool]] = {}
        self.accesses: Set[Tuple[int, int, bool]] = set()
        self.low_memory: Set[int] = set()
        self.probes: Dict[int, str] = {}
        self.uses: Set[str] = set()
        self.spins: Set[int] = set()
        self.used_inline: Set[int] = set()
        self.notes: List[str] = []

    def run(self) -> "Explorer":
        self._explore(_State.at(self.start, STACK_TOP))
        for call in sorted(self.blob_at_call):
            if call in self.owner:
                continue
            # Reached only through a jump table. Start at the top of its block, where
            # a checksum's first value may be set.
            pc = call
            while pc > self.start and pc - 4 not in self.owner and not self._in_blob(pc - 4) and not _ends_function(self.words[(pc - 4 - self.start) >> 2]):
                pc -= 4
            st = _State.at(pc, STACK_TOP - 0x1000)
            st.path = self.paths
            self.paths += 1
            self._explore(st)
        return self

    def _explore(self, first: _State) -> None:
        pending = [first]
        while pending:
            self._follow(pending.pop(), pending)

    def _in_blob(self, address: int) -> bool:
        i = bisect.bisect_right(self.blob_starts, address) - 1
        return i >= 0 and address < self.blobs[i][1]

    def _spawn(self, st: _State, pc: int, pending: List[_State], forced: bool) -> None:
        if pc in self.owner or not self.start <= pc < self.end:
            return
        other = st.copy()
        other.pc, other.path, other.forced = pc, self.paths, st.forced or forced
        self.paths += 1
        pending.append(other)

    def _load(self, st: _State, ea: int, eat: int, size: int, base_origin: int, signed: bool = False) -> Tuple[int, int, int]:
        if eat & UNKNOWN:
            return 0, UNKNOWN, 0
        mem = st.mem
        if ea in mem or STACK_LOW <= ea < STACK_HIGH:
            value, taint = 0, 0
            for i in range(size):
                byte = mem.get(ea + i)
                if byte is None:
                    return 0, UNKNOWN, 0
                value = (value << 8) | byte[0]
                taint |= byte[1]
            origin = st.memo.get(ea, 0) if size == 4 else 0
        else:
            offset, text = self.dol.find(ea)
            if offset is None or offset + size > len(self.dol.data):
                if 0x80000000 <= ea < LOW_MEMORY_END and ea not in OS_CLOCK_WORDS:
                    self.low_memory.add(ea)
                return 0, UNKNOWN, 0
            value = int.from_bytes(self.dol.data[offset : offset + size], "big")
            origin = 0
            if text and base_origin < 0 and size == 4 and -base_origin <= ea and self._in_blob(ea):
                taint, origin = INLINE, ea
                self.used_inline.add(ea)
            elif eat & INLINE:
                taint = CHECKED | eat
                st.site = st.pc
                seen = self.reads.get(st.pc)
                if seen is None:
                    self.reads[st.pc] = [ea, ea + size, 1]
                else:
                    seen[0] = min(seen[0], ea)
                    seen[1] = max(seen[1], ea + size)
                    seen[2] += 1
            else:
                taint = eat
        if signed and value & (1 << (size * 8 - 1)):
            value = (value - (1 << (size * 8))) & MASK
        return value, taint, origin

    def _store(self, st: _State, ea: int, eat: int, size: int, value: int, taint: int, origin: int) -> None:
        if eat & UNKNOWN:
            if taint & RESULT and not taint & UNKNOWN:
                self.uses.add("store")
            return
        if eat & INLINE and not STACK_LOW <= ea < STACK_HIGH:
            self.accesses.add((st.pc, ea, True))
        mem = st.mem
        for i in range(size):
            mem[ea + i] = ((value >> (8 * (size - 1 - i))) & 0xFF, taint)
        for address in range(ea - 3, ea + size):
            st.memo.pop(address, None)
        if size == 4 and origin:
            st.memo[ea] = origin

    def _compare(self, st: _State, name: str, a: int, ta: int, oa: int, b: int, tb: int, ob: int) -> int:
        """Notes an operation that combines a checked value with one from inline data."""
        if (ta | tb) & UNKNOWN:
            return 0
        if ta & CHECKED and not tb & CHECKED and tb & INLINE:
            computed, stored, origin = a, b, ob
        elif tb & CHECKED and not ta & CHECKED and ta & INLINE:
            computed, stored, origin = b, a, oa
        else:
            return 0
        self.compares[st.pc] = (name, computed, stored, origin, st.site)
        return RESULT

    def _call(self, st: _State, pc: int, target: Optional[int]) -> None:
        r, t, o = st.r, st.t, st.o
        if any(t[i] & RESULT and not t[i] & UNKNOWN for i in range(3, 11)):
            self.uses.add("argument")
        if target is not None and target == self.ios_open and not t[3] & UNKNOWN:
            chars = []
            for i in range(64):
                byte = st.mem.get(r[3] + i)
                if byte is None or byte[1] & UNKNOWN or not byte[0]:
                    break
                chars.append(byte[0])
            if chars:
                self.probes[pc] = bytes(chars).decode("ascii", "replace")
        if target in self.save:
            return
        for i in _VOLATILE:
            t[i], o[i] = UNKNOWN, 0
        for i in (0, 1, 5, 6, 7):
            st.crt[i] = UNKNOWN
        st.ctrt = st.cat = UNKNOWN
        st.lr, st.lrt, st.lro = pc + 4, UNKNOWN, 0
        if target in self.restore:
            for i in range(14, 32):
                t[i], o[i] = UNKNOWN, 0

    def _follow(self, st: _State, pending: List[_State]) -> None:
        r, t, o = st.r, st.t, st.o
        cr, crt = st.cr, st.crt
        owner, words, start, end = self.owner, self.words, self.start, self.end
        while True:
            pc = st.pc
            if not start <= pc < end:
                return
            mine = owner.get(pc)
            if mine is None:
                owner[pc] = st.path
            elif mine != st.path:
                return
            self.steps += 1
            if self.steps > MAX_STEPS:
                self.notes.append(f"gave up at {pc:08X}")
                return
            w = words[(pc - start) >> 2]
            op, d, a, b = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
            npc = pc + 4

            if op == 14 or op == 15:
                imm = _signed16(w & 0xFFFF) if op == 14 else (w & 0xFFFF) << 16
                if a:
                    r[d], t[d], o[d] = (r[a] + imm) & MASK, t[a], 0
                else:
                    r[d], t[d], o[d] = imm & MASK, 0, 0
            elif 32 <= op <= 45:
                update, kind = op & 1, (op - 32) >> 1
                disp = _signed16(w & 0xFFFF)
                if a or update:
                    ea, eat, base = (r[a] + disp) & MASK, t[a], o[a]
                else:
                    ea, eat, base = disp & MASK, 0, 0
                if kind == 0:
                    r[d], t[d], o[d] = self._load(st, ea, eat, 4, base)
                elif kind == 1:
                    r[d], t[d], o[d] = self._load(st, ea, eat, 1, base)
                elif kind == 2:
                    self._store(st, ea, eat, 4, r[d], t[d], o[d])
                elif kind == 3:
                    self._store(st, ea, eat, 1, r[d] & 0xFF, t[d], 0)
                elif kind == 4:
                    r[d], t[d], o[d] = self._load(st, ea, eat, 2, base)
                elif kind == 5:
                    r[d], t[d], o[d] = self._load(st, ea, eat, 2, base, True)
                else:
                    self._store(st, ea, eat, 2, r[d] & 0xFFFF, t[d], 0)
                if update:
                    r[a], o[a] = ea, 0
            elif op == 31:
                if not self._extended(st, w, d, a, b):
                    self.notes.append(f"unknown instruction at {pc:08X}")
                    return
            elif op == 21 or op == 23:
                count = b if op == 21 else r[b] & 31
                value = _rotate(r[d], count) & _mask((w >> 6) & 31, (w >> 1) & 31)
                taint = t[d] if op == 21 else t[d] | t[b]
                r[a], t[a], o[a] = value, taint, 0
                if w & 1:
                    cr[0], crt[0] = _sign_cr(value), taint
            elif op == 20:
                bits = _mask((w >> 6) & 31, (w >> 1) & 31)
                value = (_rotate(r[d], b) & bits) | (r[a] & ~bits & MASK)
                taint = t[d] | t[a] | self._compare(st, "rlwimi", r[d], t[d], o[d], r[a], t[a], o[a])
                r[a], t[a], o[a] = value, taint, 0
                if w & 1:
                    cr[0], crt[0] = _sign_cr(value), taint
            elif op == 18:
                target = (_branch_target(w, 0) * 4 + (0 if w & 2 else pc)) & MASK
                if not w & 1:
                    npc = target
                elif pc in self.blob_at_call:
                    st.lr, st.lrt, st.lro = npc, INLINE, -self.blob_at_call[pc][0]
                    npc = target
                else:
                    self._call(st, pc, target)
            elif op == 16 or (op == 19 and ((w >> 1) & 0x3FF) in (16, 528)):
                go = self._branch(st, w, d, a, pending)
                if go is None:
                    return
                if go:
                    continue
            elif op == 19:
                xo = (w >> 1) & 0x3FF
                if xo == 0:
                    cr[d >> 2], crt[d >> 2] = cr[a >> 2], crt[a >> 2]
                elif xo in (33, 129, 193, 225, 257, 289, 417, 449):
                    x = (cr[a >> 2] >> (3 - (a & 3))) & 1
                    y = (cr[b >> 2] >> (3 - (b & 3))) & 1
                    bit = {33: 1 - (x | y), 129: x & (1 - y), 193: x ^ y, 225: 1 - (x & y), 257: x & y, 289: 1 - (x ^ y), 417: x | (1 - y), 449: x | y}[xo]
                    field, shift = d >> 2, 3 - (d & 3)
                    cr[field] = (cr[field] & ~(1 << shift)) | (bit << shift)
                    crt[field] |= crt[a >> 2] | crt[b >> 2]
                else:
                    self.notes.append(f"unknown instruction at {pc:08X}")
                    return
            elif op == 10 or op == 11:
                if op == 11:
                    x, y = _signed32(r[a]), _signed16(w & 0xFFFF)
                else:
                    x, y = r[a], w & 0xFFFF
                cr[d >> 2], crt[d >> 2] = (8 if x < y else 4 if x > y else 2), t[a]
            elif 24 <= op <= 29:
                imm = (w & 0xFFFF) << (16 if op & 1 else 0)
                if op <= 25:
                    value = r[d] | imm
                elif op <= 27:
                    value = r[d] ^ imm
                else:
                    value = r[d] & imm
                r[a], t[a], o[a] = value, t[d], o[d] if w == 0x60000000 | (w & 0x03FF0000) else 0
                if op >= 28:
                    cr[0], crt[0] = _sign_cr(value), t[d]
            elif op == 7:
                r[d], t[d], o[d] = (r[a] * _signed16(w & 0xFFFF)) & MASK, t[a], 0
            elif op == 8:
                imm = _signed16(w & 0xFFFF) & MASK
                st.ca, st.cat = int(imm >= r[a]), t[a]
                r[d], t[d], o[d] = (imm - r[a]) & MASK, t[a], 0
            elif op == 12 or op == 13:
                full = r[a] + (_signed16(w & 0xFFFF) & MASK)
                r[d], t[d], o[d] = full & MASK, t[a], 0
                st.ca, st.cat = full >> 32, t[d]
                if op == 13:
                    cr[0], crt[0] = _sign_cr(full & MASK), t[d]
            elif op == 46 or op == 47:
                ea = ((r[a] if a else 0) + _signed16(w & 0xFFFF)) & MASK
                eat = t[a] if a else 0
                for i in range(d, 32):
                    if op == 46:
                        r[i], t[i], o[i] = self._load(st, ea, eat, 4, 0)
                    else:
                        self._store(st, ea, eat, 4, r[i], t[i], o[i])
                    ea += 4
            elif 48 <= op <= 55:
                if op & 1:
                    r[a], o[a] = (r[a] + _signed16(w & 0xFFFF)) & MASK, 0
            elif op in (56, 57, 60, 61):
                if op & 1:
                    disp = w & 0xFFF
                    r[a], o[a] = (r[a] + (disp - 0x1000 if disp & 0x800 else disp)) & MASK, 0
            elif op == 59 or op == 63:
                if op == 63 and ((w >> 1) & 0x3FF) in (0, 32, 64):
                    crt[d >> 2] = UNKNOWN
                elif w & 1:
                    crt[1] = UNKNOWN
            elif op == 4:
                if ((w >> 1) & 0x3FF) in (0, 32, 64, 96):
                    crt[d >> 2] = UNKNOWN
                elif (w >> 1) & 0x3F in (38, 39):
                    r[a], t[a], o[a] = (r[a] + r[b]) & MASK, t[a] | t[b], 0
            else:
                self.notes.append(f"unknown instruction at {pc:08X}")
                return
            st.pc = npc

    def _branch(self, st: _State, w: int, bo: int, bi: int, pending: List[_State]) -> Optional[bool]:
        """Conditional branches and branches through LR or CTR. Returns None when the path ends."""
        pc, npc = st.pc, st.pc + 4
        cr, crt, owner = st.cr, st.crt, self.owner
        kind = "bc" if w >> 26 == 16 else "bclr" if (w >> 1) & 0x3FF == 16 else "bcctr"
        if kind == "bcctr" and w & 1:
            self._call(st, pc, None if st.ctrt & UNKNOWN else st.ctr)
            st.pc = npc
            return True
        taint, taken = 0, True
        if not bo & 4:
            st.ctr = (st.ctr - 1) & MASK
            taint |= st.ctrt
            taken = (st.ctr != 0) != bool(bo & 2)
        if not bo & 16:
            taint |= crt[bi >> 2]
            taken = taken and (cr[bi >> 2] >> (3 - (bi & 3))) & 1 == (bo >> 3) & 1
        target = None
        if kind == "bc":
            target = (_signed16(w & 0xFFFC) + (0 if w & 2 else pc)) & MASK
        inside = target is not None and self.start <= target < self.end

        if taint & UNKNOWN:
            if kind == "bclr":
                self._returned(st)
            if target is None:
                st.pc = npc
            elif npc not in owner:
                if inside and target not in owner:
                    self._spawn(st, target, pending, False)
                st.pc = npc
            elif inside and target not in owner:
                st.pc = target
            else:
                # Both sides were seen already. Go forward, so that a loop whose
                # condition is unknown is left and one with a known count still ends.
                seen = self.revisits.get(pc, 0)
                if seen >= 4096:
                    return None
                self.revisits[pc] = seen + 1
                st.pc = max(npc, target) if inside else npc
            return True

        if taint & (CHECKED | RESULT):
            if taint & RESULT:
                # A branch on the result that only leads back to the comparison
                # is a hang in place.
                if target is not None and pc - 12 <= target <= pc:
                    self.spins.add(pc)
                else:
                    self.uses.add("branch")
            other = npc if taken else target
            if other is not None:
                self._spawn(st, other, pending, True)
        if kind == "bc" and w & 1:
            st.lr, st.lrt, st.lro = npc, 0, 0
        if not taken:
            st.pc = npc
            return True
        if kind == "bclr":
            if st.lrt & INLINE and not st.lrt & UNKNOWN:
                self.jumps[pc] = (st.lr, st.forced)
                if self.start <= st.lr < self.end:
                    st.pc = st.lr
                    if w & 1:
                        st.lr, st.lrt, st.lro = npc, INLINE, 0
                    return True
                return None
            self._returned(st)
            return None
        if kind == "bcctr":
            st.pc = npc if st.ctrt & UNKNOWN else st.ctr
            return True
        st.pc = target
        return True

    def _returned(self, st: _State) -> None:
        if st.t[3] & RESULT and not st.t[3] & UNKNOWN:
            self.uses.add("return")

    def _extended(self, st: _State, w: int, d: int, a: int, b: int) -> bool:
        r, t, o = st.r, st.t, st.o
        xo, x9 = (w >> 1) & 0x3FF, (w >> 1) & 0x1FF
        value: Optional[int] = None
        taint = origin = 0
        target = d
        if xo == 444:
            target = a
            if d == b:
                value, taint, origin = r[d], t[d], o[d]
            else:
                value = r[d] | r[b]
                taint = t[d] | t[b] | self._compare(st, "or", r[d], t[d], o[d], r[b], t[b], o[b])
        elif xo == 339:
            spr = ((w >> 16) & 31) | ((w >> 6) & 0x3E0)
            if spr == 8:
                value, taint, origin = st.lr, st.lrt, st.lro
            elif spr == 9:
                value, taint = st.ctr, st.ctrt
            else:
                value, taint = 0, UNKNOWN
        elif xo == 467:
            spr = ((w >> 16) & 31) | ((w >> 6) & 0x3E0)
            if spr == 8:
                st.lr, st.lrt, st.lro = r[d], t[d], o[d]
            elif spr == 9:
                st.ctr, st.ctrt = r[d], t[d]
        elif x9 in (266, 40, 8, 10, 136, 138):
            name = {266: "add", 40: "subf", 8: "subfc", 10: "addc", 136: "subfe", 138: "adde"}[x9]
            taint = t[a] | t[b] | self._compare(st, name, r[a], t[a], o[a], r[b], t[b], o[b])
            if x9 == 266 or x9 == 10:
                full = r[a] + r[b]
            elif x9 == 40 or x9 == 8:
                full = (~r[a] & MASK) + r[b] + 1
            else:
                full = (r[a] if x9 == 138 else ~r[a] & MASK) + r[b] + st.ca
                taint |= st.cat
            value = full & MASK
            if x9 not in (266, 40):
                st.ca, st.cat = full >> 32, taint
        elif x9 in (200, 202, 232, 234):
            full = (r[a] if x9 in (202, 234) else ~r[a] & MASK) + st.ca + (MASK if x9 in (232, 234) else 0)
            value, taint = full & MASK, t[a] | st.cat
            st.ca, st.cat = full >> 32, taint
        elif x9 == 104:
            value, taint = (-r[a]) & MASK, t[a]
        elif x9 == 235:
            value = (r[a] * r[b]) & MASK
            taint = t[a] | t[b] | self._compare(st, "mullw", r[a], t[a], o[a], r[b], t[b], o[b])
        elif x9 == 75:
            value, taint = ((_signed32(r[a]) * _signed32(r[b])) >> 32) & MASK, t[a] | t[b]
        elif x9 == 11:
            value, taint = (r[a] * r[b]) >> 32, t[a] | t[b]
        elif x9 == 459:
            value, taint = (r[a] // r[b] if r[b] else 0), t[a] | t[b]
        elif x9 == 491:
            x, y = _signed32(r[a]), _signed32(r[b])
            value = (0 if y == 0 else abs(x) // abs(y) * (1 if (x < 0) == (y < 0) else -1)) & MASK
            taint = t[a] | t[b]
        elif xo in _LOGIC:
            x, y = r[d], r[b]
            value = {28: x & y, 60: x & ~y, 124: ~(x | y), 284: ~(x ^ y), 316: x ^ y, 412: x | ~y, 476: ~(x & y)}[xo] & MASK
            taint = t[d] | t[b] | self._compare(st, _LOGIC[xo], x, t[d], o[d], y, t[b], o[b])
            target = a
        elif xo == 24 or xo == 536:
            count = r[b] & 63
            value = 0 if count > 31 else (r[d] << count) & MASK if xo == 24 else r[d] >> count
            taint, target = t[d] | t[b], a
        elif xo == 792 or xo == 824:
            count = b if xo == 824 else r[b] & 63
            x = _signed32(r[d])
            value = (x >> min(count, 31)) & MASK
            taint, target = t[d] | (0 if xo == 824 else t[b]), a
            st.ca, st.cat = int(x < 0 and r[d] & ((1 << min(count, 32)) - 1) != 0), taint
        elif xo == 26:
            value, taint, target = 32 - r[d].bit_length(), t[d], a
        elif xo == 922:
            value, taint, target = _signed16(r[d] & 0xFFFF) & MASK, t[d], a
        elif xo == 954:
            x = r[d] & 0xFF
            value, taint, target = (x - 0x100 if x & 0x80 else x) & MASK, t[d], a
        elif xo == 0 or xo == 32:
            x, y = r[a], r[b]
            flags = t[a] | t[b] | self._compare(st, "cmp", x, t[a], o[a], y, t[b], o[b])
            if xo == 0:
                x, y = _signed32(x), _signed32(y)
            st.cr[d >> 2], st.crt[d >> 2] = (8 if x < y else 4 if x > y else 2), flags
        elif xo == 19:
            value = 0
            for i in range(8):
                value = (value << 4) | st.cr[i]
                taint |= st.crt[i]
        elif xo == 144:
            for i in range(8):
                if (w >> 12) & (0x80 >> i):
                    st.cr[i], st.crt[i] = (r[d] >> (28 - 4 * i)) & 15, t[d]
        elif xo in _INDEXED_LOADS:
            size, update = _INDEXED_LOADS[xo]
            ea, eat = ((r[a] + r[b]) & MASK, t[a] | t[b]) if a or update else (r[b], t[b])
            value, taint, origin = self._load(st, ea, eat, size, 0, xo in (343, 375))
            if xo in (534, 790):
                value = int.from_bytes(value.to_bytes(size, "big"), "little")
            if update:
                r[a], o[a] = ea, 0
        elif xo in _INDEXED_STORES:
            size, update = _INDEXED_STORES[xo]
            ea, eat = ((r[a] + r[b]) & MASK, t[a] | t[b]) if a or update else (r[b], t[b])
            out = r[d] & ((1 << (size * 8)) - 1)
            if xo in (662, 918):
                out = int.from_bytes(out.to_bytes(size, "big"), "little")
            self._store(st, ea, eat, size, out, t[d], o[d] if size == 4 else 0)
            if update:
                r[a], o[a] = ea, 0
        elif xo in (567, 631, 695, 759):
            r[a], t[a], o[a] = (r[a] + r[b]) & MASK, t[a] | t[b], 0
        elif xo == 83 or xo == 371:
            value, taint = 0, UNKNOWN
        elif xo not in _NO_EFFECT:
            return False
        if value is not None:
            r[target], t[target], o[target] = value, taint, origin
            if w & 1:
                st.cr[0], st.crt[0] = _sign_cr(value), taint
        return True


def examine(dol: Dol, function: Function, symbols: Symbols) -> Dict[str, Any]:
    """Runs one function and returns what its protection does."""
    ex = Explorer(dol, function, symbols).run()
    response = symbols.address.get(RESPONSE)
    checksums: Dict[int, Dict[str, Any]] = {}
    for pc, (name, computed, stored, origin, site) in sorted(ex.compares.items()):
        seen = ex.reads.get(site)
        if not origin or seen is None or seen[2] < 2:
            continue
        relation = "equal" if computed == stored else "inverse" if computed ^ stored == MASK else "broken"
        checksums.setdefault(origin, {"start": seen[0], "end": seen[1], "stored_at": origin, "stored": stored, "computed": computed, "relation": relation, "compare": pc})
    hidden = [{"at": pc, "address": ea, "write": write} for pc, ea, write in sorted(ex.accesses)]
    for pc, (low, high, count) in sorted(ex.reads.items()):
        if count == 1 and not dol.find(low)[1]:
            hidden.append({"at": pc, "address": low, "write": False})
    jumps = [{"at": pc, "target": target, "forced": forced} for pc, (target, forced) in sorted(ex.jumps.items()) if not ex.start <= target < ex.end]
    return {
        "address": function[0],
        "size": function[1],
        "name": function[2],
        "inline": ex.blobs,
        "used_inline": sorted(ex.used_inline),
        "checksums": sorted(checksums.values(), key=lambda c: c["stored_at"]),
        "hangs": sorted({j["at"] for j in jumps if j["target"] == response}),
        "wild_jumps": [j for j in jumps if j["target"] != response],
        "probes": [{"at": pc, "device": device} for pc, device in sorted(ex.probes.items())],
        "hidden": hidden,
        "low_memory": sorted(ex.low_memory),
        "uses": sorted(ex.uses),
        "spins": sorted(ex.spins),
        "notes": ex.notes,
    }


_worker: Dict[str, Any] = {}


def _start_worker(data: bytes, symbols_path: str) -> None:
    _worker["dol"] = Dol(data)
    _worker["symbols"] = Symbols(Path(symbols_path))


def _work(task: Tuple[Function, List[Tuple[int, int]]]) -> Dict[str, Any]:
    function, patches = task
    dol: Dol = _worker["dol"]
    for address, value in patches:
        dol.write32(address, value)
    return examine(dol, function, _worker["symbols"])


class Analysis:
    def __init__(self, data: bytes, symbols_path: Path, jobs: Optional[int] = None) -> None:
        self.dol = Dol(data)
        self.symbols_path = symbols_path
        self.symbols = Symbols(symbols_path)
        self.jobs = jobs
        self.protected: List[Function] = []
        self.inline: List[Tuple[int, int]] = []
        for function in self.symbols.functions:
            offset, _ = self.dol.find(function[0])
            if offset is None or function[1] < 8:
                continue
            skips = find_skips(function[0], struct.unpack_from(f">{function[1] // 4}I", self.dol.data, offset))
            if skips:
                self.protected.append(function)
                self.inline += skips
        self._pool: Any = None

    def __enter__(self) -> "Analysis":
        if self.jobs != 1:
            self._pool = multiprocessing.Pool(self.jobs, _start_worker, (bytes(self.dol.data), str(self.symbols_path)))
        else:
            _start_worker(bytes(self.dol.data), str(self.symbols_path))
        return self

    def __exit__(self, *exc: Any) -> None:
        if self._pool is not None:
            self._pool.terminate()

    def run(self, functions: Optional[Iterable[Function]] = None, patches: Sequence[Tuple[int, int]] = ()) -> List[Dict[str, Any]]:
        tasks = [(f, list(patches)) for f in (self.protected if functions is None else functions)]
        if self._pool is not None:
            return self._pool.map(_work, tasks, chunksize=4)
        return [_work(task) for task in tasks]


def levels(results: List[Dict[str, Any]]) -> Dict[int, int]:
    """Orders the checksums: a checksum's level is one more than that of any stored value it covers."""
    checks = [c for r in results for c in r["checksums"]]
    stored = sorted(c["stored_at"] for c in checks)
    by_stored = {c["stored_at"]: c for c in checks}
    level: Dict[int, int] = {}

    def visit(check: Dict[str, Any], trail: Tuple[int, ...]) -> int:
        key = check["stored_at"]
        if key in level:
            return level[key]
        if key in trail:
            sys.exit(f"checksums depend on each other in a circle through {key:08X}")
        deepest = -1
        for other in stored[bisect.bisect_left(stored, check["start"]) : bisect.bisect_left(stored, check["end"])]:
            if other != key:
                deepest = max(deepest, visit(by_stored[other], trail + (key,)))
        level[key] = deepest + 1
        return level[key]

    sys.setrecursionlimit(max(sys.getrecursionlimit(), 10000))
    for check in checks:
        visit(check, ())
    return level


def seal(target: Analysis, original: List[Dict[str, Any]], pristine: bytes) -> int:
    """Rewrites the stored values of target's DOL so that every checksum holds again. Returns how many changed."""
    level = levels(original)
    relation = {c["stored_at"]: c["relation"] for r in original for c in r["checksums"]}
    by_name = {f[2]: f for f in target.protected}
    image = target.dol
    changed: List[int] = []
    for start, size, offset, _ in image.sections:
        if image.data[offset : offset + size] != pristine[offset : offset + size]:
            changed += [start + i for i in range(0, size, 4) if image.data[offset + i : offset + i + 4] != pristine[offset + i : offset + i + 4]]
    changed.sort()

    def touched(check: Dict[str, Any]) -> bool:
        return bisect.bisect_left(changed, check["start"]) < bisect.bisect_left(changed, check["end"])

    patches: List[Tuple[int, int]] = []
    for current in range(max(level.values()) + 1):
        functions = [by_name[r["name"]] for r in original if any(level[c["stored_at"]] == current and touched(c) for c in r["checksums"])]
        for result in target.run(functions, patches):
            for check in result["checksums"]:
                key = check["stored_at"]
                if level.get(key) != current:
                    continue
                value = check["computed"] if relation[key] == "equal" else ~check["computed"] & MASK
                if value != check["stored"]:
                    patches.append((key, value))
                    image.write32(key, value)
                    bisect.insort(changed, key)
    return len(patches)


def response(result: Dict[str, Any]) -> str:
    if result["hangs"]:
        return "hangs"
    if result["uses"]:
        return "used as " + "/".join(result["uses"])
    return "hangs in place" if result["spins"] else "no response found"


def describe(result: Dict[str, Any], symbols: Symbols) -> List[str]:
    lines = []
    head = f"{result['address']:08X} {result['name']}"
    effect = response(result)
    for check in result["checksums"]:
        lines.append(f"{head}: checksum of {check['start']:08X}-{check['end']:08X}, stored at {check['stored_at']:08X} ({check['relation']}), {effect}")
    for probe in result["probes"]:
        lines.append(f"{head}: opens {probe['device']}")
    for jump in result["wild_jumps"]:
        lines.append(f"{head}: jumps to {jump['target']:08X}")
    objects: Dict[str, Set[str]] = {}
    for access in result["hidden"]:
        name = symbols.hidden_at(access["address"]) or f"{access['address']:08X}"
        objects.setdefault(name, set()).add("writes" if access["write"] else "reads")
    for name, kinds in sorted(objects.items()):
        lines.append(f"{head}: {' and '.join(sorted(kinds))} {name}")
    if result["low_memory"]:
        lines.append(f"{head}: reads low memory {result['low_memory'][0]:08X}-{result['low_memory'][-1] + 4:08X}")
    for note in result["notes"]:
        lines.append(f"{head}: {note}")
    return lines or [f"{head}: nothing recognised"]


def summarise(results: List[Dict[str, Any]], dol: Dol) -> None:
    checks = [c for r in results for c in r["checksums"]]
    blobs = [b for r in results for b in r["inline"]]
    print(f"{len(results)} protected functions, {len(blobs)} runs of inline data, {sum(e - s for s, e in blobs)} bytes")
    print(f"{len(checks)} checksums: " + ", ".join(f"{sum(1 for c in checks if c['relation'] == k)} {k}" for k in ("equal", "inverse", "broken")))
    with_check = [r for r in results if r["checksums"]]
    kinds = [response(r).split(" as ")[0] for r in with_check]
    print(f"  in {len(with_check)} functions: {kinds.count('hangs')} jump to the response, {kinds.count('hangs in place')} hang in place, {kinds.count('used')} feed the result into the game")
    spans: List[List[int]] = []
    for start, end in sorted((c["start"], c["end"]) for c in checks):
        if spans and start <= spans[-1][1]:
            spans[-1][1] = max(spans[-1][1], end)
        else:
            spans.append([start, end])
    for address, size, _, text in dol.sections:
        covered = sum(min(e, address + size) - max(s, address) for s, e in spans if s < address + size and e > address)
        if covered:
            print(f"  {'text' if text else 'data'} section {address:08X}: {covered:#x} of {size:#x} bytes checked")
    if checks:
        print(f"  longest chain of checksums that cover each other's stored values: {max(levels(results).values()) + 1}")
    print(f"{sum(len(r['probes']) for r in results)} device probes: " + ", ".join(sorted({p["device"] for r in results for p in r["probes"]})))
    print(f"{sum(1 for r in results if r['hidden'])} functions use hidden objects, {sum(1 for r in results if r['low_memory'])} read low memory")
    print(f"{sum(1 for r in results if r['wild_jumps'])} functions can jump to a meaningless address")
    unexplained = [r for r in results if not (r["checksums"] or r["probes"] or r["hidden"] or r["low_memory"] or r["wild_jumps"])]
    noted = [r for r in results if r["notes"]]
    if unexplained or noted:
        print(f"{len(unexplained)} functions not recognised, {len(noted)} with notes (see --list)")


def identifier(symbol: str) -> str:
    """Returns the name a function goes by in the generated header (see include/metafortress.h)."""
    return re.sub(r"\W", "_", symbol)


def write_words(path: Path, version: str, analysis: "Analysis") -> None:
    lines = [f"// Generated by tools/metafortress.py from the {version} disc.", "#ifndef METAFORTRESS_WORDS_H", "#define METAFORTRESS_WORDS_H", ""]
    for start, size, name in analysis.protected:
        offset, _ = analysis.dol.find(start)
        words = struct.unpack_from(f">{size // 4}I", analysis.dol.data, offset)
        for low, high in find_skips(start, words):
            for address in range(low, high, 4):
                lines.append(f"#define mf_{identifier(name)}_0x{address - start:X} 0x{words[(address - start) // 4]:08X}")
    lines += ["", "#endif", ""]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines), encoding="utf-8", newline="\n")


def unit_of(version: str, address: int) -> Optional[str]:
    unit = None
    for line in (Path("config") / version / "splits.txt").read_text(encoding="utf-8").splitlines():
        if line and not line[0].isspace() and line.endswith(":"):
            unit = line[:-1]
        m = re.match(r"\s+\.text\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
        if m and unit and int(m.group(1), 16) <= address < int(m.group(2), 16):
            return unit
    return None


def source(version: str, analysis: "Analysis", wanted: str) -> List[str]:
    """Returns a protected function in the syntax of the compiler's inline assembler.

    Everything is given as assembly, the compiler's own instructions included.
    Which part was written as an asm block and which as C is for the reader to
    work out; see ArenaGameData::isCleared for a finished one.
    """
    found = [f for f in analysis.protected if f[2] == wanted] or [f for f in analysis.protected if wanted in f[2]]
    if len(found) != 1:
        sys.exit(f"{len(found)} protected functions match {wanted}" + "".join(f"\n  {f[2]}" for f in found[:20]))
    start, size, name = found[0]
    unit = unit_of(version, start)
    listing = Path("build") / version / "asm" / Path(unit or "").with_suffix(".s")
    if not listing.is_file():
        sys.exit(f"{listing} not found (run the build first)")
    result = examine(analysis.dol, found[0], analysis.symbols)
    used = set(result["used_inline"])
    data = {a: (low, high) for low, high in result["inline"] for a in range(low, high, 4)}

    body: List[Tuple[Optional[int], str]] = []
    inside = False
    for line in listing.read_text(encoding="utf-8").splitlines():
        if line.startswith(".fn "):
            inside = line[4:].rsplit(",", 1)[0].strip().strip('"') == name
        elif line.startswith(".endfn"):
            inside = False
        elif inside:
            m = re.match(r"/\* ([0-9A-F]{8}) \S+ +([0-9A-F ]{11}) \*/\s+(.*)", line)
            if m:
                body.append((int(m.group(1), 16), m.group(3)))
            elif line.endswith(":"):
                body.append((None, line[:-1]))
    labels: Dict[str, str] = {}
    previous = None
    for address, text in body:
        if address is None:
            after = previous is not None and previous in data
            labels[text] = f"after{sum(v.startswith('after') for v in labels.values()) + 1}" if after else f"L{sum(v.startswith('L') for v in labels.values()) + 1}"
        else:
            previous = address

    out = [f"// {name}", f"// {unit}, 0x{start:08X}, {size} bytes"]
    out += ["// " + line.split(": ", 1)[1] for line in describe(result, analysis.symbols)]
    out += [f"#define MF_FUNCTION {identifier(name)}", ""]
    for address, text in body:
        if address is None:
            out.append(f"    {labels[text]}:")
        elif address in data:
            word, = struct.unpack_from(">I", analysis.dol.data, analysis.dol.find(address)[0])
            out.append(f"        opword  MF_WORD(0x{address - start:X})" if address in used else f"        opword  0x{word:08X}")
        else:
            mnemonic, _, operands = text.partition(" ")
            for old, label in labels.items():
                operands = re.sub(re.escape(old) + r"\b", label, operands)
            out.append(f"        {mnemonic:7} {operands}".rstrip())
    out += ["", "#undef MF_FUNCTION"]
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description="Finds and examines the MetaFortress protection in a build of the game.")
    parser.add_argument("version", type=str.upper, help="game ID, e.g. SUKE01 (reads orig/<ID>/sys/main.dol and config/<ID>/symbols.txt)")
    parser.add_argument("--yaml", action="store_true", help="print block_relocations entries for config.yml")
    parser.add_argument("--list", action="store_true", help="print one line per finding")
    parser.add_argument("--json", type=Path, metavar="FILE", help="write everything found to FILE")
    parser.add_argument("--verify", type=Path, metavar="DOL", help="report the checksums that fail in a modified DOL")
    parser.add_argument("--seal", type=Path, nargs=2, metavar=("IN", "OUT"), help="write IN to OUT with its stored checksums recomputed")
    parser.add_argument("--words", type=Path, metavar="FILE", help="write the inline data of every protected function to FILE as macros")
    parser.add_argument("--source", metavar="SYMBOL", help="print a protected function in the compiler's inline assembly syntax")
    parser.add_argument("--jobs", type=int, help="worker processes (default: one per core)")
    args = parser.parse_args()

    dol_path = Path("orig") / args.version / "sys" / "main.dol"
    symbols_path = Path("config") / args.version / "symbols.txt"
    for path in (dol_path, symbols_path):
        if not path.is_file():
            sys.exit(f"{path} not found (run this from the project root)")
    data = dol_path.read_bytes()

    if args.words:
        write_words(args.words, args.version, Analysis(data, symbols_path))
        return
    if args.source:
        print("\n".join(source(args.version, Analysis(data, symbols_path), args.source)))
        return

    with Analysis(data, symbols_path, args.jobs) as analysis:
        if args.yaml:
            if sorted(analysis.inline) != find_inline_data(data):
                sys.exit("find_inline_data() and the function boundaries disagree about the inline data")
            for start, end in sorted(analysis.inline):
                print(f"- source: .text:0x{start:08X}")
                print(f"  end: .text:0x{end:08X}")
            return
        results = analysis.run()
        sections = analysis.dol.sections

    other = args.verify or (args.seal and args.seal[0])
    if other:
        with Analysis(other.read_bytes(), symbols_path, args.jobs) as target:
            if len(target.dol.data) != len(data) or target.dol.sections != sections:
                sys.exit("the DOL does not have the layout of the original")
            if args.seal:
                changed = seal(target, results, data)
                args.seal[1].write_bytes(target.dol.data)
                print(f"{changed} stored checksums rewritten, wrote {args.seal[1]}")
                return
            failed = 0
            for result in target.run():
                for check in result["checksums"]:
                    if check["relation"] == "broken":
                        failed += 1
                        effect = response(result)
                        print(f"{result['address']:08X} {result['name']}: checksum of {check['start']:08X}-{check['end']:08X} fails ({effect})")
            print(f"{failed} checksums fail")
            sys.exit(1 if failed else 0)

    if args.json:
        args.json.write_text(json.dumps(results, indent=1), encoding="utf-8")
    if args.list:
        for result in results:
            for line in describe(result, analysis.symbols):
                print(line)
    else:
        summarise(results, analysis.dol)


if __name__ == "__main__":
    main()
