import os
from pathlib import Path


def load_input(base_name: str = __file__):
    input_path = Path(os.path.abspath(os.path.dirname(base_name)))
    input_name = os.path.basename(base_name)
    input_file = (input_path / input_name).with_suffix('.input')
    with open(input_file, "r") as f:
        res = f.readlines()
    return res


# Rock <- Paper <- Scissors
lhs = {'A': 1, 'B': 2, 'C': 3}
rhs = {'X': 1, 'Y': 2, 'Z': 3}

res1 = {
    'A': {'X': rhs['X'] + 3, 'Y': rhs['Y'] + 6, 'Z': rhs['Z'] + 0},
    'B': {'X': rhs['X'] + 0, 'Y': rhs['Y'] + 3, 'Z': rhs['Z'] + 6},
    'C': {'X': rhs['X'] + 6, 'Y': rhs['Y'] + 0, 'Z': rhs['Z'] + 3},
}

res2 = {
    'A': {'X': rhs['Z'] + 0, 'Y': rhs['X'] + 3, 'Z': rhs['Y'] + 6},
    'B': {'X': rhs['X'] + 0, 'Y': rhs['Y'] + 3, 'Z': rhs['Z'] + 6},
    'C': {'X': rhs['Y'] + 0, 'Y': rhs['Z'] + 3, 'Z': rhs['X'] + 6},
}

ans1 = 0
ans2 = 0
for line in load_input():
    l, r = line.rstrip().split()
    #l, r = lhs[l], rhs[r]
    #ans1 += r + (r - l + 1) % 3 * 3
    ans1 += res1[l][r]
    #ans2 += (r - 1) * 3 + (l + r) % 3 + 1
    ans2 += res2[l][r]
print(f'{ans1=}')
print(f'{ans2=}')
