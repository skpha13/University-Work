file = open("elevi.in")
lista = []
for line in file:
    l = line.split(maxsplit=3)
    lista.append(l)
for i in range(len(lista)):
    lista[i][3] = [int(x) for x in lista[i][3].split()]

def b(cnp,l):
    # ce se intampla daca nota este 10?? creste la 11 sau nu?
    aux = -1
    for i in range(len(l)):
        if cnp == l[i][0]:
            aux = l[i][3][0] + 1
            l[i][3][0] += 1
            break
    if aux != -1:
        return aux
    else:
        return None

def c(cnp,lnote,l):
    aux = -1
    for i in range(len(l)):
        if cnp == l[i][0]:
            aux = 1
            for x in lnote:
                l[i][3].append(x)
            temp = l[i][3]
            break
    if aux != -1:
        return temp
    else:
        return None

def d(cnp,l):
    for i in range(len(l)):
        if cnp == l[i][0]:
            l.pop(i)
            break

def e():
    def medie(l):
        return sum(l)/len(l)
    f = open("eveli.out","w")
    l = []
    for line in lista:
        l.append(line[1:])
    l.sort(key=lambda x:(-medie(x[2]),x[0],x[1]))
    for line in l:
        for x in line:
            f.write(str(x)+" ")
        f.write("\n")

def f(l):
    import random
    litere = "qwertyuiopasdfghjklzxcvbnm"
    for i in range(len(l)):
        cod = ""
        part1 = ""
        for x in range(3):
            part1 += random.choice(litere)
        part2 = random.randint(100,999)
        cod = part1 + str(part2)
        l[i].append(cod)

#print(b(input("CNP: "),lista))

#print(c(input("CNP: "),[10,8],lista))

#d(input("CNP: "),lista)
#print(lista)

#e()

#f(lista)
#print(lista)