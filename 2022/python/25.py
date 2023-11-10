#!/usr/sbin/python
VALS = "=-012"
def snafu2dec(num):
    return sum([(VALS.index(c) - 2) * (5 ** i) for i, c in enumerate(reversed(num))])
def dec2snafu(num):
    ans = ''
    while num:
        d = (num + 2) % 5 - 2
        ans = VALS[d+2] + ans
        num = (num - d) // 5
    return ans
L = [row.rstrip() for row in open('input/25.in').read().splitlines()]
tot = sum(map(snafu2dec, L))
print(f'{tot=}')
ans = dec2snafu(tot)
print(f'{ans=}')
