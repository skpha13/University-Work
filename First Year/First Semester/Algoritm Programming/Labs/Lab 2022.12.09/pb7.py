def citire_date():
    with open("pb7_obiecte.txt") as f:
        m = int(f.readline().strip())
        l = [(i+1,int(line.strip().split()[0]),int(line.strip().split()[1])) for i,line in enumerate(f.readlines())]

    return m,l

def greedy(greutate,obiecte):
    for i in range(len(obiecte)):
        obiecte[i] += (round(obiecte[i][2]/obiecte[i][1],2),)
    obiecte.sort(key = lambda x: -x[3])

    sol = []
    for obj in obiecte:
        if obj[1] <= greutate:
            sol.append((*obj[:-1],100.00))
            greutate -= obj[1]
        else:
            sol.append((*obj[:-1],round((100*greutate)/obj[1],2)))
            break
    return sol

def afisare(rez):
    with open("pb7_rucsac.txt",'w') as  g:
        castig = 0
        for i in rez:
            castig += i[2]
        g.write(f"Castig maxim: {castig}\n\n")
        for i in range(len(rez)):
            g.write(f"Obiect {rez[i][0]}: {rez[i][-1]:.2f}%\n")

g,obiecte = citire_date()
afisare(greedy(g,obiecte))