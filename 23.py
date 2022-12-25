#!/usr/sbin/python
from collections import defaultdict
from itertools import count

DIRECTIONS = [
    [(-1,  0), (-1,  1), (-1, -1)],  # N, NE, NW
    [(1,  0), (1,  1), (1, -1)],  # S, SE, SW
    [(0, -1), (-1, -1), (1, -1)],  # W, NW, SW
    [(0,  1), (-1,  1), (1,  1)],  # E, NE, SE
]

CARDINALS = sorted(set([point for row in DIRECTIONS for point in row]))


def has_neigb(p) -> bool:
    pj, pi = p
    return any((pj + cj, pi + ci) in Q for cj, ci in CARDINALS)


def get_destination(n, src):
    if not has_neigb(src):
        return None
    (sj, si) = src
    for t in range(len(DIRECTIONS)):
        C = DIRECTIONS[(n+t) % len(DIRECTIONS)]
        if all((sj + cj, si + ci) not in Q for cj, ci in C):
            dj, di = C[0]
            dst = (sj+dj, si+di)
            assert (dst not in Q)
            return dst
    return None


def step1(n) -> dict:
    moves = defaultdict(list)
    for src in Q:
        if not has_neigb(src):
            continue
        dst = get_destination(n, src)
        if dst:
            moves[dst].append(src)
    return moves


def step2(moves):
    global Q
    for dst, values in moves.items():
        if len(values) == 1:
            src = values[0]
            assert (src != dst)
            Q.remove(src)
            Q.add(dst)


def count_empty(Q):
    miny, minx = min([p[0] for p in Q]), min([p[1] for p in Q])
    maxy, maxx = max([p[0] for p in Q]), max([p[1] for p in Q])
    # empty = 0
    # gap = 0
    # for j in range(miny-gap, maxy+1+gap):
    #     for i in range(minx-gap, maxx+1+gap):
    #         empty += ((j, i) not in Q)
    return (maxy - miny + 1) * (maxx - minx + 1) - len(Q)


def load_data():
    L = [line.rstrip() for line in open('input/23.in').readlines()]
    Q = set()
    for j, row in enumerate(L):
        if '#' not in row:
            continue
        for i, val in enumerate(row):
            if val == '#':
                Q.add((j, i))
    return Q


def evolve(rounds):
    global Q
    Q = load_data()
    for n in count():
        desire = step1(n)
        if len(desire) == 0:
            return "stop", n+1, count_empty(Q)
        step2(desire)
        if rounds == (n+1):
            break
    return "limit", rounds, count_empty(Q)


type, n, empty = evolve(10)
print(f"{type=}, {n=}, {empty=}")

type, n, empty = evolve(-1)
print(f"{type=}, {n=}, {empty=}")
