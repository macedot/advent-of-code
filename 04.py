from AoC import load_input

ans1 = 0
ans2 = 0
for line in load_input(__file__):
    A, B = line.rstrip().split(",")
    Al, Ar = [int(x) for x in A.split("-")]
    Bl, Br = [int(x) for x in B.split("-")]
    ans1 += ((Al <= Bl and Br <= Ar) or (Bl <= Al and Ar <= Br))
    ans2 += not ((Ar < Bl) or (Br < Al))
print(f'{ans1=}')
print(f'{ans2=}')
