def min_max(l):
    return min(l),max(l)

def incarca_fisier(fisier):
    l = []
    with open(fisier) as f:
        for line in f:
            l.append([int(x) for x in line.split()])
    return l

nume_fisier = input("nume fisier: ")
