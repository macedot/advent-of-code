#!/usr/sbin/python
def find_string_unique(line, size) -> int:
    for i in range(len(line)):
        l = line[i:i+size]
        s = ''.join(sorted(line[i:i+size]))
        u = ''.join(sorted(set(l)))
        if s == u:
            return i+size
    return -1


for line in open(0).readlines():
    line = line.rstrip()
    print(1, find_string_unique(line, 4))
    print(2, find_string_unique(line, 14))
