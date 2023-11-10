#!/usr/sbin/python
import re
M, K = [line.rstrip() for line in open(0).read().split("\n\n")]
M = [l.rstrip() for l in M.split("\n")]
SIZE_H = len(M)
SIZE_W = max(map(len, M))
print(SIZE_H, SIZE_W)
for idx in range(SIZE_H):
    M[idx] = M[idx].ljust(SIZE_W, ' ')
N = [int(x) for x in re.findall('\d+', K)]
R = [x for x in re.findall('L|R', K)]
D = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def at(p):
    py, px = p
    return M[py][px]


def add(p, d):
    return (p[0] + d[0], p[1] + d[1])


def adjust_2D(x, size):
    if x < 0:
        return size-1
    elif x >= size:
        return 0
    return x


def next_point(p, d):
    qy, qx = add(p, d)
    py = adjust_2D(qy, SIZE_H)
    px = adjust_2D(qx, SIZE_W)
    return (py, px)


def is_wall(p):
    return at(p) == '#'


def get_dir(D, idx):
    return D[idx % len(D)]


def out_of_bound(p):
    y, x = p
    return (y < 0 or
            y >= SIZE_H or
            x < 0 or
            x >= SIZE_W or
            at(p) == ' ')


def next_valid1(p, d):
    last = p
    new = next_point(p, d)
    while at(new) == ' ':
        new = next_point(new, d)
    if is_wall(new):
        return last
    return new


def adjust_on_cube(p, d):
    # https://github.com/mrphlip/aoc/blob/master/2022/22.png
    py, px = p
    if d == D[0]:  # right

        if 0 <= py < 50:  # i
            nx = 100 - 1
            ny = 150 - py - 1
            d = D[2]  # go left
        elif 50 <= py < 100:  # g
            nx = 100 + (py - 50)
            ny = 50 - 1
            d = D[3]  # go up
        elif 100 <= py < 150:  # i
            nx = 150 - 1
            ny = 150 - py - 1
            d = D[2]  # go left
        elif 150 <= py < 200:  # f
            nx = 50 + (py - 150)
            ny = 150 - 1
            d = D[3]  # go up

    elif d == D[1]:  # down

        if 0 <= px < 50:  # l
            nx = px + 100
            ny = 0
            d = D[1]  # go down
        elif 50 <= px < 100:  # f
            nx = 50 - 1
            ny = 150 + (px - 50)
            d = D[2]  # go left
        elif 100 <= px < 150:  # g
            nx = 100 - 1
            ny = 50 + (px - 100)
            d = D[2]  # go left

    elif d == D[2]:  # left

        if 0 <= py < 50:  # j
            nx = 0
            ny = 150 - py - 1
            d = D[0]  # go right
        elif 50 <= py < 100:  # h
            nx = py - 50
            ny = 100
            d = D[1]  # go down
        elif 100 <= py < 150:  # j
            nx = 50
            ny = 150 - py - 1
            d = D[0]  # go right
        elif 150 <= py < 200:  # k
            nx = 50 + (py - 150)
            ny = 0
            d = D[1]  # go down

    elif d == D[3]:  # up

        if 0 <= px < 50:  # h
            nx = 50
            ny = 50 + px
            d = D[0]  # go right
        elif 50 <= px < 100:  # k
            nx = 0
            ny = 150 + (px - 50)
            d = D[0]  # go right
        elif 100 <= px < 150:  # l
            nx = px - 100
            ny = 200 - 1
            d = D[3]  # go up
    else:
        assert (False)

    assert (not out_of_bound((ny, nx)))

    return (ny, nx), d


def next_valid2(p, d):
    pold, dold = p, d
    new = add(p, d)
    if out_of_bound(new):
        new, d = adjust_on_cube(new, d)
    if is_wall(new):
        return pold, dold
    return new, d


def solve1(p):
    idx_d = 0
    print('solve1:START', p, D[idx_d])
    for idx in range(len(N)):
        d = get_dir(D, idx_d)
        for _ in range(N[idx]):
            p = next_valid1(p, d)
        if idx < len(R):
            idx_d += 1 if R[idx] == 'R' else 3
            idx_d %= len(D)
    print('solve1:END', p, d)
    py, px = p
    return 1000 * (py+1) + 4 * (px+1) + D.index(d)


def solve2(p):
    idx_d = 0
    print('solve2:START', p, D[idx_d])
    for idx in range(len(N)):
        d = get_dir(D, idx_d)
        for _ in range(N[idx]):
            newd = d
            new = add(p, d)
            if out_of_bound(new):
                new, newd = adjust_on_cube(new, d)
            if is_wall(new):
                break
            p, d = new, newd
            assert (at(p) == '.')
        idx_d = D.index(d)
        if idx < len(R):
            idx_d += 1 if R[idx] == 'R' else 3
            idx_d %= len(D)
    print('solve2:END', p, d, idx_d, D.index(d))
    py, px = p
    return 1000 * (py+1) + 4 * (px+1) + D.index(d)


start = (0, 0)
while at(start) == " ":
    start = add(start, D[0])
print("ans1 =", solve1(start))
print("ans2 =", solve2(start))
