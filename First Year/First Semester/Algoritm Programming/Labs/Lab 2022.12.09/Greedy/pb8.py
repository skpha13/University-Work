def citire_date():
    with open("pb8_proiecte.txt") as f:
        l = [(line.split()[0],int(line.strip().split()[1]),int(line.strip().split()[2])) for line in f.readlines()]

    return l

def greedy(proiecte):
    proiecte.sort(key = lambda x: -x[2])
    d = {i:0 for i in range(1,32)}
    sol = []
    for proj in proiecte:
        if d[proj[1]] == 0:
            d[proj[1]] = proj
        else:
            for i in range(proj[1],0,-1):
                if d[i] == 0:
                    d[i] = proj

    for i in d:
        if d[i] != 0:
            sol.append(d[i])
    
    return sol

def afisare(sol):
    with open("pb8_profit.txt",'w') as g:
        suma = 0
        for zi in sol:
            suma += zi[2] 
            g.write(f"Ziua {zi[1]}: {zi[0]}\n")
    
        sir = " + ".join(str(zi[2]) for zi in sol)
        g.write(f"\nProfit maxim: {sir} = {suma}")

afisare(greedy(citire_date()))