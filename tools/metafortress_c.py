#!/usr/bin/env python3

###
# Prints the MetaFortress check of a protected function as C in the canonical
# form (docs/decompiling.md, "The canonical form"): the data fetches as asm
# blocks, the checksum on the locals `u32 i; u32 last; u32 limit; u32 hash;`
# in natural expressions, the response as the linked sources write it, and the
# game's own instructions as comment lines in place.
#
# The check's instructions are told from the game's by following what is read
# from the volatile stack slots that the asm blocks fill. A register that is
# written once and read once right away is taken for a temporary of the
# compiler and folded into the expression that uses it; every other register
# of the check is a variable, named by what it does in the checksum loop.
# What does not fit is printed as its instructions under `// NOT RECOGNISED`.
#
# Usage:
#   python tools/metafortress_c.py SUKE01 SYMBOL            # one function
#   python tools/metafortress_c.py SUKE01 SYMBOL --reuse    # the same with the finish written through the
#                                                           # variables whose registers its temporaries use
#   python tools/metafortress_c.py SUKE01 SYMBOL --locals   # the same with a local for a value that is used twice
#                                                           # after the loop, where the default writes it out twice
#   python tools/metafortress_c.py SUKE01 --survey          # one line per protected function, then the counts
###

import argparse
import re
import struct
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from metafortress import MASK, Analysis, describe, examine, identifier, unit_of

Expr = Tuple[Any, ...]

LOCAL_ORDER = ("i", "word", "last", "base", "limit", "hash")
CALL_CLOBBERS = ["r0"] + [f"r{n}" for n in range(3, 13)] + ["cr0", "cr1", "cr5", "cr6", "cr7"]
PLAIN_BRANCHES = ("b", "bl", "blr", "bctr", "bctrl", "blrl")
COMPARES = ("cmpw", "cmplw", "cmpwi", "cmplwi", "fcmpu", "fcmpo")
RELATIONS = {"beq": "==", "bne": "!=", "blt": "<", "bge": ">=", "bgt": ">", "ble": "<="}
OPPOSITE = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
CONSTANT_STEPS = ("addi", "subi", "addis", "subis", "ori", "oris")
BINARY = {"add": "+", "mullw": "*", "xor": "^", "or": "|", "and": "&", "slw": "<<", "srw": ">>"}
IMMEDIATE = {"mulli": "*", "xori": "^", "ori": "|", "slwi": "<<", "srwi": ">>"}
COMPOUND = ("+", "-", "*", "^", "|", "&", "<<", ">>")
ENTRY = -1


class Ins:
    __slots__ = ("addr", "mn", "ops", "text", "asm", "reads", "writes", "mem", "target", "position")

    def __init__(self, addr: int, text: str, position: int) -> None:
        self.addr, self.text, self.position = addr, text, position
        mnemonic, _, rest = text.partition(" ")
        self.mn = mnemonic.rstrip("+-")
        plain = re.sub(r"@sda21\(r\d+\)", "", re.sub(r'"[^"]*"', "Q", rest))
        self.ops = [o.strip() for o in plain.split(",")] if plain.strip() else []
        self.asm = False
        self.mem: Optional[Tuple[int, str]] = None
        self.target: Optional[str] = None
        for op in self.ops:
            m = re.fullmatch(r"(-?(?:0x[0-9a-fA-F]+|\d+))\((r\d+)\)", op)
            if m:
                self.mem = (int(m.group(1), 0), m.group(2))
        if self.mn.startswith("b") and self.ops and self.ops[-1].startswith(".L"):
            self.target = self.ops[-1]
        self.reads: List[str] = []
        self.writes: List[str] = []
        self._effects()

    def _effects(self) -> None:
        mn, ops = self.mn, self.ops
        regs = [re.findall(r"\br\d+\b", op) for op in ops]
        if mn.startswith("b"):
            if mn in ("bl", "bctrl", "blrl"):
                self.writes = list(CALL_CLOBBERS)
            elif mn not in PLAIN_BRANCHES and not mn.startswith("bd"):
                self.reads = [ops[0] if ops and ops[0].startswith("cr") else "cr0"]
        elif mn in COMPARES:
            self.writes = [ops[0] if ops[0].startswith("cr") else "cr0"]
            self.reads = [r for found in regs for r in found]
        elif mn.startswith("st"):
            self.reads = [r for found in regs for r in found]
            if mn.rstrip("x").endswith("u") and self.mem:
                self.writes = [self.mem[1]]
        elif mn.startswith("mt"):
            self.reads = [r for found in regs for r in found]
        else:
            if ops and re.fullmatch(r"r\d+", ops[0]):
                self.writes = [ops[0]]
                self.reads = [r for found in regs[1:] for r in found]
            else:
                self.reads = [r for found in regs for r in found]
            if mn.startswith("l") and mn.rstrip("x").endswith("u") and self.mem:
                self.writes.append(self.mem[1])
            if mn.endswith("."):
                self.writes.append("cr0")

    @property
    def conditional(self) -> bool:
        return self.mn.startswith("b") and self.mn not in PLAIN_BRANCHES


def read_listing(path: Path) -> Dict[str, List[Tuple[Optional[int], str]]]:
    """Returns the lines of every function of a unit's listing: (address, instruction) or (None, label)."""
    functions: Dict[str, List[Tuple[Optional[int], str]]] = {}
    body: Optional[List[Tuple[Optional[int], str]]] = None
    for line in path.read_text(encoding="utf-8").splitlines():
        if line.startswith(".fn "):
            body = functions.setdefault(line[4:].rsplit(",", 1)[0].strip().strip('"'), [])
        elif line.startswith(".endfn"):
            body = None
        elif body is not None:
            m = re.match(r"/\* ([0-9A-F]{8}) \S+ +([0-9A-F ]{11}) \*/\s+(.*)", line)
            if m:
                body.append((int(m.group(1), 16), m.group(3)))
            elif line.endswith(":"):
                body.append((None, line[:-1]))
    return functions


def constant(value: int) -> Expr:
    return ("c", value & MASK)


def has_raw(e: Expr) -> bool:
    return e[0] == "r" or any(isinstance(x, tuple) and has_raw(x) for x in e[1:])


def show_constant(value: int, parent: str) -> str:
    if value >= 0xFFFF8000:
        return f"-{0x100000000 - value}"
    if parent in ("<<", ">>") or value < 10 or (parent == "*" and value < 0x10000):
        return str(value)
    return f"0x{value:X}" if value < 0x10000 else f"0x{value:08X}"


def show(e: Expr, parent: str = "", right: bool = False) -> str:
    kind = e[0]
    if kind == "c":
        return show_constant(e[1], parent)
    if kind in ("v", "r"):
        return e[1]
    if kind == "ld":
        inner = show(e[1])
        return f"*(u16*){inner}" if e[1][0] == "v" else f"*(u16*)({inner})"
    if kind == "u":
        return f"{e[1]}{show(e[2], 'unary', True)}"
    if kind == "call":
        return f"{e[1]}({show(e[2])})"
    op = e[1]
    text = f"{show(e[2], op)} {op} {show(e[3], op, True)}"
    if not parent:
        return text
    comparison = parent in OPPOSITE
    additive = op in ("+", "-") and parent in ("+", "-") and not right
    if (comparison and op in ("+", "-", "*")) or additive:
        return text
    return f"({text})"


