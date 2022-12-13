def citire_date():
    with open("pb4_bani.txt") as f:
        lines = f.readlines()
        bancnote = [int(x) for x in lines[0].split()]
        suma = int(lines[1])
    return bancnote,suma

def greedy(lista,s):
    def find_low(l,x):
        for i in l:
            if i<=x:
                return i

    lista.sort(reverse = True)
    sol = {}
    while s != 0:
        ban = find_low(lista,s)
        s -= ban
        if ban not in sol:
            sol[ban] = 1
        else:
            sol[ban] += 1
    return sol

def afisare(sol):
    g = open("pb4_plata.txt",'w')
    g.write("s = ")
    for i in sol:
        g.write(f"{i}*{sol[i]} + ")
        
lista,s = citire_date()
sol = greedy(lista,s)
afisare(sol)