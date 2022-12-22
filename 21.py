#!/usr/sbin/python
T = [line.strip().split(":") for line in open(0).readlines()]
D = {v: x.strip() for v, x in T}


def solve1(D: dict, exp):
    if ' ' not in exp:
        return int(exp)
    lhs, op, rhs = exp.split(" ")
    return int(eval("{} {} {}".format(solve1(D, D[lhs]), op, solve1(D, D[rhs]))))


print("ans1 =", solve1(D, D['root']))


def solve2(D):
    lhs, op, rhs = D['root'].split(" ")
    exp = "{} - {}".format(lhs, rhs)
    s = solve1(D, exp)
    nmin, nmax = -abs(s), abs(s)
    while True:
        n = int((nmin + nmax) // 2)
        D['humn'] = str(n)
        s = solve1(D, exp)
        if s > 0:
            nmin = n
        elif s < 0:
            nmax = n
        else:
            return n


print("ans2 =", solve2(D))
