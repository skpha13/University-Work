def deviruseaza(prop):
    prop = prop.split()
    
    def schimbare(cuv):
        if len(cuv) > 1:
            temp = cuv[-1] + cuv[1:-1] + cuv[0] 
            cuv = temp
        return cuv

    for i in range(len(prop)):
        prop[i] = schimbare(prop[i])

    for i in range(len(prop)//2 + 1):
        if i < len(prop)//2:
            temp = prop[i]
            prop[i] = prop[len(prop)-i-1]
            prop[len(prop)-i-1] = temp
    prop = " ".join(prop)
    return prop

def prime(n,nr_max = 0):
    l = []
    def prim(n):
        if n < 2:
            return False
        d = 2
        while d*d <= n:
            if n % d == 0:
                return False
            d += 1
        return True

    if nr_max == 0:
        for i in range(2,n):
            if prim(i):
                l.append(i)
    else:
        nr = 0
        for i in range(2,n):
            if prim(i) and nr != nr_max:
                l.append(i)
                nr += 1
    return l

with open("intrare_devirusata.out",'w') as g:
    sol = []
    with open("intrare.in") as f:
        for i,line in enumerate(f):
            if i+1 != 1 and prime(i+2)[-1] == i+1:
                sol.append(deviruseaza(line))
            else:
                sol.append(line.strip())
    for line in sol:
        g.write(line + "\n")