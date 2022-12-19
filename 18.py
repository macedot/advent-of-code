#!/usr/sbin/python
from collections import deque
from AoC import load_input
# https://github.com/juanplopes/advent-of-code-2022/blob/main/day18.py
cubes = set(tuple(map(int, line.strip().split(",")))
            for line in load_input(__file__))
mins, maxs = [min(x)-1 for x in zip(*cubes)], [max(x)+1 for x in zip(*cubes)]

# ans1 = 0
# for (x, y, z) in cubes:
#     ans1 += (x+1, y, z) not in cubes
#     ans1 += (x-1, y, z) not in cubes
#     ans1 += (x, y+1, z) not in cubes
#     ans1 += (x, y-1, z) not in cubes
#     ans1 += (x, y, z+1) not in cubes
#     ans1 += (x, y, z-1) not in cubes
# print(f"{ans1=}")


def neighbors(x, y, z):
    yield from ((x+1, y, z), (x, y+1, z), (x, y, z+1))
    yield from ((x-1, y, z), (x, y-1, z), (x, y, z-1))


total1 = sum(n not in cubes
             for c in cubes
             for n in neighbors(*c))
total2 = 0
Q, visited = deque([tuple(mins)]), set(cubes)
while len(Q):
    for cube in neighbors(*Q.popleft()):
        if not all(a <= x <= b for a, b, x in zip(mins, maxs, cube)):
            continue
        total2 += cube in cubes
        if cube in visited:
            continue
        visited.add(cube)
        Q.append(cube)
print(total1, total2)
