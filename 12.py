from AoC import load_input
from collections import deque

heightmap = []
for line in load_input(__file__):
    line = line.strip()
    heightmap.append([x for x in line])

BASE = ord('a')
SIZE_H = len(heightmap)
SIZE_W = len(heightmap[0])
diagram = [[0 for _ in range(SIZE_W)] for _ in range(SIZE_H)]

for j in range(SIZE_H):
    for i in range(SIZE_W):
        if heightmap[j][i] == "S":
            diagram[j][i] = 1
        elif heightmap[j][i] == "E":
            diagram[j][i] = 26
        else:
            diagram[j][i] = ord(heightmap[j][i]) - BASE + 1


# https://github.com/jonathanpaulson/AdventOfCode/blob/master/2022/12.py
def bfs(part):
    Q = deque()
    for j in range(SIZE_H):
        for i in range(SIZE_W):
            if (part == 1 and heightmap[j][i] == 'S') or (part == 2 and diagram[j][i] == 1):
                Q.append(((j, i), 0))
    S = set()
    while Q:
        (j, i), d = Q.popleft()
        if (j, i) in S:
            continue
        S.add((j, i))
        if heightmap[j][i] == 'E':
            return d
        for dj, di in [(-1, 0), (0, 1), (1, 0), (0, -1)]:
            jj = j+dj
            ii = i+di
            if 0 <= jj < SIZE_H and 0 <= ii < SIZE_W and diagram[jj][ii] <= 1+diagram[j][i]:
                Q.append(((jj, ii), d+1))


print(bfs(1))
print(bfs(2))
