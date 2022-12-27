def deviruseaza(prop):
    prop = prop.split()
    
    def schimbare(cuv):
        temp = cuv[-1] + cuv[1:-1] + cuv[0] 
        cuv = temp
        return cuv

    for i in range(len(prop)//2 + 1):
        if i < len(prop)//2:
            temp = schimbare(prop[i])
            prop[i] = schimbare(prop[len(prop)-i-1])
            prop[len(prop)-i-1] = temp
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

print(prime(1000))