class Function:
    """One protected function: its instructions, which of them belong to the check, and the C they stand for."""

    def __init__(self, analysis: Analysis, unit: str, function: Tuple[int, int, str], body: List[Tuple[Optional[int], str]], result: Dict[str, Any], reuse: bool = False, inline: bool = True) -> None:
        self.analysis, self.unit, self.reuse, self.inline = analysis, unit, reuse, inline
        self.start, self.size, self.name = function
        self.body, self.result = body, result
        self.data = {a for low, high in result["inline"] for a in range(low, high, 4)}
        self.used = set(result["used_inline"])
        self.problems: List[str] = []
        self.ins: List[Ins] = []
        self.index_of_label: Dict[str, int] = {}
        self.labels: Dict[str, str] = {}
        self.labels_at: Dict[int, List[str]] = {}
        self._parse()
        self.n = len(self.ins)
        self.blocks: List[Tuple[int, int]] = []
        self.slots: Dict[int, str] = {}
        self.response_slots: Set[int] = set()
        self.final_blocks: List[Tuple[int, int]] = []
        self._find_asm()
        self._name_slots()
        self._spills()
        self._flow()
        self._mark_check()
        self._loops()
        self._webs()
        self._name_variables()
        self._name_response_slots()
        # A value that reads a volatile local cannot be written twice: such a function wants the local.
        self.impure = any(self._repeated(d) and self._reads_volatile(self._value(d, set())) for d in sorted(self.check))
        self._structure()

    def problem(self, text: str) -> None:
        if text not in self.problems:
            self.problems.append(text)

    def _parse(self) -> None:
        previous: Optional[int] = None
        pending: List[str] = []
        for position, (address, text) in enumerate(self.body):
            if address is None:
                after = previous is not None and previous in self.data
                prefix = "after" if after else "L"
                self.labels[text] = f"{prefix}{sum(v.startswith(prefix) for v in self.labels.values()) + 1}"
                pending.append(text)
                continue
            previous = address
            if address in self.data:
                continue
            for label in pending:
                self.index_of_label[label] = len(self.ins)
            if pending:
                self.labels_at[len(self.ins)] = pending
            pending = []
            self.ins.append(Ins(address, text, position))

    def _blob_call(self, k: int) -> bool:
        return self.ins[k].mn == "bl" and self.ins[k].addr + 4 in self.data

    def _find_asm(self) -> None:
        ins, k = self.ins, 0
        while k < self.n:
            if not self._blob_call(k):
                k += 1
                continue
            first, fetched = k, set()
            # A response may clear the way with a store below the stack pointer ahead of its first fetch.
            while first > 0 and ins[first - 1].mn == "stw" and ins[first - 1].mem and ins[first - 1].mem[1] == "r1" and ins[first - 1].mem[0] in (-8, -4, 0, 4):
                first -= 1
            k += 1
            while k < self.n:
                i = ins[k]
                if i.mn == "mflr" and self._blob_call(k - 1):
                    fetched.add(i.ops[0])
                elif self._blob_call(k) or i.mn == "blrl":
                    pass
                elif i.mn == "lwz" and i.mem and i.mem[1] in fetched:
                    fetched.add(i.ops[0])
                elif i.mn == "stw" and i.mem and i.mem[1] == "r1" and i.ops[0] in fetched:
                    if i.mem[0] >= 8:
                        self.slots.setdefault(i.mem[0], "")
                elif i.mn == "add" and i.ops[1] in fetched and i.ops[2] in fetched:
                    fetched.add(i.ops[0])
                elif i.mn in ("addi", "subi") and i.ops[1] in fetched:
                    fetched.add(i.ops[0])
                elif i.mn == "mtlr" and i.ops[0] in fetched:
                    pass
                else:
                    break
                k += 1
            self.blocks.append((first, k - 1))
        for k in range(self.n - 2):
            a, b, c = ins[k : k + 3]
            if a.mn == "lwz" and a.mem and a.mem[1] == "r1" and b.mn == "mtlr" and b.ops == a.ops[:1] and c.mn == "blr":
                self.blocks.append((k, k + 2))
                self.final_blocks.append((k, k + 2))
                self.slots.setdefault(a.mem[0], "")
                self.response_slots.add(a.mem[0])
        self.blocks.sort()
        for first, last in self.blocks:
            for k in range(first, last + 1):
                ins[k].asm = True
                if ins[k].mn in ("bl", "blrl"):
                    ins[k].writes = []
        named = {r for i in ins if i.asm for r in i.writes if r.startswith("r")}
        if any(not i.asm and i.mn not in ("bl", "bctrl", "blrl") and set(i.writes) & named for i in ins[4:-6]):
            self.problem("a register of an asm block is also written by the compiler")

    def _spills(self) -> None:
        """Gives the other stack slots a place in the data flow: a variable of the check can be kept in one."""
        for i in self.ins:
            if i.asm or not i.mem or i.mem[1] != "r1" or i.mem[0] < 8 or i.mem[0] in self.slots:
                continue
            if i.mn == "stw":
                i.writes, i.reads = [f"rS{i.mem[0]:X}"], [r for r in i.reads if r != "r1"]
            elif i.mn == "lwz":
                i.reads = [f"rS{i.mem[0]:X}"]

    def _word(self, address: int) -> int:
        offset, _ = self.analysis.dol.find(address)
        return struct.unpack_from(">I", self.analysis.dol.data, offset)[0] if offset is not None else 0

    def _name_slots(self) -> None:
        """Runs the fetch blocks to see which slot gets a range's start, its end and the stored word."""
        ins = self.ins
        values: Dict[int, Tuple[int, int]] = {}
        self.base_slots: Set[int] = set()
        for first, last in self.blocks:
            regs: Dict[str, Tuple[int, int, bool]] = {}
            for k in range(first, last + 1):
                i = ins[k]
                if i.mn == "mflr" and self._blob_call(k - 1):
                    regs[i.ops[0]] = (ins[k - 1].addr + 4, 0, True)
                elif i.mn == "lwz" and i.mem and i.mem[1] in regs and regs[i.mem[1]][2]:
                    address = regs[i.mem[1]][0] + i.mem[0]
                    regs[i.ops[0]] = (self._word(address), address, False)
                elif i.mn == "add" and i.ops[1] in regs and i.ops[2] in regs:
                    regs[i.ops[0]] = ((regs[i.ops[1]][0] + regs[i.ops[2]][0]) & MASK, 0, False)
                elif i.mn in ("addi", "subi") and i.ops[1] in regs:
                    step = int(i.ops[2], 0) * (1 if i.mn == "addi" else -1)
                    regs[i.ops[0]] = ((regs[i.ops[1]][0] + step) & MASK, 0, False)
                elif i.mn == "stw" and i.mem and i.mem[1] == "r1" and i.mem[0] in self.slots and i.ops[0] in regs:
                    values[i.mem[0]] = regs[i.ops[0]][:2]
                    if regs[i.ops[0]][2]:
                        self.base_slots.add(i.mem[0])
        for number, check in enumerate(self.result["checksums"]):
            suffix = "" if number == 0 else str(number + 1)
            for slot, (value, origin) in sorted(values.items()):
                if self.slots[slot]:
                    continue
                if origin == check["stored_at"]:
                    self.slots[slot] = "expected" + suffix
                elif value == check["start"] and "start" + suffix not in self.slots.values():
                    self.slots[slot] = "start" + suffix
                elif abs(value - check["end"]) <= 2 and "end" + suffix not in self.slots.values():
                    self.slots[slot] = "end" + suffix

    def _flow(self) -> None:
        """Reaching definitions: for every instruction, which instructions may have written each register it reads."""
        ins, n = self.ins, self.n
        referenced = {i.target for i in ins if i.target}
        unreferenced = [k for label, k in self.index_of_label.items() if label not in referenced and not self.labels[label].startswith("after")]
        self.succ: List[List[int]] = []
        for k, i in enumerate(ins):
            following = [k + 1] if k + 1 < n else []
            if i.asm:
                self.succ.append([] if i.mn == "blr" else following)
            elif i.mn == "b":
                self.succ.append([self.index_of_label[i.target]] if i.target in self.index_of_label else [])
            elif i.mn == "blr":
                self.succ.append([])
            elif i.mn == "bctr":
                self.succ.append(unreferenced)
            elif i.conditional and i.target in self.index_of_label:
                self.succ.append(following + [self.index_of_label[i.target]])
            else:
                self.succ.append(following)
        leaders = {0}
        for k, targets in enumerate(self.succ):
            if targets != [k + 1]:
                leaders.update(targets)
                leaders.add(k + 1)
        starts = sorted(x for x in leaders if x < n)
        self.block_of = [0] * n
        spans = []
        for b, first in enumerate(starts):
            last = (starts[b + 1] if b + 1 < len(starts) else n) - 1
            spans.append((first, last))
            for k in range(first, last + 1):
                self.block_of[k] = b
        preds: List[List[int]] = [[] for _ in spans]
        for b, (first, last) in enumerate(spans):
            for target in self.succ[last]:
                preds[self.block_of[target]].append(b)
        gen: List[Dict[str, int]] = []
        for first, last in spans:
            written: Dict[str, int] = {}
            for k in range(first, last + 1):
                for loc in ins[k].writes:
                    written[loc] = k
            gen.append(written)
        outs: List[Dict[str, frozenset]] = [{loc: frozenset([k]) for loc, k in g.items()} for g in gen]
        entry = frozenset([ENTRY])
        nothing: frozenset = frozenset()
        everything = {loc for i in ins for loc in i.reads + i.writes}

        def arriving(b: int) -> Dict[str, frozenset]:
            sources = preds[b]
            state = {loc: nothing.union(*(outs[p].get(loc, nothing) for p in sources)) for loc in {loc for p in sources for loc in outs[p]}}
            if b == 0 or not sources:
                for loc in everything:
                    state[loc] = state.get(loc, nothing) | entry
            return state

        changed = True
        rounds = 0
        while changed and rounds < 200:
            changed = False
            rounds += 1
            for b in range(len(spans)):
                merged = arriving(b)
                for loc, k in gen[b].items():
                    merged[loc] = frozenset([k])
                if merged != outs[b]:
                    outs[b] = merged
                    changed = True
        self.rd: List[Dict[str, frozenset]] = [{} for _ in range(n)]
        for b, (first, last) in enumerate(spans):
            state = arriving(b)
            for k in range(first, last + 1):
                self.rd[k] = {loc: state.get(loc, nothing) for loc in ins[k].reads}
                for loc in ins[k].writes:
                    state[loc] = frozenset([k])
        self.uses: Dict[int, List[Tuple[int, str]]] = {}
        for k in range(n):
            for loc, defs in self.rd[k].items():
                for d in defs:
                    if d >= 0:
                        self.uses.setdefault(d, []).append((k, loc))

    def _volatile(self, k: int) -> Optional[str]:
        i = self.ins[k]
        if not i.asm and i.mn in ("lwz", "stw") and i.mem and i.mem[1] == "r1" and i.mem[0] in self.slots:
            return i.mn
        return None

    def _constant_def(self, d: int, depth: int = 0) -> bool:
        if d < 0 or depth > 3:
            return False
        i = self.ins[d]
        if i.asm:
            return False
        if i.mn in ("li", "lis"):
            return True
        if i.mn in CONSTANT_STEPS:
            defs = self.rd[d].get(i.ops[1], ())
            return len(defs) == 1 and all(self._constant_def(x, depth + 1) for x in defs)
        return False

    def _mark_check(self) -> None:
        ins = self.ins
        self.check: Set[int] = {k for k in range(self.n) if self._volatile(k)}
        changed = True
        while changed:
            changed = False
            for k, i in enumerate(ins):
                if i.asm or k in self.check or i.mn in PLAIN_BRANCHES or not i.reads:
                    continue
                if i.mn.startswith("mt") or (i.mn.startswith("st") and not (i.writes and i.writes[0].startswith("rS"))):
                    continue
                if any(d in self.check for defs in self.rd[k].values() for d in defs):
                    self.check.add(k)
                    changed = True
            for k in list(self.check):
                for defs in self.rd[k].values():
                    for d in defs:
                        if d < 0 or d in self.check or ins[d].asm:
                            continue
                        stepping = ins[d].mn in ("addi", "subi") and ins[d].ops[0] == ins[d].ops[1]
                        if stepping or self._constant_def(d):
                            self.check.add(d)
                            changed = True

    def _find(self, d: int) -> int:
        while self.parent[d] != d:
            self.parent[d] = self.parent[self.parent[d]]
            d = self.parent[d]
        return d

    def _webs(self) -> None:
        self.kind: Dict[int, str] = {}
        self.parent = {d: d for d in self.check}
        for k in range(self.n):
            for defs in self.rd[k].values():
                mine = [d for d in defs if d in self.check]
                for d in mine[1:]:
                    self.parent[self._find(d)] = self._find(mine[0])
        # A register that is already a variable and is updated in place stays that variable.
        changed = True
        while changed:
            changed = False
            size: Dict[int, int] = {}
            for d in self.check:
                size[self._find(d)] = size.get(self._find(d), 0) + 1
            for k in sorted(self.check):
                i = self.ins[k]
                if not i.writes or not i.writes[0].startswith("r") or self._constant_def(k) or self._spanned(k):
                    continue
                reg = i.writes[0]
                defs = self.rd[k].get(reg, ()) if reg in i.reads else ()
                if defs and all(d in self.check for d in defs):
                    root = self._find(next(iter(defs)))
                    if size.get(root, 0) > 1 and self._find(k) != root:
                        self.parent[self._find(k)] = root
                        changed = True
                        break
                # A value that goes on into an update in place of the same register is that variable too.
                users = self.uses.get(k, [])
                u = users[0][0] if len(users) == 1 else -1
                if u > k and u in self.check and self.ins[u].writes[:1] == [reg] and reg in self.ins[u].reads:
                    if size.get(self._find(u), 0) > 1 and self._find(u) != self._find(k) and not self._constant_def(u) and not self._spanned(u):
                        self.parent[self._find(k)] = self._find(u)
                        changed = True
                        break
        self.members: Dict[int, List[int]] = {}
        for d in sorted(self.check):
            self.members.setdefault(self._find(d), []).append(d)

    def _spanned(self, k: int) -> bool:
        return self._spanning(k) is not None

    def _spanning(self, k: int) -> Optional[int]:
        """A temporary computed ahead of instruction k that is still to be used after it: k is then inside an expression."""
        for e in range(k - 1, -1, -1):
            if self.block_of[e] != self.block_of[k] or e not in self.check:
                return None
            users = self.uses.get(e, [])
            writes = self.ins[e].writes
            if not writes or not writes[0].startswith("r") or self._volatile(e) or self.kind.get(e) == "var":
                continue
            if len(users) == 1 and users[0][0] > k and self.block_of[users[0][0]] == self.block_of[k] and all(x in self.check for x in range(e, users[0][0])):
                return e
            if self._repeated(e) and max(u for u, _ in users) > k:
                return e
        return None

    def _reads_volatile(self, e: Expr) -> bool:
        return (e[0] == "v" and e[1] in self.slots.values()) or any(isinstance(x, tuple) and self._reads_volatile(x) for x in e[1:])

    def _repeated(self, d: int) -> bool:
        """Whether a value used more than once after the loop is written out at each use (not with --locals)."""
        users = sorted({u for u, _ in self.uses.get(d, [])})
        writes = self.ins[d].writes
        if not self.inline or len(users) < 2 or users[0] <= d or not writes or not writes[0].startswith("r") or self._volatile(d):
            return False
        if not self.sums or any(q >= d for _, q, _ in self.sums) or any(self.block_of[u] != self.block_of[d] for u in users):
            return False
        return all(k in self.check and self._volatile(k) != "stw" for k in range(d, users[-1] + 1))

    def _loops(self) -> None:
        ins = self.ins
        self.loops: List[Tuple[int, int]] = []
        for q, i in enumerate(ins):
            if not i.asm and i.target in self.index_of_label and i.mn != "bl" and self.index_of_label[i.target] <= q:
                self.loops.append((self.index_of_label[i.target], q))
        self.sums: List[Tuple[int, int, int]] = []
        for h in sorted(self.check):
            if ins[h].mn in ("lhz", "lhzx"):
                around = sorted((q - t, t, q) for t, q in self.loops if t <= h <= q)
                if around and not any(s[:2] == around[0][1:] for s in self.sums):
                    self.sums.append((around[0][1], around[0][2], h))

    def _sum_of(self, k: int) -> Optional[Tuple[int, int, int]]:
        for loop in self.sums:
            if loop[0] <= k <= loop[1]:
                return loop
        return None

    def _classify(self, d: int) -> str:
        """Says whether what an instruction of the check writes is a temporary, a variable or a value for the game."""
        if d in self.kind:
            return self.kind[d]
        self.kind[d] = "var"
        ins = self.ins
        result = "var"
        users = self.uses.get(d, [])
        if len(self.members[self._find(d)]) > 1:
            pass
        elif all(u not in self.check for u, _ in users):
            result = "out"
        elif self._tested(d) or self._repeated(d):
            result = "temp"
        elif len(users) == 1 and users[0][0] in self.check and users[0][0] > d and self.block_of[users[0][0]] == self.block_of[d] and all(self._temporary(k) for k in range(d + 1, users[0][0])):
            result = "temp"
            u = ins[users[0][0]]
            if self._volatile(d) == "lwz" and u.mn in ("addi", "subi") and self._hoisted(users[0][0]) and self._classify(users[0][0]) == "temp":
                result = "var"
        elif self._hoisted(d) and (self._constant_def(d) or (ins[d].mn in ("addi", "subi") and self._is_variable(d, ins[d].ops[1]))):
            result = "temp"
        self.kind[d] = result
        return result

    def _tested(self, d: int) -> bool:
        """Whether a value is only turned into a bool with subic and subfe."""
        users = sorted(u for u, _ in self.uses.get(d, []))
        if len(users) != 2 or users[1] != users[0] + 1 or users[0] <= d or self.block_of[users[1]] != self.block_of[d]:
            return False
        first, second = self.ins[users[0]], self.ins[users[1]]
        return first.mn in ("subic", "addic") and second.mn == "subfe" and all(k in self.check for k in range(d, users[1] + 1))

    def _temporary(self, k: int) -> bool:
        i = self.ins[k]
        return k in self.check and bool(i.writes) and i.writes[0].startswith("r") and self._classify(k) == "temp"

    def _hoisted(self, d: int) -> bool:
        users = self.uses.get(d, [])
        loops = {self._sum_of(u) for u, _ in users}
        return bool(users) and len(loops) == 1 and None not in loops and self._sum_of(d) is None and all(u in self.check for u, _ in users)

    def _is_variable(self, k: int, loc: str) -> bool:
        defs = self.rd[k].get(loc, ())
        return bool(defs) and all(d in self.check and self._classify(d) == "var" for d in defs)

    def _roots(self, k: int, loc: str, depth: int = 0) -> Set[int]:
        """The variables a register read by instruction k is computed from, looking through temporaries."""
        found: Set[int] = set()
        for d in self.rd[k].get(loc, ()):
            if d not in self.check or depth > 8:
                continue
            if self._classify(d) == "var":
                found.add(self._find(d))
            else:
                for inner in self.ins[d].reads:
                    found |= self._roots(d, inner, depth + 1)
        return found

    def _sink(self, d: int, depth: int = 0) -> Optional[int]:
        for u, _ in self.uses.get(d, []):
            if u in self.check and self.ins[u].writes and self.ins[u].writes[0].startswith("r") and depth < 8:
                if self._classify(u) == "var":
                    return self._find(u)
                found = self._sink(u, depth + 1)
                if found is not None:
                    return found
        return None

    def _name_variables(self) -> None:
        ins = self.ins
        self.web_name: Dict[int, str] = {}
        for d in sorted(self.check):
            if ins[d].writes and ins[d].writes[0].startswith("r"):
                self._classify(d)
        # Whatever is written to the hash's register between the loop and the comparison is the hash.
        merged = False
        for t, q, h in self.sums:
            web = self._sink(h)
            registers = {ins[d].writes[0] for d in self.members.get(web, [])} if web is not None else set()
            if len(registers) != 1:
                continue
            for k in range(q + 1, self.n):
                if k in self.check and ins[k].conditional or ins[k].asm and ins[k].mn == "blr":
                    break
                if k in self.check and ins[k].writes[:1] == list(registers) and self._find(k) != self._find(web) and not self._volatile(k) and not self._spanned(k):
                    self.parent[self._find(k)] = self._find(web)
                    merged = True
        if merged:
            self.members = {}
            for d in sorted(self.check):
                self.members.setdefault(self._find(d), []).append(d)
            self.kind = {}
            for d in sorted(self.check):
                if ins[d].writes and ins[d].writes[0].startswith("r"):
                    self._classify(d)

        def give(web: Optional[int], name: str) -> None:
            if web is None:
                self.problem(f"no variable found for {name}")
            elif self.web_name.setdefault(web, name) != name:
                self.problem(f"{self.web_name[web]} and {name} are one register")

        for number, (t, q, h) in enumerate(self.sums):
            suffix = "" if number == 0 else str(number + 1)
            give(self._sink(h), "hash" + suffix)
            stepping = None
            for d in range(t, q + 1):
                i = ins[d]
                if d in self.check and i.mn in ("addi", "subi") and i.ops[0] == i.ops[1] and i.ops[2] in ("0x2", "2") and self._classify(d) == "var":
                    stepping = self._find(d)
            if stepping is None:
                self.problem("no variable in the loop steps by 2")
                continue
            outside = [d for d in self.members[stepping] if not t <= d <= q]
            index = bool(outside) and all(self._constant_def(d) for d in outside)
            give(stepping, ("i" if index else "word") + suffix)
            address = set()
            for loc in ins[h].reads:
                address |= self._roots(h, loc)
            for web in address - {stepping}:
                backward = any(ins[d].mn == "subf" and stepping in self._roots(d, ins[d].ops[1]) for d in range(t, h))
                give(web, ("last" if backward else "base") + suffix)
            for c in range(t, q + 1):
                if c in self.check and ins[c].mn in ("cmplw", "cmpw"):
                    sides = [self._roots(c, loc) for loc in ins[c].reads]
                    if len(sides) == 2 and {stepping} in sides:
                        other = sides[1 - sides.index({stepping})]
                        if len(other) == 1:
                            web = next(iter(other))
                            if web not in self.web_name:
                                give(web, ("limit" if index else "last") + suffix)
        # A value kept after the loop and used twice is a variable: the one whose register it sits in, or a fifth.
        self.extra: List[str] = []
        end_of_loops = max((q for _, q, _ in self.sums), default=self.n)
        for web, members in sorted(self.members.items()):
            d = members[0]
            if web in self.web_name or len(members) != 1 or d < end_of_loops or not ins[d].writes or not ins[d].writes[0].startswith("r"):
                continue
            if self._classify(d) == "var" and not self._volatile(d) and all(u in self.check for u, _ in self.uses.get(d, [])):
                reused = {name for w, name in self.web_name.items() if name[:4] not in ("hash", "firs") and any(ins[x].writes[:1] == ins[d].writes[:1] for x in self.members[w])}
                if len(reused) == 1:
                    self.web_name[web] = reused.pop()
                    continue
                self.web_name[web] = "first" if not self.extra else f"first{len(self.extra) + 1}"
                self.extra.append(self.web_name[web])
        # A temporary in the register of a local added after the loop is that local. With --reuse the same
        # goes for the registers of the variables that are done with: the older form of the finish.
        for _, q, _ in self.sums * 2:
            for d in range(q + 1, self.n):
                if d in self.check and ins[d].conditional or ins[d].asm and ins[d].mn == "blr":
                    break
                if d not in self.check or not ins[d].writes or self._find(d) in self.web_name or len(self.members[self._find(d)]) != 1:
                    continue
                reused = {name for w, name in self.web_name.items() if (name in self.extra or (self.reuse and name[:4] != "hash")) and any(ins[x].writes[:1] == ins[d].writes[:1] for x in self.members[w])}
                if len(reused) != 1 or self.kind.get(d) != "temp":
                    continue
                # A statement cannot stand inside an expression, so a value that is pending here is a local as well.
                e = self._spanning(d)
                if e is not None and self.kind.get(e) == "temp" and len(self.members[self._find(e)]) == 1 and self._find(e) not in self.web_name and reused <= set(self.extra) and not self._volatile(e):
                    self.kind[e] = "var"
                    self.web_name[self._find(e)] = "first" if not self.extra else f"first{len(self.extra) + 1}"
                    self.extra.append(self.web_name[self._find(e)])
                if not self._spanned(d):
                    self.kind[d] = "var"
                    self.web_name[self._find(d)] = reused.pop()
        # So is the upper half of a start value that is loaded into such a local's register.
        for d in sorted(self.check):
            if ins[d].mn == "lis" and self.kind.get(d) == "temp" and self._find(d) not in self.web_name:
                reused = {name for w, name in self.web_name.items() if name in self.extra and any(ins[x].writes[:1] == ins[d].writes[:1] for x in self.members[w])}
                if len(reused) == 1:
                    self.kind[d] = "var"
                    self.web_name[self._find(d)] = reused.pop()
        if self.result["checksums"] and not self.sums:
            self.problem("the checksum loop was not found")
        if len(self.sums) > 1:
            self.problem("more than one checksum: the names of the later ones are guesses")

    def _name_response_slots(self) -> None:
        ins = self.ins
        roles: Dict[int, str] = {}
        for k in sorted(self.check):
            i = ins[k]
            if i.mn in ("xor", "add", "subf") and len(i.reads) == 2:
                loads = []
                for loc in i.reads:
                    defs = list(self.rd[k].get(loc, ()))
                    loads.append(ins[defs[0]].mem[0] if len(defs) == 1 and defs[0] >= 0 and self._volatile(defs[0]) == "lwz" else None)
                if None in loads or any(self.slots[s] for s in loads):
                    continue
                first, second = (loads[1], loads[0]) if i.mn == "subf" else (loads[0], loads[1])
                if second in self.base_slots:
                    first, second = second, first
                if first in self.base_slots:
                    roles.setdefault(second, "response" if second in self.response_slots else "offset")
                else:
                    roles.setdefault(first, "offset")
                    roles.setdefault(second, {"xor": "key", "add": "addend", "subf": "subtrahend"}[i.mn])
        taken = set(self.slots.values()) | set(self.web_name.values())
        for slot in sorted(self.slots, reverse=True):
            if self.slots[slot]:
                continue
            read = any(self._volatile(k) == "lwz" and ins[k].mem[0] == slot for k in range(self.n))
            if slot in self.response_slots:
                wanted = "response"
            elif slot in self.base_slots:
                wanted = "base"
            else:
                wanted = roles.get(slot, "offset" if read else "unused")
            name, number = wanted, 1
            while name in taken:
                number += 1
                name = f"{wanted}{number}"
            self.slots[slot] = name
            taken.add(name)

    def _read(self, k: int, loc: str, used: Set[int]) -> Expr:
        defs = self.rd[k].get(loc, ())
        if not defs or any(d not in self.check for d in defs):
            return ("r", loc)
        first = next(iter(defs))
        kind = self._classify(first)
        if kind == "var":
            web = self._find(first)
            if any(self._find(d) != web for d in defs) or web not in self.web_name:
                return ("r", loc)
            return ("v", self.web_name[web])
        if len(defs) != 1:
            return ("r", loc)
        used.add(first)
        return self._value(first, used)

    def _value(self, d: int, used: Set[int]) -> Expr:
        """The expression an instruction of the check computes."""
        i = self.ins[d]
        mn, ops = i.mn, i.ops

        def reg(n: int) -> Expr:
            return self._read(d, ops[n], used)

        def imm(n: int) -> int:
            return int(ops[n], 0)

        if mn == "li":
            return constant(imm(1))
        if mn == "lis":
            return constant(imm(1) << 16)
        if mn == "lwz" and self._volatile(d):
            return ("v", self.slots[i.mem[0]])
        if mn in ("addi", "subi", "addis", "subis"):
            a = reg(1)
            step = imm(2) * (0x10000 if mn.endswith("s") else 1) * (-1 if mn.startswith("sub") else 1)
            if a[0] == "c":
                return constant(a[1] + step)
            return ("b", "+", a, constant(step)) if step >= 0 else ("b", "-", a, constant(-step))
        if mn in ("ori", "oris") and reg(1)[0] == "c":
            return constant(reg(1)[1] | (imm(2) << (16 if mn == "oris" else 0)))
        if mn in IMMEDIATE:
            a = reg(1)
            if mn == "srwi" and a[0] == "call":
                a = ("u", "(u32)", a)
            return ("b", IMMEDIATE[mn], a, constant(imm(2)))
        if mn in BINARY:
            return ("b", BINARY[mn], reg(1), reg(2))
        if mn == "subf":
            return ("b", "-", reg(2), reg(1))
        if mn == "andc":
            return ("b", "&", reg(1), ("u", "~", reg(2)))
        if mn == "nor":
            return ("u", "~", reg(1) if ops[1] == ops[2] else ("b", "|", reg(1), reg(2)))
        if mn == "not":
            return ("u", "~", reg(1))
        if mn == "neg":
            return ("u", "-", reg(1))
        if mn == "mr":
            return reg(1)
        if mn == "stw" and i.writes and i.writes[0].startswith("rS"):
            return reg(0)
        if mn == "lwz" and i.reads and i.reads[0].startswith("rS"):
            return self._read(d, i.reads[0], used)
        if mn == "subfe" and d - 1 in self.check:
            before = self.ins[d - 1]
            if before.mn in ("subic", "addic") and before.ops[0] == ops[1] and before.ops[1] == ops[2] and abs(int(before.ops[2], 0)) == 1:
                used.add(d - 1)
                return ("b", "!=", self._read(d - 1, before.ops[1], used), constant(0))
        if mn == "cntlzw":
            return ("call", "__cntlzw", reg(1))
        if mn == "lhz" and i.mem:
            base = self._read(d, i.mem[1], used)
            if i.mem[0] == 0:
                return ("ld", base)
            return ("ld", ("b", "+" if i.mem[0] > 0 else "-", base, constant(abs(i.mem[0]))))
        if mn == "lhzx":
            return ("ld", ("b", "+", reg(1), reg(2)))
        return ("r", ops[0] if ops else "?")

    def _condition(self, k: int, used: Set[int]) -> Optional[Tuple[str, Expr, Expr]]:
        """The comparison a conditional branch of the check is taken on."""
        i = self.ins[k]
        relation = RELATIONS.get(i.mn)
        defs = list(self.rd[k].get(i.reads[0], ())) if i.reads else []
        if relation is None or len(defs) != 1 or defs[0] not in self.check:
            return None
        c = self.ins[defs[0]]
        used.add(defs[0])
        if c.mn in ("cmplw", "cmpw"):
            return relation, self._read(defs[0], c.reads[0], used), self._read(defs[0], c.reads[1], used)
        if c.mn in ("cmpwi", "cmplwi"):
            return relation, self._read(defs[0], c.reads[0], used), constant(int(c.ops[-1], 0))
        return None

    def _condition_text(self, k: int, negate: bool, used: Set[int]) -> Optional[str]:
        found = self._condition(k, used)
        if found is None or has_raw(found[1]) or has_raw(found[2]):
            return None
        relation = OPPOSITE[found[0]] if negate else found[0]
        return f"{show(found[1], relation)} {relation} {show(found[2], relation, True)}"

    def _structure(self) -> None:
        """Decides what every instruction prints: a statement, the frame of a loop or of an `if`, or nothing."""
        ins, n = self.ins, self.n
        self.before: Dict[int, List[Tuple[str, str]]] = {}
        self.after: Dict[int, List[Tuple[str, str]]] = {}
        self.lines: Dict[int, List[Tuple[str, str]]] = {}
        self.silent: Set[int] = set()
        self.raw: Set[int] = set()
        self.absorbed: Set[int] = set()
        self.inner_slots: List[int] = []
        self.whole_response = False
        self.fed = False
        self.searched = False
        control: Set[int] = set()

        def unrecognised(k: int, used: Set[int], why: str) -> None:
            self.raw.update(used | {k})
            self.problem(why)

        for t, q, h in self.sums:
            used: Set[int] = set()
            if ins[q].mn == "b":
                exits = [x for x in range(t, q) if x in self.check and ins[x].conditional and self.index_of_label.get(ins[x].target, 0) > q]
                text = self._condition_text(exits[0], False, used) if len(exits) == 1 else None
                if text is None:
                    self.problem("the loop's exit is not a single comparison")
                    continue
                self.before.setdefault(t, []).append(("open", "for (;;) {"))
                self.lines[exits[0]] = [("line", f"if ({text}) {{"), ("line", "    break;"), ("line", "}")]
                self.after.setdefault(q, []).append(("close", "}"))
                control |= used | {exits[0], q}
            elif q in self.check and ins[q].conditional:
                text = self._condition_text(q, False, used)
                if text is None:
                    self.problem("the loop's condition is not a single comparison")
                    continue
                entry = t - 1 if t > 0 and ins[t - 1].mn == "b" and t < self.index_of_label.get(ins[t - 1].target, -1) <= q else None
                if entry is not None:
                    self.searched = self.searched or " - 1" in text
                    self.lines[entry] = [("open", f"while ({text}) {{")]
                    self.after.setdefault(q, []).append(("close", "}"))
                    control.add(entry)
                else:
                    self.before.setdefault(t, []).append(("open", "do {"))
                    self.after.setdefault(q, []).append(("close", f"}} while ({text});"))
                control |= used | {q}
            else:
                self.problem("the loop's back edge is not the check's")
        self.absorbed |= {k for k in control if ins[k].mn.startswith("b")}
        self.silent |= control - set(self.lines)

        responses: List[Tuple[int, int]] = []
        for first, last in self.final_blocks:
            s = first
            while s > 0 and (ins[s - 1].asm or (s - 1 in self.check and not ins[s - 1].conditional)) and not any(not self.labels[x].startswith("after") for x in self.labels_at.get(s, [])):
                s -= 1
            responses.append((s, last))
            for k in range(s, last + 1):
                if ins[k].asm:
                    for x in (ins[k].mem,):
                        if ins[k].mn == "stw" and x and x[1] == "r1" and x[0] in self.slots:
                            self.response_slots.add(x[0])
                elif self._volatile(k) == "stw":
                    self.response_slots.add(ins[k].mem[0])
        ordinary = [s for s in self.slots if s not in self.response_slots]
        inner = bool(self.response_slots) and len(responses) == 1 and (not ordinary or max(self.response_slots) < min(ordinary))
        if inner:
            self.inner_slots = sorted(self.response_slots, reverse=True)
        declare = [("line", f"volatile u32 {self.slots[s]};") for s in self.inner_slots] + [("line", "")] if inner else []
        starts = {s: last for s, last in responses}

        for k in sorted(self.check):
            i = ins[k]
            if k in control or k in self.lines:
                self.silent.add(k)
                continue
            used = set()
            if i.conditional:
                target = self.index_of_label.get(i.target, -1) if i.target else -1
                spin = k - 4 <= target <= k and all(x in self.check for x in range(target, k + 1))
                text = self._condition_text(k, not spin and (target in starts or k + 1 in starts), used)
                if text is None:
                    unrecognised(k, used, "a branch of the check is not a single comparison")
                    continue
                self.silent |= used
                if spin:
                    self.silent.update(range(target, k))
                    self.lines[k] = [("line", f"while ({text}) {{"), ("line", "}")]
                    self.absorbed.add(k)
                    self.whole_response = True
                elif target in starts and target > k:
                    self.lines[k] = [("open", f"if ({text}) {{")]
                    self.before.setdefault(target, []).append(("middle", "} else {"))
                    self.before[target] += declare
                    self.after.setdefault(starts[target], []).append(("close", "}"))
                    self.absorbed.add(k)
                    self.whole_response = True
                    j = target - 1
                    if ins[j].mn == "b" and self.index_of_label.get(ins[j].target, -1) == starts[target] + 1:
                        self.lines[j] = []
                        self.absorbed.add(j)
                elif k + 1 in starts:
                    last = starts[k + 1]
                    self.lines[k] = [("open", f"if ({text}) {{")] + declare
                    self.absorbed.add(k)
                    self.whole_response = True
                    j = last + 1
                    over = self.index_of_label.get(ins[j].target, -1) if j < n and ins[j].mn == "b" and ins[j].target else -1
                    if over > j and target == j + 1:
                        self.after.setdefault(last, []).append(("middle", "} else {"))
                        self.before.setdefault(over, []).insert(0, ("close", "}"))
                        self.lines[j] = []
                        self.absorbed.add(j)
                    else:
                        self.after.setdefault(last, []).append(("close", "}"))
                else:
                    self.fed = True
                    self.lines[k] = [("line", f"// if ({text}) goto {self.labels.get(i.target or '', '?')};")]
                continue
            if i.mn in COMPARES:
                continue
            if self._volatile(k) == "stw":
                value = self._read(k, i.ops[0], used)
                if has_raw(value):
                    unrecognised(k, used, "a value stored to a volatile local is not the check's")
                    continue
                self.silent |= used
                self.lines[k] = [("line", f"{self.slots[i.mem[0]]} = {show(value)};")]
                continue
            if not i.writes or not i.writes[0].startswith("r"):
                self.raw.add(k)
                self.problem(f"{i.mn} in the check")
                continue
            kind = self._classify(k)
            if kind == "temp":
                continue
            value = self._value(k, used)
            if has_raw(value):
                unrecognised(k, used, f"{i.mn} on a value that is not the check's" if value[0] != "r" or i.mn in BINARY or i.mn in IMMEDIATE else f"{i.mn} in the check")
                continue
            if kind == "out":
                self.silent |= used
                self.fed = True
                if value[0] == "b" and value[1] == ">>" and value[3] == constant(5) and value[2][0] == "u" and value[2][2][0] == "call":
                    value = ("b", "==", value[2][2][2], constant(0))
                # `a == b` compiles to `b - a`.
                if value[0] == "b" and value[1] in ("==", "!=") and value[3] == constant(0) and value[2][0] == "b" and value[2][1] == "-":
                    value = ("b", value[1], value[2][3], value[2][2])
                self.lines[k] = [("line", f"// {i.writes[0]} = {show(value)}; for the game")]
                continue
            name = self.web_name.get(self._find(k))
            if name is None:
                unrecognised(k, used, "a variable of the check without a part in the loop")
                continue
            self.silent |= used
            self.lines[k] = [("line", self._assignment(name, value))]
        self.silent -= self.raw
        for k in self.raw:
            self.lines.pop(k, None)
        for k in sorted(self.check):
            if k not in self.silent and k not in self.lines and k not in self.raw:
                self.raw.add(k)
                self.problem("an instruction of the check that no statement uses")
        if responses and not self.whole_response:
            self.problem("the branch to the response was not found")

    def _assignment(self, name: str, value: Expr) -> str:
        if value[0] == "b" and value[1] in COMPOUND and value[2] == ("v", name):
            return f"{name} {value[1]}= {show(value[3], value[1] if value[3][0] == 'c' else '')};"
        return f"{name} = {show(value)};"

    def _operands(self, i: Ins) -> str:
        mnemonic, _, operands = i.text.partition(" ")
        for old, label in self.labels.items():
            operands = re.sub(re.escape(old) + r"\b", label, operands)
        if i.mem and i.mem[1] == "r1" and i.mem[0] in self.slots and (i.asm or i.mn in ("lwz", "stw")):
            operands = re.sub(r"-?(?:0x[0-9a-fA-F]+|\d+)\(r1\)", self.slots[i.mem[0]], operands)
        return f"{mnemonic:7} {operands}".rstrip()

    def _asm_block(self, first: int, last: int) -> List[str]:
        out = ["asm {"]
        for position in range(self.ins[first].position, self.ins[last].position + 1):
            address, text = self.body[position]
            if address is None:
                out.append(f"{self.labels[text]}:")
            elif address in self.data:
                out.append(f"    opword  MF_WORD(0x{address - self.start:X})" if address in self.used else f"    opword  0x{self._word(address):08X}")
            else:
                out.append("    " + self._operands(next(i for i in self.ins[first : last + 1] if i.addr == address)))
        return out + ["}"]

    def render(self) -> List[str]:
        ins = self.ins
        out = [f"// {self.name}", f"// {self.unit}, 0x{self.start:08X}, {self.size} bytes"]
        out += ["// " + line.split(": ", 1)[1] for line in describe(self.result, self.analysis.symbols)]
        out.append(f"// {self.status()}")
        if self.searched:
            out.append("// in this kind of loop the order of the four declarations varies: search it (compare.py -p)")
        out += [f"#define MF_FUNCTION {identifier(self.name)}", "{"]
        for slot in sorted(self.slots, reverse=True):
            if slot not in self.inner_slots:
                out.append(f"    volatile u32 {self.slots[slot]};")
        names = set(self.web_name.values())
        for suffix in [""] + [str(x) for x in range(2, len(self.sums) + 1)]:
            out += [f"    u32 {name + suffix};" for name in LOCAL_ORDER if name + suffix in names]
        out += [f"    u32 {name};" for name in self.extra if name in names]
        out.append("")
        depth = 1
        referenced = {i.target for k, i in enumerate(ins) if i.target and k not in self.absorbed and not i.asm}

        def emit(items: List[Tuple[str, str]]) -> None:
            nonlocal depth
            for kind, text in items:
                if kind in ("close", "middle"):
                    depth = max(depth - 1, 1)
                out.append(("    " * depth + text).rstrip())
                if kind in ("open", "middle"):
                    depth += 1

        block_end = dict(self.blocks)
        k = 0
        while k < self.n:
            emit(self.before.get(k, []))
            for label in self.labels_at.get(k, []):
                if label in referenced or (not self.labels[label].startswith("after") and not any(i.target == label for i in ins)):
                    emit([("line", f"// {self.labels[label]}:")])
            if k in block_end:
                last = block_end[k]
                emit([("line", line) for line in self._asm_block(k, last)])
                for x in range(k + 1, last + 1):
                    emit(self.before.get(x, []) + self.after.get(x, []))
                k = last + 1
                continue
            if k in self.lines:
                emit(self.lines[k])
            elif k in self.raw:
                emit([("line", f"// NOT RECOGNISED: {self._operands(ins[k])}")])
            elif k not in self.silent:
                note = ""
                for loc, defs in self.rd[k].items():
                    webs = {self.web_name.get(self._find(d)) for d in defs if d in self.check}
                    if len(webs) == 1 and None not in webs:
                        note = f"    ({loc} is {webs.pop()})"
                emit([("line", f"// {self._operands(ins[k])}{note}")])
            emit(self.after.get(k, []))
            k += 1
        out += ["}", "#undef MF_FUNCTION"]
        return out

    def status(self) -> str:
        if not self.result["checksums"]:
            return "part: no checksum in this function, only the asm blocks are written"
        if self.problems:
            return "part: " + "; ".join(self.problems)
        if self.fed or not self.whole_response:
            return "the check whole, its result is used by the game: the expression stands in a comment"
        if self.extra:
            return f"whole, with {len(self.extra)} more {'local' if len(self.extra) == 1 else 'locals'} after the loop: where to declare them is a guess"
        return "whole"


