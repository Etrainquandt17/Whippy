#!/usr/bin/env python3
"""Lists the game units that have no source file yet, smallest first.

python tools/unwritten.py [unit path prefix] [--version SUKE01]

Each line is the unit's code size in bytes, its number of functions, and its path. The size is what
the original link left: a unit of 72 bytes with four functions has three of them folded away or
replaced by a branch. Library units are left out.
"""

import argparse
import bisect
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LIBS = (
    "nw4r/",
    "RVL_SDK/",
    "MSL_C/",
    "MSL_C++/",
    "Runtime/",
    "MetroTRK/",
    "homebuttonLib/",
    "libms/",
    "nrel/",
    "Mobiclip/",
    "mobiclip/",
)


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("prefix", nargs="?", default="")
    parser.add_argument("--version", default="SUKE01")
    args = parser.parse_args()
    config = ROOT / "config" / args.version

    units = {}
    unit = None
    for line in (config / "splits.txt").read_text().splitlines():
        if line and not line[0].isspace() and line.endswith(":"):
            unit = line[:-1]
        m = re.match(r"\s+\.text\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
        if m and unit:
            units[unit] = (int(m.group(1), 16), int(m.group(2), 16))

    starts = []
    for line in (config / "symbols.txt").read_text().splitlines():
        m = re.match(r"\S+ = \.text:0x([0-9A-F]+); // type:function", line)
        if m:
            starts.append(int(m.group(1), 16))
    starts.sort()

    rows = []
    for name, (a, b) in units.items():
        if name.startswith(LIBS) or not re.search(r"\.(cpp|c)$", name):
            continue
        if not name.startswith(args.prefix) or (ROOT / "src" / name).exists():
            continue
        n = bisect.bisect_left(starts, b) - bisect.bisect_left(starts, a)
        rows.append((b - a, n, name))
    rows.sort()

    lines = ["%d game units without a source, %d bytes" % (len(rows), sum(r[0] for r in rows)), ""]
    count = Counter()
    size = Counter()
    depth = args.prefix.rstrip("/").count("/") + 2 if args.prefix else 3
    for bytes_, _, name in rows:
        parts = name.split("/")[:-1]
        d = "/".join(parts[:depth]) if parts else "."
        count[d] += 1
        size[d] += bytes_
    lines += ["%4d units %7d bytes  %s" % (n, size[d], d) for d, n in count.most_common(60)]
    lines.append("")
    lines += ["%6d %3d  %s" % row for row in rows]
    try:
        print("\n".join(lines))
        sys.stdout.flush()
    except OSError:
        # The reader closed the pipe (`| head`).
        sys.stderr.close()


if __name__ == "__main__":
    main()
