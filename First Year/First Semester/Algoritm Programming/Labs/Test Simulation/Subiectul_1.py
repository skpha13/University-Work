def a(fisier):
    with open(fisier) as f:
        l = []
        for line in f:
            temp = [int(x) for x in line.split()]
            l.append(temp)
    return l

def prelucrare_lista(lista):
    for i in range(len(lista)):
        minn = min(lista[i])
        while minn in lista[i]:
            lista[i].remove(minn)
    
    m = min(lista,key=lambda x:len(x))
    m = len(m)
    for i in range(len(lista)):
        lista[i] = lista[i][:m]

L = a("numere.in")
prelucrare_lista(L)
for line in L:
    print(*line)

L = a("numere.in")
k = int(input("k = "))
sol = set()
ok = False
for line in L:
    for ele in line:
        if len(str(ele)) == k:
            sol.add(ele)
            ok = True
sol = list(sol)
sol.sort(reverse=True)
temp = [str(x) for x in sol]
temp = " ".join(temp)
with open("cifre.out",'w') as g:
    if ok == True:
        g.writelines(temp)
        g.write(" ")
    else:
        g.write("Imposibil!")