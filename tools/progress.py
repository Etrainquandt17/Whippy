"""Prints the build report's totals for each version. Usage: final_numbers.py [VERSION...]"""
import json
import sys
from pathlib import Path

for version in sys.argv[1:] or ["SUKE01", "SUKK01"]:
    path = Path("build") / version / "report.json"
    if not path.exists():
        print(version, "no report")
        continue
    report = json.load(open(path))
    m = report["measures"]

    def n(key):
        return int(m.get(key, 0))

    print(
        f"{version}: code {n('matched_code')}/{n('total_code')} = {100 * n('matched_code') / n('total_code'):.3f}%"
        f"  functions {n('matched_functions')}/{n('total_functions')} = {100 * n('matched_functions') / n('total_functions'):.3f}%"
        f"  data {n('matched_data')}/{n('total_data')} = {100 * n('matched_data') / max(1, n('total_data')):.3f}%"
        f"  linked code {n('complete_code')}/{n('total_code')} = {100 * n('complete_code') / n('total_code'):.3f}%"
        f"  units {n('complete_units')}/{n('total_units')}"
    )
    for category in report.get("categories", []):
        c = category["measures"]
        total = int(c.get("total_code", 0))
        if total:
            print(f"    {category.get('name', category.get('id'))}: {100 * int(c.get('matched_code', 0)) / total:.3f}% of {total} bytes, linked {100 * int(c.get('complete_code', 0)) / total:.3f}%")
