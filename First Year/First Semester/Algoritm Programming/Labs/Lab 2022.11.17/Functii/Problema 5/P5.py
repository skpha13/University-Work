def negative_positive(L):
    l_neg = []
    l_poz = []
    for x in L:
        if x < 0:
            l_neg.append(x)
        elif x > 0:
            l_poz.append(x)
    return l_neg,l_poz

name = input("Fisier: ")
file = open(name)
fa = open(name,'a')
lista = []
for line in file:
    lnr = [int(x) for x in line.split()]
    for x in lnr:
        lista.append(x)

l1,l2 = negative_positive(lista)
l1.sort()
l2.sort()

fa.write("\n")
for x in l1:
    fa.write(str(x) + " ")
fa.write("\n")
for x in l2:
    fa.write(str(x) + " ")
