#!/usr/bin/env python3
"""Lists the state of every source below a directory, by tools/compare.py's verdict over every version.

    python tools/status.py                   # all of src
    python tools/status.py src/RVL_SDK/os    # one directory, or single files
    python tools/status.py --open            # leave out the linked units

States: linked (Matching in configure.py), complete (ready for tools/link_complete.py), functions (every function
matches, data or order still differs), partial, broken (does not compile). The numbers are matching functions,
compiled functions and the unit's functions, in the version where the fewest match.
"""
import argparse
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import List, Tuple

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import compare  # noqa: E402

EXTENSIONS = (".cpp", ".c", ".cp")


def check(source: Path) -> Tuple[Path, str, Tuple[int, int, int]]:
    out = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "compare.py"), "all", str(source)], capture_output=True, text=True, cwd=ROOT
    ).stdout
    count = len(compare.versions()) - out.count(compare.ABSENT)
    summary = [tuple(map(int, m)) for m in re.findall(r"(\d+) of (\d+) compiled functions match; the unit has (\d+)", out)]
    worst = min(summary) if summary else (0, 0, 0)
    if "does not compile" in out or len(summary) < count or not count:
        state = "broken"
    elif out.count("the unit is complete") == count:
        state = "complete"
    elif all(a == b == c for a, b, c in summary) and "another order" not in out:
        state = "functions"
    else:
        state = "partial"
    return source, state, worst


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("paths", nargs="*", help="sources or directories (default: src)")
    parser.add_argument("--open", action="store_true", help="leave out the linked units")
    args = parser.parse_args()
    configure = (ROOT / "configure.py").read_text(encoding="utf-8")
    forced_list = ROOT / "config" / "force_linked.txt"
    forced = set(forced_list.read_text(encoding="utf-8").split()) if forced_list.is_file() else set()
    roots = [Path(p).resolve() for p in args.paths] or [ROOT / "src"]
    sources: List[Path] = sorted(
        {p for root in roots for p in ([root] if root.is_file() else root.rglob("*")) if p.suffix in EXTENSIONS}
    )
    with ThreadPoolExecutor(8) as pool:
        results = list(pool.map(check, sources))
    tally = {}
    for source, state, (matching, compiled, total) in results:
        unit = source.relative_to(ROOT / "src").as_posix()
        if f'Object(Matching, "{unit}"' in configure:
            # A unit in config/force_linked.txt links identically although compare.py objects to it.
            accepted = ("complete", "functions", "partial") if unit in forced else ("complete", "functions")
            state = "linked" if state in accepted else f"LINKED BUT {state.upper()}"
        tally[state] = tally.get(state, 0) + 1
        if args.open and state == "linked":
            continue
        print(f"{state:10s} {matching:4d} {compiled:4d} {total:4d}  {unit}")
    print(", ".join(f"{count} {state}" for state, count in sorted(tally.items())))


if __name__ == "__main__":
    main()
