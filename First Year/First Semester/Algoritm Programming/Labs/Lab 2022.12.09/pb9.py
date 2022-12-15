def citire_date():
    with open("pb9_intervale.txt") as f:
        l = [(int(line.strip().split()[0]),int(line.strip().split()[1])) for line in f.readlines()]
    return l

def greedy(intervale):
    intervale.sort(key = lambda x: x[1])
    sol = []
    sol.append(intervale[0][1])
    for i in intervale:
        if i[0] > sol[-1]:
            sol.append(i[1])

    return sol

def afisare(sol):
    with open("pb9_acoperire.txt",'w') as g:
        for i in sol:
            g.write(f"{str(i)}\n")

afisare(greedy(citire_date()))