import os
from pathlib import Path


def load_input(base_name: str = __file__):
    input_path = Path(os.path.abspath(os.path.dirname(base_name)))
    input_name = os.path.basename(base_name)
    input_file = (input_path / input_name).with_suffix('.input')
    with open(input_file, "r") as f:
        res = f.readlines()
    return res


tot = 0
totals = [0]
for line in load_input():
    line = line.rstrip()
    if line == "":
        totals.append(tot)
        tot = 0
    else:
        tot += int(line)

print("1,", max(totals))
totals.sort(reverse=True)
print("2,", sum(totals[:3]), totals[:3])
