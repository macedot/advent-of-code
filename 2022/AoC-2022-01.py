from AoC import load_input

tot = 0
totals = [0]
for line in load_input(__file__):
    line = line.rstrip()
    if line == "":
        totals.append(tot)
        tot = 0
    else:
        tot += int(line)

print("1,", max(totals))
totals.sort(reverse=True)
print("2,", sum(totals[:3]), totals[:3])
