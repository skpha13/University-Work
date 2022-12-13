def citire_date():
    l = []
    with open("pb6_evenimente.txt") as f:
        lines = f.readlines()
        for line in lines:
            name = line.strip().split(maxsplit=1)[1]
            line = line.replace('-',' ')
            line = line.replace(':',' ')
            temp = line.split()
            l.append((temp[0],temp[1],temp[2],temp[3],) + (name,))
    return l

def greedy(evenimente):
    evenimente.sort(key = lambda x: (x[0],x[1]))
    lista = []
    lista.append([])
    lista[0].append(evenimente[0])
    k = 1
    for i in range(1,len(evenimente)):
        for sala in range(len(lista)):
            if evenimente[i][0] > lista[sala][-1][2]:
                lista[sala].append(evenimente[i])
                break
            elif evenimente[i][0] == lista[sala][-1][2] and evenimente[i][1] >= lista[sala][-1][3]:
                lista[sala].append(evenimente[i])
                break
        else:
            lista.append([])
            lista[sala + 1].append(evenimente[i])
    k = 1
    sala = 0
    return lista

def afisare(lista):
    with open("pb6_sali.txt",'w') as g:
        g.write(f"Numar minim de sali: {len(lista)}")
        g.write("\n\n")
        for i in range(len(lista)):
            g.write(f"Sala {i+1}:")
            g.write("\n")
            for j in range(len(lista[i])):
                g.write(str(lista[i][j]))
                if j != len(lista[i]) - 1:
                    g.write(', ')
            g.write("\n\n")

afisare(greedy(citire_date()))
