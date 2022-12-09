from AoC import load_input

box = dict()


def move(qt: int, src: int, dst: int):
    print(qt, src, dst)


def load(line: str):
    data = chunk(str(line.rstrip()))
    for i, x in enumerate(data):
        x = x.strip()
        if x == "":
            continue
        idx = i+1
        if idx not in box:
            box[idx] = list()
        box[idx].append(x)


def chunk(string: str, length: int = 4):
    return [string[0+i:length+i] for i in range(0, len(string), length)]


for orig_line in load_input(__file__):
    line = [s for s in orig_line.rstrip().split(' ') if s]
    if len(line) == 0:
        continue
    if line[0] == "1":
        continue
    if line[0] == "move":
        move(line[1], line[3], line[5])
    else:
        load(orig_line)


print(1, [box[k][-1] for k in sorted(box.keys())])
