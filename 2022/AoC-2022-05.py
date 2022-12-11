from AoC import load_input, chunk

BOX_SIZE = 10
box1 = [list() for _ in range(BOX_SIZE)]
box2 = [list() for _ in range(BOX_SIZE)]


def load(line: str):
    data = chunk(str(line.rstrip()))
    for i, x in enumerate(data):
        x = x.strip()
        if x == "":
            continue
        box1[i].insert(0, x[1])
        box2[i].insert(0, x[1])


def move1(qt, src, dst):
    for _ in range(int(qt)):
        box1[dst].append(box1[src].pop())


def move2(qt, src, dst):
    box2[dst] += box2[src][-qt:]
    del box2[src][-qt:]


def print_box(box):
    for lst in box:
        print(lst)
    print()


def print_box_top(task, box):
    print(task, ",", end='', sep='')
    for lst in box:
        print(lst[-1] if len(lst) > 0 else '', end='')
    print()


for orig_line in load_input(__file__):
    orig_line = orig_line.rstrip()
    line = [s for s in orig_line.rstrip().split(' ') if s]
    if len(line) == 0:
        continue
    if line[0] == "1":
        box1 = box1[:len(line)]
        box2 = box2[:len(line)]
        continue
    if line[0] == "move":
        move1(int(line[1]), int(line[3]) - 1, int(line[5]) - 1)
        move2(int(line[1]), int(line[3]) - 1, int(line[5]) - 1)
    else:
        load(orig_line)

# print_box(box1)
# print_box(box2)

print_box_top(1, box1)
print_box_top(2, box2)
