def citire_nume(fisier):
    l = []
    with open(fisier) as f:
        for line in f:
            temp = [int(x) for x in line.split()]
            l.append(temp)
    return l

l = citire_nume("Subiectul_1_a_fisier.txt")
print(l)