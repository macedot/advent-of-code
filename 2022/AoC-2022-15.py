#!/usr/sbin/python
from AoC import load_input
from collections import defaultdict
from itertools import count


def get_xy(line):
    x, y = [int(aux.split("=")[1])
            for aux in line.split(",")]
    return (x, y)


def def_value():
    return 0


G = defaultdict(def_value)
D = dict()
S = set()
B = set()
for line in load_input(__file__):
    (sx, sy), (bx, by) = map(get_xy, line.strip().split(":"))
    s = (sx, sy)
    b = (bx, by)
    S.add(s)
    B.add(b)
    D[s] = abs(sx - bx) + abs(sy - by)
    G[s] = 'S'
    G[b] = 'B'


def dump_grid():
    X = set([p[0] for p in G])
    Y = set([p[1] for p in G])
    x_min, x_max = min(X), max(X)
    y_min, y_max = min(Y), max(Y)
    for j in range(y_min - 1, y_max + 2):
        print(f"{j:3d} ", end='')
        for i in range(x_min - 1, x_max + 2):
            p = (i, j)
            print(G[p] if p in G else '.', end='')
        print()


def solve1(y_target):
    res = 0
    for x in range(int(-5e6), int(5e6)):
        good = True
        for sx, sy in S:
            d = abs(sx - x) + abs(sy - y_target)
            if d <= D[(sx, sy)]:
                good = False
                break
        if not good:
            if (x, y_target) not in B:
                res += 1
    return res


# print(solve1(10))
#print(solve1(2000000))


def solve2(val_max):
    for y in range(0, 1+val_max):
        for x in range(0, 1+val_max):
            for sx, sy in S:
                d = abs(sx - x) + abs(sy - y)
                if d <= D[(sx, sy)]:
                    return (x, y)


print(solve2(4000000))

# def process(y_ans):
#     ans1 = set()
#     for s in S:
#         x, y = s
#         last = False
#         for n in count():
#             for j in range(-n, n + 1):
#                 yj = y+j
#                 # if yj != y_ans:
#                 #     continue
#                 aj = n - abs(j)
#                 for xi in range(x-aj, x + aj + 1):
#                     # if xi in ans1:
#                     #     continue
#                     p = (xi, yj)
#                     if p in B:
#                         last = True
#                     else:
#                         if p not in G:
#                             G[p] = '#'
#                         if yj == y_ans:
#                             ans1.add(xi)
#             if last:
#                 break  # while
#     dump_grid()
#     return ans1


# ans1 = process(10)
# print("ans1 =", len(ans1), ans1)
