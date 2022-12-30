#!/usr/sbin/python

def solve(START, stop, step):
    P = O = set([START])
    while True:
        N = set()
        for r, c in P:
            for x, y in ((r, c), (r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                if (x, y) == stop:
                    return step
                if (0 <= x < HEIGHT and 0 <= y < WIDTH
                   and G[x][(y - step) % WIDTH] != ">"
                   and G[x][(y + step) % WIDTH] != "<"
                   and G[(x - step) % HEIGHT][y] != "v"
                   and G[(x + step) % HEIGHT][y] != "^"):
                    N.add((x, y))
        P = N if N else O
        step += 1


G = [row[1:-1] for row in open('input/24.in').read().splitlines()[1:-1]]
HEIGHT, WIDTH = len(G), len(G[0])
START, FINISH = (-1, 0), (HEIGHT, WIDTH - 1)

print(s1 := solve(START, FINISH, 1))
print(solve(START, FINISH, solve(FINISH, START, s1)))
