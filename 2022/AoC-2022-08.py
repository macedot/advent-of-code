from AoC import load_input

grid = []
for line in load_input(__file__):
    line = list(line.rstrip())
    grid.append(line)


SIZE_H = len(grid)
SIZE_W = len(grid[0])


def is_visible(ix, jx):
    X = grid[jx][ix]
    if X > max([grid[jx][i] for i in range(0, ix)]):
        return True
    if X > max([grid[jx][i] for i in range(ix+1, SIZE_W)]):
        return True
    if X > max([grid[j][ix] for j in range(0, jx)]):
        return True
    if X > max([grid[j][ix] for j in range(jx+1, SIZE_H)]):
        return True
    return False


def scenic_score(ix, jx):
    X = grid[jx][ix]
    score = 1
    s = 0
    for i in range(ix-1, -1, -1):
        #print("L", f"{jx=},{i=}", grid[jx][i], )
        s += 1
        if grid[jx][i] >= X:
            break
    score *= s
    
    s = 0
    for i in range(ix+1, SIZE_W):
        #print("R", f"{jx=},{i=}", grid[jx][i])
        s += 1
        if grid[jx][i] >= X:
            break
    score *= s

    s = 0
    for j in range(jx-1, -1, -1):
        #print("T", f"{j=},{ix=}", grid[j][ix])
        s += 1
        if grid[j][ix] >= X:
            break
    score *= s

    s = 0
    for j in range(jx+1, SIZE_H):
        #print("B", f"{j=},{ix=}", grid[j][ix])
        s += 1
        if grid[j][ix] >= X:
            break
    score *= s

    return score


ans1 = 2 * (SIZE_H + SIZE_W - 2)
ans2 = 0
for j in range(1, SIZE_H-1):
    for i in range(1, SIZE_W-1):
        ans1 += is_visible(i, j)
        ans2 = max(ans2, scenic_score(i, j))
print(f"{ans1=}")
print(f"{ans2=}")
