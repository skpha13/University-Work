def a(*file):
    d = {}
    l = []
    for i in file:
        temp = open(i)
        l_cuv = temp.read().split()
        for cuv in l_cuv:
            if cuv not in d:
                d[cuv] = 1
            else:
                d[cuv] += 1
    return d

def b():
    d = a("cuvinte1.in","cuvinte2.in")
    l = []
    l = sorted(d.keys())
    return l

def c():
    d = a("cuvinte1.in")
    l = sorted(d.items(), key= lambda item:item[1],reverse=True)
    return l

def d():
    d = a("cuvinte2.in")
    print(d)
    cuv = min(d.items(), key= lambda x: (-x[1], x[0]))
    return cuv[0]

def e():
    import math

    d1 = a("cuvinte1.in")
    d2 = a("cuvinte2.in")
    l_cuv = set(d1.keys()) | set(d2.keys())

    s = sum([d1.get(cuv,0)* d2.get(cuv,0)for cuv in l_cuv])
    s1 = sum([d1.get(cuv,0)**2 for cuv in d1.keys()])
    s2 = sum([d2.get(cuv,0)**2 for cuv in d2.keys()])

    res = s/(s1**(1/2)*s2**(1/2))
    return round(res,2)

print(a("cuvinte1.in","cuvinte2.in"))
print()
print(b())
print()
print(c())
print()
print(d())
print()
print(e())
print()