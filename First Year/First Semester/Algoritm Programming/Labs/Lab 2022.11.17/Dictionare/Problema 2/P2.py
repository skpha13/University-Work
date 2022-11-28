file = open(input("Nume fisier: "))
rime = open("rime.txt","w")
p = int(input("Numar: "))

d = {}
for line in file:
    l_cuv = line.split()
    for cuv in l_cuv:
        if cuv[-p:] not in d:
            d[cuv[-p:]] = [1,[cuv]]
        else:
            d[cuv[-p:]][0] += 1
            d[cuv[-p:]][1].append(cuv)
 
l = sorted(d.items(), key=lambda x:x[1],reverse=True)
lista = [sorted(l[i][1][1],reverse=True) for i in range(len(l))]

for i in lista:
    for j in i:
        rime.write(str(j) + " ")
    rime.write("\n")