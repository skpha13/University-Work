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

def d(M):
    k = int(input("k = "))
    cifre = []
    for i in M:
        for j in i:
            if len(str(j)) == k:
                cifre.append(j)

    with open("cifre.out",'w') as g:
        if len(cifre) == 0:
            g.write("Imposibil!")
        else:
            cifre = set(cifre)
            cifre = list(cifre)
            cifre.sort(reverse=True)
            print(cifre)
            for i in cifre:
                g.write(str(i))
                g.write(" ")


M = citire_numere()
d(M)
prelucrare_lista(M)
for line in M:
    print(*line)

