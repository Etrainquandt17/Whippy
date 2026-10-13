#!/usr/bin/env python3
"""Marks as Matching in configure.py every unit that tools/compare.py calls complete in every version, once a scratch
link with it still reproduces the DOL.

    python tools/link_complete.py            # test and mark
    python tools/link_complete.py --dry      # only list the candidates
    python tools/link_complete.py --retry    # also try the units config/not_linkable.txt remembers
    python tools/link_complete.py --force src/a/B.cpp   # try a unit compare.py does not call complete

The link is the last word. compare.py judges a unit by the split object, and where the splitter got a relocation wrong
there, a unit that links identically is still reported as differing. --force is for those; give it sources, not all of src.
Units linked that way are listed in config/force_linked.txt, so that tools/status.py does not report them as broken.

A unit with functions the original link replaced by a branch has its look-alikes un-exported in symbols.txt, as
docs/code_merging.md describes. Units that fail the link are remembered in config/not_linkable.txt.

The scratch links are of the version build.ninja is configured for. Build every version afterwards: this marks
units, it does not prove the other versions.
"""
import argparse
import itertools
import re
import shutil
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Set, Tuple

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import aliases  # noqa: E402
import compare  # noqa: E402
import linktest  # noqa: E402

SCRATCH = linktest.SCRATCH / "pass"
CACHE = SCRATCH / "objects"
MEMO = ROOT / "config" / "not_linkable.txt"
FORCED = ROOT / "config" / "force_linked.txt"
MERGING = '    "-code_merging all",\n'
RETRY_ALONE = 16
LDFLAGS_HEAD = 'config.ldflags = [\n    "-fp hardware",\n    "-nodefaults",\n'
serial = itertools.count()


def check(source: Path, version: str) -> Tuple[Path, bool, List[str]]:
    """Returns whether compare.py calls the source complete, and the functions it found replaced by a branch."""
    out = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "compare.py"), "all", str(source)], capture_output=True, text=True, cwd=ROOT
    ).stdout
    branches = re.findall(rf"^{version}: replaced by a branch to a look-alike by the original link (\S+)$", out, re.M)
    # A unit whose functions all match, in order, is tried even when its data could not be compared: the link decides.
    summary = re.findall(r"(\d+) of (\d+) compiled functions match; the unit has (\d+)", out)
    count = len(compare.versions()) - out.count(compare.ABSENT)
    written = (
        len(summary) == count
        and all(a == b == c for a, b, c in summary)
        and "another order" not in out
        and "does not compile" not in out
    )
    return source, bool(count) and (out.count("the unit is complete") == count or written), branches


class Pass:
    def __init__(self, version: str, merging: bool) -> None:
        self.version = version
        self.merging = merging
        self.ranges = linktest.unit_ranges(version)

    def scratch(self, units: Iterable[str], obj: Optional[Path] = None) -> Tuple[bool, Optional[int]]:
        """Links with the units from source. Returns whether the DOL is identical and the first differing address."""
        out = SCRATCH / f"w{next(serial)}"
        flags = "" if self.merging else "-code_merging all"
        same, _, addresses = linktest.link(
            self.version, [u.rsplit(".", 1)[0] for u in units], out, cache=CACHE, obj=obj, ldflags=flags if obj else ""
        )
        shutil.rmtree(out, ignore_errors=True)
        return same, addresses[0] if addresses else None

    def unit_at(self, address: int, candidates: Set[str]) -> Optional[str]:
        """Returns the candidate that holds the address, or the nearest one ahead of it in that section."""
        section = next((r for r in self.ranges if r[0] <= address < r[1]), None)
        before = [
            r for r in self.ranges if r[0] <= address and r[3] in candidates and (section is None or r[2] == section[2])
        ]
        return before[-1][3] if before else None

    def halves(self, units: List[str], always: List[str], obj: Optional[Path]) -> List[str]:
        if not units:
            return []
        if self.scratch(always + units, obj)[0]:
            return units
        if len(units) == 1:
            return []
        half = len(units) // 2
        return self.halves(units[:half], always, obj) + self.halves(units[half:], always, obj)

    def linkable(self, units: List[str], always: List[str] = [], obj: Optional[Path] = None) -> List[str]:
        """Returns the units that link identically: all at once if that works, else each on its own, six at a time."""
        if not units:
            return []
        if self.scratch(always + units, obj)[0]:
            return units
        with ThreadPoolExecutor(6) as pool:
            alone = list(pool.map(lambda unit: self.scratch([unit], obj)[0], units))
        good = [unit for unit, ok in zip(units, alone) if ok]
        print("   ", len(good), "of", len(units), "link on their own", flush=True)
        # Units that link alone can still disturb each other. The first differing address names the one to drop.
        for _ in range(40):
            if not good:
                break
            same, address = self.scratch(always + good, obj)
            if same:
                return good
            unit = self.unit_at(address, set(good)) if address is not None else None
            print("    combined link differs at", hex(address) if address else None, "dropping", unit, flush=True)
            if unit is None:
                return self.halves(good, always, obj)
            good.remove(unit)
        return self.halves(good, always, obj) if good else []


