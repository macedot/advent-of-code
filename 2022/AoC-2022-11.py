from AoC import load_input
from math import prod


class Monkey:
    def __init__(self, id: int):
        self.id = id
        self.items = []
        self.operation = ""
        self.test = 0
        self.test_true = 0
        self.test_false = 0
        self.inspect = 0

    def __lt__(self, other):
        return self.inspect < other.inspect

    def __eq__(self, other):
        return self.inspect == other.inspect

    def __repr__(self) -> str:
        return f"Monkey[{self.id}, {self.items}, {self.operation}, {self.test}, {self.test_true}, {self.test_false}, {self.inspect}]"


def my_eval(exp: str, val: int):
    a, op, b = exp.split()
    x = val if a == "old" else int(a)
    y = val if b == "old" else int(b)
    return x + y if op == "+" else x * y


def proc_monkey(id: int, worried: bool = True):
    global monkeys, lcm

    for item in monkeys[id].items:
        value = my_eval(monkeys[id].operation, item)
        final = (value // 3) if worried else value % lcm
        dst = monkeys[id].test_true if final % monkeys[id].test == 0 else monkeys[id].test_false
        #assert (dst != id)
        monkeys[dst].items.append(final)
        monkeys[id].inspect += 1
    monkeys[id].items = []


def load_monkey(line):
    global last_id
    op, param = line
    if "Monkey" in op:
        _, last_id = op.strip().split()
        last_id = int(last_id)
        monkeys[last_id] = Monkey(last_id)
    elif "Starting items" in op:
        monkeys[last_id].items = [int(i.strip()) for i in param.split(",")]
    elif "Operation" in op:
        operation = [i.strip() for i in param.split("=")]
        #assert (operation[0] == "new")
        monkeys[last_id].operation = operation[1].strip()
    elif "Test" in op:
        monkeys[last_id].test = int(param.split()[2])
    elif "If true" in op:
        monkeys[last_id].test_true = int(param.split()[3])
    elif "If false" in op:
        monkeys[last_id].test_false = int(param.split()[3])


def proc_rounds(rounds: int, worried: bool):
    global last_id, monkeys, div, lcm

    last_id = 0
    monkeys = [Monkey(id) for id in range(10)]

    for line in load_input(__file__):
        line = line.strip().split(":")
        if len(line) < 2:
            continue
        load_monkey(line)

    # https://github.com/jonathanpaulson/AdventOfCode/blob/master/2022/11.py
    div = set()
    for m in monkeys:
        if m.test > 0:
            div.add(m.test)
    lcm = prod(div)

    for _ in range(rounds):
        for idx in range(len(monkeys)):
            proc_monkey(idx, worried)

    sorted_monkeys = sorted(monkeys, reverse=True)
    # for monkey in sorted_monkeys:
    #     print(monkey)

    ans = (sorted_monkeys[0].inspect * sorted_monkeys[1].inspect)
    print(f"{ans=}")


proc_rounds(20, True)
proc_rounds(10000, False)
