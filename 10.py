#!/usr/sbin/python

def divide_chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i: i + n]


reg_X = 1
cycle = 1

# ans1
monitor = [20, 60, 100, 140, 180, 220]
signal_strength = []

# ans2
SCREEN_H = 6
SCREEN_W = 40
screen = ['.' for _ in range(SCREEN_H * SCREEN_W)]


def output_screen():
    global screen
    for row in divide_chunks(screen, SCREEN_W):
        for col in row:
            print(col, end='')
        print()


def get_pixel_value(idx):
    global reg_X
    return "#" if idx in [reg_X-1, reg_X, reg_X+1] else "."


def proc_cycle():
    global cycle, reg_X, monitor, signal_strength, screen
    if cycle in monitor:
        #print(cycle, reg_X, cycle * reg_X)
        signal_strength.append(cycle * reg_X)
    screen[cycle-1] = get_pixel_value((cycle - 1) % SCREEN_W)


def proc_noop():
    global cycle
    proc_cycle()
    cycle += 1


def proc_addx(arg: int):
    global cycle, reg_X
    proc_cycle()
    cycle += 1
    proc_cycle()
    reg_X += arg
    cycle += 1


for line in open(0).readlines():
    line = line.rstrip().split()
    if line[0] == "noop":
        proc_noop()
    elif line[0] == "addx":
        proc_addx(int(line[1].strip()))

print(f"ans1={sum(signal_strength)}", signal_strength)

print("ans2")
output_screen()
