from AoC import load_input
from string import ascii_lowercase, ascii_uppercase

letters = ascii_lowercase + ascii_uppercase
values = [x for x in range(1, 1 + len(letters))]
priority = dict(zip([*letters], values))

ans1 = 0
ans2 = 0
idx = 0
group = []
for line in load_input(__file__):
    line = line.rstrip()
    mid = int(len(line) / 2)
    l, r = line[:mid], line[mid:]
    for x in [*l]:
        if x in r:
            ans1 += priority[x]
            #print(l, r, x, priority[x])
            break
    group.append(line)
    if len(group) == 3:
        # print(group)
        for x in [*group[0]]:
            if x in group[1] and x in group[2]:
                ans2 += priority[x]
                break
        group.clear()
print(f'{ans1=}')
print(f'{ans2=}')
