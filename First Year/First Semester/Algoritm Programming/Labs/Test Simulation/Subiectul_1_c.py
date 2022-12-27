def citire_numere():
    l = []
    with open("Subiectul_1_c_numere.in") as f:
        for line in f:
            temp = [int(x) for x in line.split()]
            l.append(temp)
    return l

M = citire_numere()
for line in M:
    print(*line)