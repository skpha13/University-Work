def litere(*cuvinte):
    d = {}
    for cuv in cuvinte:
        s = set(cuv)
        dd = {}
        for litera in s:
            dd[litera] = cuv.count(litera)
        d[cuv] = dd
    return(d)

print(litere("teste","programare"))