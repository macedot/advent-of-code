#!/usr/sbin/python
# https://github.com/juanplopes/advent-of-code-2022/blob/main/day20.py
T = [int(x) for x in open(0).readlines()]
SIZE_T = len(T)


def mixing(runs, key):
    I = list(range(SIZE_T))
    for _ in range(runs):
        for i in range(SIZE_T):
            idx = I.index(i)
            I.pop(idx)
            I.insert((idx + T[i] * key) % len(I), i)
    zero = I.index(T.index(0))
    return sum(T[I[(zero+i) % len(I)]] * key for i in (1000, 2000, 3000))


print(mixing(1, 1))
print(mixing(10, 811589153))
