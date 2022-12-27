def min_max(l):
    return min(l),max(l)

def incarca_fisier(fisier):
    l = []
    with open(fisier) as f:
        for line in f:
            l.append([int(x) for x in line.split()])
    return l

nume_fisier = input("nume fisier: ")
ok = False
l = incarca_fisier(nume_fisier)
with open("egale.txt",'w') as g:
    for line in range(len(l)):
        x = min_max(l[line])
        if x[0] == x[1]:
            ok = True
            g.write(str(line) + " ")
    if ok == False:
        g.write("Nu exista!")

minn, maxx = min_max(l[0])
for i in range(len(l)):
    x = min_max(l[i])
    if x[1] > maxx:
        maxx = x[1]
    if x[0] < minn:
        minn = x[0]

print(minn,maxx)