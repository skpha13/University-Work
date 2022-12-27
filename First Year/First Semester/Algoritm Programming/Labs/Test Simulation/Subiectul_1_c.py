def citire_numere():
    l = []
    with open("Subiectul_1_c_numere.in") as f:
        for line in f:
            temp = [int(x) for x in line.split()]
            l.append(temp)
    return l

def prelucrare_lista(l):
    for i in range(len(l)):
        aux = minn = 0
        while aux == minn:
            minn = min(l[i])
            l[i].remove(minn)
            aux = min(l[i])

    temp = []
    for line in l:
        temp.append(len(line))
    m = min(temp)
    for i in range(len(l)):
        if len(l[i]) > 1:
            l[i] = l[i][:m]      

M = citire_numere()
prelucrare_lista(M)
for line in M:
    print(*line)