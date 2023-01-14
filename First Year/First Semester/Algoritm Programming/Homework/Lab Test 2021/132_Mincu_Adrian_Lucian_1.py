def citire_fisier(nume_fisier):
    m = []
    ok = False
    with open(nume_fisier) as f:
        for line in f:
            temp = [int(x) for x in line.split()]
            if ok == True:
                if len(m[-1]) > 0 and len(temp) != len(m[-1]):
                    return None
            ok = True
            m.append(temp)
    return m

def multimi(m,*arg):
    n = len(m[0])
    l = []
    s1 = set(m[0])
    s2 = set([x for x in m[0] if x >= 0])
    for i in arg:
        set1 = set()
        set2 = set()
        for j in range(n):
            if m[i][j] < 0:
                set1.add(m[i][j])
            elif str(m[i][j])[-1] == str(m[i][j])[0]:
                set2.add(m[i][j])
        overall1 = set1 & s1
        overall2 = set2 | s2
    return overall1,overall2

def c(m):
    t = multimi(m,len(m)-1,len(m)-2,len(m)-3)
    line = sorted(t[1])
    print(*line)

    t = multimi(m,0,len(m)-1)
    line = t[0]
    print(len(line))
    
m = citire_fisier("matrice.in")
c(m)