def branch_targets(version: str) -> Dict[str, str]:
    """Returns, for each function the original link replaced by a branch, the look-alike it branches to."""
    targets = {}
    with open(ROOT / "orig" / version / "files" / "iuk.MAP", encoding="utf-8", errors="replace") as map_file:
        for line in map_file:
            if line.startswith("--> the function") and "will be replaced by a branch to" in line:
                fields = line.split()
                targets[fields[3]] = fields[-1]
            elif line.startswith(".init"):
                break
    return targets


def local_functions(obj: Path) -> Set[str]:
    """Returns the names of the functions an object defines with local binding."""
    data = obj.read_bytes()
    (shoff,) = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum, _ = struct.unpack_from(">HHH", data, 0x2E)
    sections = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]
    symtab = next(s for s in sections if s[1] == 2)
    strings = sections[symtab[6]][4]
    found = set()
    for i in range(symtab[5] // 16):
        name, _, _, info, _, shndx = struct.unpack_from(">IIIBBH", data, symtab[4] + i * 16)
        if info == 2 and shndx:
            found.add(data[strings + name : data.index(b"\0", strings + name)].decode("utf-8", "replace"))
    return found


def folded_statics(version: str, units: Iterable[str]) -> Dict[str, Set[str]]:
    """Returns, per unit, the survivors of the static functions the original link folded away.

    The linker script cannot stand in for a local symbol, so the linker has to fold such a function itself, and it
    only folds into a function that is not exported.
    """
    known = aliases.functions(version)
    following: Dict[str, List[Tuple[str, int]]] = {}
    for name, other, size in aliases.duplicates(version):
        following.setdefault(name, []).append((other, size))
    found: Dict[str, Set[str]] = {}
    for unit in units:
        obj = CACHE / (unit.rsplit(".", 1)[0].replace("/", "_") + ".o")
        if not obj.is_file():
            continue
        for name in local_functions(obj):
            survivors = {other for other, size in following.get(name, []) if other in known and known[other][1] == size}
            if survivors:
                found.setdefault(unit, set()).update(survivors)
    return found


def unexport(symbols_text: str, names: Iterable[str]) -> str:
    for name in names:
        pattern = re.compile(r"^(" + re.escape(name) + r" = [^\n]*?)( noexport)?$", re.M)
        symbols_text, count = pattern.subn(r"\1 noexport", symbols_text, count=1)
        if not count:
            print("   no symbols.txt line for", name)
    return symbols_text


def split_with(version: str, names: Iterable[str]) -> Path:
    """Splits the DOL again into the scratch directory with the given symbols un-exported. Returns the objects."""
    cfg = SCRATCH / "cfg"
    cfg.mkdir(parents=True, exist_ok=True)
    config = ROOT / "config" / version
    symbols = unexport((config / "symbols.txt").read_text(encoding="utf-8"), names)
    (cfg / "symbols.txt").write_text(symbols, encoding="utf-8", newline="\n")
    relative = cfg.relative_to(ROOT).as_posix()
    yml = (config / "config.yml").read_text(encoding="utf-8")
    yml = yml.replace(f"symbols: config/{version}/symbols.txt", f"symbols: {relative}/symbols.txt")
    (cfg / "config.yml").write_text(yml, encoding="utf-8", newline="\n")
    out = SCRATCH / "split"
    shutil.rmtree(out, ignore_errors=True)
    subprocess.run(
        [str(ROOT / "build" / "tools" / "dtk.exe"), "dol", "split", f"{relative}/config.yml", out.relative_to(ROOT).as_posix()],
        capture_output=True,
        cwd=ROOT,
    )
    return out / "obj"


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--dry", action="store_true", help="list the candidates and stop")
    parser.add_argument("--retry", action="store_true", help="try the remembered failures again")
    parser.add_argument("--force", action="store_true", help="try the given sources whatever compare.py says of them")
    parser.add_argument("paths", nargs="*", help="sources or directories to look at (default: all of src)")
    args = parser.parse_args()

    configure = ROOT / "configure.py"
    text = configure.read_text(encoding="utf-8")
    version = linktest.ninja()[0]
    roots = [Path(p).resolve() for p in args.paths] or [ROOT / "src"]
    sources = sorted(
        {p for root in roots for p in ([root] if root.is_file() else root.rglob("*")) if p.suffix in linktest.EXTENSIONS}
    )
    with ThreadPoolExecutor(8) as pool:
        results = list(pool.map(lambda source: check(source, version), sources))

    skipped = set(MEMO.read_text(encoding="utf-8").split()) if MEMO.exists() else set()
    forced = set(FORCED.read_text(encoding="utf-8").split()) if FORCED.exists() else set()
    incomplete = set()
    plain: List[str] = []
    stubbed: Dict[str, List[str]] = {}
    for source, complete, branches in results:
        unit = source.relative_to(ROOT / "src").as_posix()
        if not complete:
            incomplete.add(unit)
        if not complete and unit not in forced and f'Object(Matching, "{unit}"' in text:
            print("WARNING: linked but no longer complete:", unit)
        if unit in skipped and not (args.retry or args.force):
            continue
        if (complete or args.force) and f'Object(NonMatching, "{unit}"' in text:
            if branches:
                stubbed[unit] = branches
            else:
                plain.append(unit)
    print(len(plain), "new complete units:", " ".join(plain))
    print(len(stubbed), "new complete units with branches:", " ".join(stubbed))
    if args.dry or not (plain or stubbed):
        return

    # Objects are compiled once per pass. One from an earlier pass may predate a change to its source or its flags.
    shutil.rmtree(CACHE, ignore_errors=True)
    same, message, _ = linktest.link(version, [], SCRATCH / "baseline")
    if not same:
        sys.exit(f"the tree as it is does not link identically, so nothing can be tested: build {version} first\n{message[-600:]}")
    merging = MERGING in text
    run = Pass(version, merging)
    good = run.linkable(list(plain))
    rejected = [unit for unit in plain if unit not in good]

    targets = branch_targets(version)
    survivors = {unit: {targets[name] for name in branches if name in targets} for unit, branches in stubbed.items()}
    for unit, names in folded_statics(version, rejected).items():
        print("   ", unit, "has folded static functions; trying with", " ".join(sorted(names)), "un-exported")
        survivors[unit] = names
    rejected = [unit for unit in rejected if unit not in survivors]
    if survivors:
        obj = split_with(version, set().union(*survivors.values()))
        stub_good = run.linkable(list(survivors), good, obj)
        # The split above un-exports the look-alikes of every candidate, also of those that cannot link yet,
        # and that alone can make a good unit differ. Try what failed again, one by one, on a split that has
        # only the names of the units known to be good.
        left = [unit for unit in survivors if unit not in stub_good]
        if 0 < len(left) <= RETRY_ALONE:
            for unit in left:
                names = set().union(*(survivors[each] for each in stub_good + [unit]))
                if run.scratch(good + stub_good + [unit], split_with(version, names))[0]:
                    print("   ", unit, "links without the other candidates' look-alikes un-exported", flush=True)
                    stub_good.append(unit)
        rejected += [unit for unit in survivors if unit not in stub_good]
        if stub_good:
            for each in compare.versions():
                # A function's look-alike is not the same one in every version.
                if each == version:
                    names = set().union(*(survivors[unit] for unit in stub_good))
                else:
                    other = branch_targets(each)
                    names = {other[name] for unit in stub_good for name in stubbed.get(unit, []) if name in other}
                    statics = folded_statics(each, [unit for unit in stub_good if unit not in stubbed])
                    names |= set().union(*statics.values()) if statics else set()
                path = ROOT / "config" / each / "symbols.txt"
                path.write_text(unexport(path.read_text(encoding="utf-8"), names), encoding="utf-8", newline="\n")
                print(each, "un-exported", len(names), "look-alikes:", " ".join(sorted(names))[:300])
            good += stub_good
            merging = True

    retried = set(plain) | set(stubbed)
    remembered = (skipped - retried) | set(rejected)
    if rejected:
        print("NOT LINKABLE (scratch link differs or fails):", " ".join(rejected))
    if args.force:
        # A unit that was only tried on request is not one that compares complete and fails.
        remembered = skipped - set(good)
    if remembered != skipped:
        MEMO.write_text("".join(unit + "\n" for unit in sorted(remembered)), encoding="utf-8", newline="\n")
    # Read again: the pass is long, and configure.py may have been edited meanwhile.
    fresh = configure.read_text(encoding="utf-8")
    if merging and MERGING not in fresh:
        assert fresh.count(LDFLAGS_HEAD) == 1
        fresh = fresh.replace(LDFLAGS_HEAD, LDFLAGS_HEAD + MERGING)
    newly_forced = forced | (set(good) & incomplete)
    if newly_forced != forced:
        FORCED.write_text("".join(unit + "\n" for unit in sorted(newly_forced)), encoding="utf-8", newline="\n")
    for unit in good:
        fresh = fresh.replace(f'Object(NonMatching, "{unit}"', f'Object(Matching, "{unit}"')
    configure.write_bytes(fresh.encode("utf-8"))
    print("marked", len(good))


if __name__ == "__main__":
    main()
