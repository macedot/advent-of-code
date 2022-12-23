#!/usr/sbin/python
from functools import cmp_to_key
from math import prod


def compare(L, R):
    if type(L) is int and type(R) is int:
        if L < R:
            return -1
        if L > R:
            return 1
        return 0
    L = L if type(L) is list else [L]
    R = R if type(R) is list else [R]
    for l, r in zip(L, R):
        res = compare(l, r)
        if res:
            return res
    sL, sR = len(L), len(R)
    if sL < sR:
        return -1
    if sL > sR:
        return 1
    return 0


c = 0
idx = 0
comp = [0, 0]
ans1 = []
full = []
for line in open(0).readlines():
    line = line.strip()
    if len(line) == 0:
        continue
    comp[c] = eval(line)
    full.append(comp[c])
    c += 1
    if c == 2:
        idx += 1
        res = compare(comp[0], comp[1])
        if res < 0:
            ans1.append(idx)
        c = 0

print("ans1", sum(ans1), ans1)

cmp_key = cmp_to_key(compare)
BEGIN = [[2]]
END = [[6]]
full.append(BEGIN)
full.append(END)
full.sort(key=cmp_key)
ans2 = []
for i, f in enumerate(full):
    if f == BEGIN or f == END:
        ans2.append(i+1)
print("ans2", prod(ans2), ans2)
