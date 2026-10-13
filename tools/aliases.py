#!/usr/bin/env python3
"""Lists the functions the original link folded away, each with the address of the copy that survived.

    python tools/aliases.py SUKE01            # summary
    python tools/aliases.py SUKE01 --lcf      # assignments for the linker script
    python tools/aliases.py SUKE01 --write    # config/SUKE01/ldscript.lcf from config/ldscript.lcf

The original link removed about 4,500 functions that were identical to another
one (docs/code_merging.md). Nothing in the DOL carries their names, so source
that calls one of them cannot link against the split objects. An assignment in
the linker script gives the name back, at the address of the surviving copy.
"""

import argparse
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

ROOT = Path(__file__).resolve().parent.parent


def functions(version: str) -> Dict[str, Tuple[int, int]]:
    """Returns address and size of every function in symbols.txt."""
    found = {}
    pattern = re.compile(r"^(\S+) = \.\w+:0x([0-9A-F]+); // type:function size:0x([0-9A-F]+)")
    with open(ROOT / "config" / version / "symbols.txt", encoding="utf-8") as symbols:
        for line in symbols:
            m = pattern.match(line)
            if m:
                found[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
    return found


def duplicates(version: str) -> List[Tuple[str, str, int]]:
    """Returns the linker's own account: (folded function, the one it duplicates, size)."""
    found = []
    pattern = re.compile(r"--> (?:duplicated code: symbol )?(\S+) is duplicated by (\S+), size = (\d+)")
    with open(ROOT / "orig" / version / "files" / "iuk.MAP", encoding="utf-8", errors="replace") as map_file:
        for line in map_file:
            if line.startswith("-->"):
                m = pattern.match(line)
                if m:
                    found.append((m.group(1), m.group(2), int(m.group(3))))
            elif line.startswith(".init"):
                break
    return found


def aliases(version: str) -> Tuple[Dict[str, int], List[str]]:
    """Returns the address for each removed function, and the names that could not be settled."""
    known = functions(version)
    following: Dict[str, List[str]] = {}
    sizes: Dict[str, int] = {}
    for name, other, size in duplicates(version):
        following.setdefault(name, [])
        if other not in following[name]:
            following[name].append(other)
        sizes[name] = size
    found: Dict[str, int] = {}
    unsettled = []
    for name in following:
        if name in known:
            continue
        seen = {name}
        frontier = list(following[name])
        targets = set()
        while frontier:
            other = frontier.pop()
            if other in seen:
                continue
            seen.add(other)
            # A function that was replaced by a branch is still in the DOL, four bytes long.
            if other in known and known[other][1] == sizes[name]:
                targets.add(known[other][0])
            else:
                frontier.extend(following.get(other, []))
        if len(targets) == 1:
            found[name] = targets.pop()
        else:
            unsettled.append(name)
    return found, unsettled


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("version", help="game ID such as SUKE01")
    parser.add_argument("--lcf", action="store_true", help="print linker script assignments")
    parser.add_argument("--write", action="store_true", help="write the version's linker script template")
    args = parser.parse_args()
    version = args.version.upper()
    found, unsettled = aliases(version)
    lines = []
    for name, address in sorted(found.items(), key=lambda item: (item[1], item[0])):
        quoted = name if re.fullmatch(r"\w+", name) else f'"{name}"'
        lines.append(f"    {quoted} = 0x{address:08X};")
    text = "\n".join(lines) + "\n"
    if args.lcf:
        print(text, end="")
        return
    if args.write:
        marker = "    $ALIASES\n"
        template = (ROOT / "config" / "ldscript.lcf").read_text(encoding="utf-8")
        if template.count(marker) != 1:
            sys.exit("config/ldscript.lcf has no $ALIASES line")
        out = ROOT / "config" / version / "ldscript.lcf"
        out.write_text(template.replace(marker, text), encoding="utf-8", newline="\n")
        print(f"wrote {out.relative_to(ROOT).as_posix()} with {len(lines)} assignments")
        return
    print(f"{args.version}: {len(found)} removed functions have one surviving copy, {len(unsettled)} could not be settled")
    for name in unsettled[:20]:
        print("   ", name)


if __name__ == "__main__":
    sys.exit(main())
