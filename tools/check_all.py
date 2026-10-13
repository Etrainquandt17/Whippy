#!/usr/bin/env python3
"""Builds the DOL of every version and checks it against the original, then leaves the tree configured for the first.

    python tools/check_all.py            # DOL only
    python tools/check_all.py --full     # everything, so that build/<ID>/report.json is fresh
"""
import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import compare  # noqa: E402


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--full", action="store_true", help="build every target, not only the DOL")
    args = parser.parse_args()
    versions = compare.versions()
    failed = []
    for version in reversed(versions):
        subprocess.run([sys.executable, "configure.py", "--version", version], cwd=ROOT, check=True, capture_output=True)
        target = [] if args.full else [f"build/{version}/ok"]
        result = subprocess.run(["ninja", *target], cwd=ROOT, capture_output=True, text=True)
        lines = [line for line in (result.stdout + result.stderr).splitlines() if line.strip()]
        ok = result.returncode == 0
        print(f"{version}: {'OK' if ok else 'FAILED'}")
        if not ok:
            failed.append(version)
            interesting = [line for line in lines if not line.startswith(("[", "#   ")) and "Linker Warning" not in line]
            print("\n".join(interesting[-25:]))
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
