#!/usr/sbin/python
from AoC import load_input
from re import compile
from multiprocessing.dummy import Pool as ThreadPool
from itertools import cycle


def load_data():
    G = dict()
    pattern = compile(r"-?\d+")
    for line in load_input(__file__):
        sx, sy, bx, by = map(int, pattern.findall(line))
        d = abs(sx - bx) + abs(sy - by)
        G[(sx, sy, bx, by)] = d
    return G


def solve1(y_target):
    global G
    known = set()
    intervals = []
    for p in G:
        sx, sy, bx, by = p
        d = G[p]
        o = d - abs(sy - y_target)
        if o < 0:
            continue
        lx = sx - o
        hx = sx + o
        intervals.append([lx, hx])
        if by == y_target:
            known.add(bx)

    # merge intervals - https://raw.githubusercontent.com/hyper-neutrino/advent-of-code/main/2022/day15p1.py
    intervals.sort()
    q = [intervals[0]]
    for lo, hi in intervals[1:]:
        _, qhi = q[-1]
        if lo > qhi + 1:
            q.append([lo, hi])
        else:
            q[-1][1] = max(qhi, hi)

    candidate = set()
    for lo, hi in intervals:
        for x in range(lo, hi + 1):
            if x not in known:
                candidate.add(x)
    return len(candidate)


def solve2_ex(param):
    global G
    Y, limit = param
    intervals = []
    for p in G:
        sx, sy, _, _ = p
        d = G[p]
        o = d - abs(sy - Y)
        if o < 0:
            continue
        lx = sx - o
        hx = sx + o
        intervals.append([lx, hx])

    # merge intervals
    intervals.sort()
    q = [intervals[0]]
    for lo, hi in intervals[1:]:
        _, qhi = q[-1]
        if lo > qhi + 1:
            q.append([lo, hi])
        else:
            q[-1][1] = max(qhi, hi)

    x = 0
    for lo, hi in q:
        if x < lo:
            return (x * 4000000 + Y)
        x = max(x, hi + 1)
        if x > limit:
            break

    pass


def solve2(limit):
    pool = ThreadPool(10)
    results = pool.map(solve2_ex, zip(range(1+limit), cycle([limit])))
    pool.close()
    pool.join()
    return set(results)


G = load_data()
# print("ans1 =", solve1(10)) # .ex
print("ans1 =", solve1(2000000))
print("ans2 =", solve2(4000000))
