from AoC import load_input


class Knot:
    x: int = 0
    y: int = 0

    def __repr__(self):
        return (f'Elem({self.x},{self.y})')

    def set(self, x, y):
        self.x = x
        self.y = y

    def move(self, qx, qy):
        self.x += qx
        self.y += qy


class Rope:
    size_knots: int = 0
    knots: list = []
    places = set()

    def __init__(self, size_knots: int):
        self.places = set()
        self.size_knots = size_knots
        self.knots = [Knot() for _ in range(size_knots)]
        self.update_places_tail()

    def __repr__(self):
        return (f'Rope({self.knots})')

    def update_places_tail(self):
        self.places.add((self.knots[-1].x, self.knots[-1].y))

    # https://github.com/jonathanpaulson/AdventOfCode/blob/master/2022/9.py
    @staticmethod
    def adjust_tail(H, T):
        dr = (H.x - T.x)
        dc = (H.y - T.y)
        x, y = H.x, H.y
        if abs(dr) <= 1 and abs(dc) <= 1:
            return T.x, T.y
        if abs(dr) >= 2:
            x = H.x - 1 if T.x < H.x else H.x + 1
        if abs(dc) >= 2:
            y = H.y - 1 if T.y < H.y else H.y + 1
        return x, y

    def move(self, qx, qy, qt):
        for _ in range(qt):
            self.knots[0].move(qx, qy)
            for i in range(0, self.size_knots - 1):
                res = self.adjust_tail(self.knots[i], self.knots[i+1])
                self.knots[i+1].x, self.knots[i+1].y = res
            self.update_places_tail()


rope2 = Rope(2)
rope10 = Rope(10)

DX = {'L': -1, 'R': 1, 'U': 0, 'D': 0}
DY = {'L': 0, 'R': 0, 'U': -1, 'D': 1}

for line in load_input(__file__):
    d, v = line.rstrip().split()
    rope2.move(DX[d], DY[d], int(v))
    rope10.move(DX[d], DY[d], int(v))

print(f"ans1={len(rope2.places)}")
print(f"ans2={len(rope10.places)}")
