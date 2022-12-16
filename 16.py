#!/usr/sbin/python
from AoC import load_input
from re import compile
import functools

# Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
pattern = compile(
    r"^Valve ([A-Z][A-Z]) has flow rate=(\d+); .+ valve.? (.+)$")
lines = [pattern.findall(line)[0]
         for line in load_input(__file__)]

F = dict()
G = dict()
for l in lines:
    v, f, c = l
    F[v] = int(f)
    G[v] = [x.strip() for x in c.split(",")]


@functools.lru_cache(maxsize=None)
def maxflow(cur, min_left, opened=()):
    # https://github.com/nthistle/advent-of-code/blob/master/2022/day16/day16.py
    global F, G
    if min_left < 2 or cur in opened:
        return 0
    f_max = 0
    val = (min_left - 1) * F[cur]
    cur_opened = tuple(sorted(opened + (cur,)))
    for adj in G[cur]:
        if val != 0:
            f_max = max(f_max, val + maxflow(adj, min_left - 2, cur_opened))
        f_max = max(f_max, maxflow(adj, min_left - 1, opened))
    return f_max

print("ans1 =", maxflow("AA", 30))
#print("ans2 =", maxflow2("AA", 26))

# import sys, re
# lines = [re.split('[\\s=;,]+', x) for x in sys.stdin.read().splitlines()]
# G = {x[1]: set(x[10:]) for x in lines}
# F = {x[1]: int(x[5]) for x in lines if int(x[5]) != 0}
# I = {x: 1<<i for i, x in enumerate(F)}
# T = {x: {y: 1 if y in G[x] else float('+inf') for y in G} for x in G}
# for k in T:
#     for i in T:
#         for j in T:
#             T[i][j] = min(T[i][j], T[i][k]+T[k][j])
# def visit(v, budget, state, flow, answer):
#     answer[state] = max(answer.get(state, 0), flow)
#     for u in F:
#         newbudget = budget - T[v][u] - 1
#         if I[u] & state or newbudget <= 0: continue
#         visit(u, newbudget, state | I[u], flow + newbudget * F[u], answer)
#     return answer    
# total1 = max(visit('AA', 30, 0, 0, {}).values())
# visited2 = visit('AA', 26, 0, 0, {})
# total2 = max(v1+v2 for k1, v1 in visited2.items() 
#                    for k2, v2 in visited2.items() if not k1 & k2)
# print(total1, total2)