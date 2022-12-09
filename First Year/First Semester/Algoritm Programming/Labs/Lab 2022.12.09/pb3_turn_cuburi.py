def citire_date():
    with open("pb3_cuburi.txt",'r') as f:
        n = int(f.readline().strip())
        l_cuburi = []
        for linie in f:
            latura, culoare = linie.strip().split(maxsplit=1) # split(" ", 1)
            l_cuburi.append((int(latura),culoare))
        return l_cuburi

def greedy(l_cuburi):
    l_cuburi.sort(key = lambda x: -x[0])

    sol = [l_cuburi[0]]
    h = l_cuburi[0][0]

    for cub in l_cuburi[1:]:
        if cub[1] != sol[-1][1]:
            sol.append(cub)
            h += cub[0]
    
    return sol,h

def afisare(l,h):
    with open("pb3_turn.txt",'w') as g:
        l_siruri = ["{} {}\n".format(*cub) for cub in l]
        g.writelines(l_siruri)

        sir = f"\nInaltime totala: {h}"
        g.write(sir)

cuburi = citire_date()

rezultat = greedy(cuburi)
afisare(*rezultat)