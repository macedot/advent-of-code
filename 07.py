#!/usr/sbin/python

current_dir = []
sizes = dict()


def chdir(path: str):
    global current_dir
    if path == "/":
        current_dir = []
    elif path == "..":
        current_dir.pop()
    else:
        current_dir.append(path)


def add_size(size: int):
    global current_dir
    tmp_dir = current_dir.copy()
    while len(tmp_dir) >= 0:
        cwd = "/" + '/'.join(tmp_dir)
        if not cwd in sizes:
            sizes[cwd] = 0
        sizes[cwd] += size
        if cwd == "/":
            break
        tmp_dir.pop()


for line in open(0).readlines():
    line = line.rstrip().split()
    if line[0] == "$":
        if line[1] == "cd":
            chdir(line[2])
    else:
        if line[0] != "dir":
            add_size(int(line[0]))

ans1 = 0
MAX_SIZE = 100000

MIN_SPACE = 30000000
TOTAL_SPACE = 70000000
TOTAL_SIZE = sizes["/"]
FREE_SPACE = TOTAL_SPACE - TOTAL_SIZE
MIN_DELETE = MIN_SPACE - FREE_SPACE
ans2 = TOTAL_SPACE

for k, v in sizes.items():
    if v <= MAX_SIZE:
        ans1 += v
    if v >= MIN_DELETE:
        if v < ans2:
            ans2 = v

print(1, ans1)
print(2, ans2)
