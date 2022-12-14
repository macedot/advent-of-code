#!/usr/sbin/python
from AoC import load_input


class Point:
    x: int
    y: int

    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y

    def __repr__(self) -> str:
        return f"Point({self.x},{self.y})"

    def __eq__(self, __o: object) -> bool:
        return self.x == __o.x and self.y == __o.y


SAND_PT = Point(500, 0)
EXTRA_X = 200
base_x = 300

lst = []
for line in load_input(__file__):
    line = line.strip()
    pts = []
    for pair in line.split("->"):
        x, y = [int(k) for k in pair.strip().split(",")]
        base_x = min(x, base_x)
        pts.append(Point(x, y))
    lst.append(pts)
# print(lst)

size_w = 0
size_h = 0
for pts in lst:
    for p in pts:
        p.x -= base_x
        size_w = max(size_w, p.x+EXTRA_X)
        size_h = max(size_h, p.y+1)
#print(size_w, size_h)

SAND_PT.x -= base_x


def print_grid():
    for j in range(size_h):
        print(f"{j:3d} ", end='')
        for i in range(size_w):
            print(G[j][i], end='')
        print()
    print("*" * (4 + size_w))


def move_sand(part, s: Point):
    while True:
        d = s.y+1
        if part == 1 and d >= size_h:
            return None
        if G[d][s.x] == '.':
            s.y += 1
        else:
            if G[d][s.x-1] == '.':
                s.y += 1
                s.x -= 1
            elif G[d][s.x+1] == '.':
                s.y += 1
                s.x += 1
            else:
                return s


def let_it_sand(part, dump: bool = False):
    global size_h, G
    if part == 2:
        size_h += 2

    G = [['.' for _ in range(size_w)] for _ in range(size_h)]
    for pts in lst:
        for idx in range(len(pts) - 1):
            p1, p2 = pts[idx], pts[idx+1]
            jb, je = min(p1.y, p2.y), max(p1.y, p2.y)
            for j in range(jb, 1 + je):
                ib, ie = min(p1.x, p2.x), max(p1.x, p2.x)
                for i in range(ib, 1 + ie):
                    G[j][i] = '#'
    if part == 2:
        for i in range(size_w):
            G[size_h-1][i] = '#'

    if dump:
        print_grid()

    count = 0
    while True:
        try:
            s = move_sand(part, Point(SAND_PT.x, SAND_PT.y))
        except:
            print_grid()
            raise Exception
        if (part == 1 and s is None):
            break
        G[s.y][s.x] = 'o'
        count += 1
        if (part == 2 and s == SAND_PT):
            break

    if dump:
        print_grid()

    return count


ans1 = let_it_sand(1)
print(f"{ans1=}")

ans2 = let_it_sand(2)
print(f"{ans2=}")