class Printer:
    def __init__(self, version: str, analysis: Analysis) -> None:
        self.version, self.analysis = version, analysis
        self.listings: Dict[str, Dict[str, List[Tuple[Optional[int], str]]]] = {}

    def function(self, function: Tuple[int, int, str], result: Optional[Dict[str, Any]] = None, reuse: bool = False, inline: bool = True) -> Function:
        unit = unit_of(self.version, function[0]) or ""
        if unit not in self.listings:
            path = Path("build") / self.version / "asm" / Path(unit).with_suffix(".s")
            if not path.is_file():
                sys.exit(f"{path} not found (run the build first)")
            self.listings = {unit: read_listing(path)}
        body = self.listings[unit].get(function[2])
        if not body:
            sys.exit(f"{function[2]} not found in the listing of {unit}")
        if result is None:
            result = examine(self.analysis.dol, function, self.analysis.symbols)
        made = Function(self.analysis, unit, function, body, result, reuse, inline)
        return Function(self.analysis, unit, function, body, result, reuse, False) if made.impure else made


def survey(version: str, data: bytes, symbols_path: Path, jobs: Optional[int]) -> None:
    with Analysis(data, symbols_path, jobs) as analysis:
        results = analysis.run()
        printer = Printer(version, analysis)
        counts: Dict[str, int] = {}
        reasons: Dict[str, int] = {}
        for function, result in zip(analysis.protected, results):
            try:
                f = printer.function(function, result)
                f.render()
                status = f.status()
            except Exception as error:
                status = f"error: {type(error).__name__}: {error}"
            print(f"{function[2]}: {status}")
            head, _, rest = status.partition(": ")
            counts[head] = counts.get(head, 0) + 1
            for reason in rest.split("; ") if head == "part" else []:
                reasons[reason] = reasons.get(reason, 0) + 1
        print()
        print(f"{len(results)} protected functions")
        for head, count in sorted(counts.items(), key=lambda x: -x[1]):
            print(f"{count:5} {head}")
        for reason, count in sorted(reasons.items(), key=lambda x: -x[1]):
            print(f"{count:9} {reason}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Prints the MetaFortress check of a protected function as C in the canonical form.")
    parser.add_argument("version", type=str.upper, help="game ID, e.g. SUKE01")
    parser.add_argument("symbol", nargs="?", help="the function to print (a part of its symbol is enough if only one matches)")
    parser.add_argument("--survey", action="store_true", help="print one line per protected function: printed whole or not, and why not")
    parser.add_argument("--reuse", action="store_true", help="write the finish through the variables whose registers its temporaries sit in (limit = hash >> 10; hash ^= limit;)")
    parser.add_argument("--locals", action="store_true", help="give a value that is used twice after the loop a local (first = hash >> 5;) instead of writing it out at each use")
    parser.add_argument("--jobs", type=int, help="worker processes for the survey (default: one per core)")
    args = parser.parse_args()

    dol_path = Path("orig") / args.version / "sys" / "main.dol"
    symbols_path = Path("config") / args.version / "symbols.txt"
    for path in (dol_path, symbols_path):
        if not path.is_file():
            sys.exit(f"{path} not found (run this from the project root)")
    data = dol_path.read_bytes()
    if args.survey:
        survey(args.version, data, symbols_path, args.jobs)
        return
    if not args.symbol:
        parser.error("give a symbol or --survey")
    analysis = Analysis(data, symbols_path)
    found = [f for f in analysis.protected if f[2] == args.symbol] or [f for f in analysis.protected if args.symbol in f[2]]
    if len(found) != 1:
        sys.exit(f"{len(found)} protected functions match {args.symbol}" + "".join(f"\n  {f[2]}" for f in found[:20]))
    print("\n".join(Printer(args.version, analysis).function(found[0], reuse=args.reuse, inline=not args.locals).render()))


if __name__ == "__main__":
    main()
