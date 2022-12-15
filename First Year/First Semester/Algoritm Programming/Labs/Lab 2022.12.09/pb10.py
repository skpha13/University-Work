def citire_date():
    with open("pb10_intervale.txt") as f:
        l = [(int(line.strip().split()[0]),int(line.strip().split()[1])) for line in f.readlines()]
    return l

def greedy(intervale):
    intervale.sort(key = lambda x: (x[0],-x[1]))
    first_element = intervale[0][0]
    last_element = intervale[0][1]
    sol = [[first_element,last_element]]
    for i in intervale:
        if i[0] <= last_element and i[1] <= last_element:
            continue
        if i[0] <= last_element and i[1] >= last_element:
            sol[-1][1] = i[1]
            last_element = i[1]
        else:
            first_element = i[0]
            last_element = i[1]
            sol.append([first_element,last_element])

    return sol

def afisare(sol):
    lungime = 0
    with open("pb10_reuniune.txt",'w') as g:
        g.write("Reuniunea intervalelor:\n")
        for i in sol:
            lungime += i[1] - i[0]
            g.write(f"{str(i)}\n")

        g.write(f"\nLungimea reuniunii: {lungime}")

afisare(greedy(citire_date()))