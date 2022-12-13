def citire_date():
    l = []
    with open("pb1_tis.txt") as f:
        line = f.readline().strip().split()
        for i in range(len(line)):
            l.append((i+1,int(line[i])))
    return l

def afisare_timpi_servire(lista):
    s = 0
    med = 0.
    for i in lista:
        print(i[0],i[1],s)
        s += i[1]
        med += s
    print("Timp mediu de asteptare:",round(med/len(lista),2))

tis = citire_date()
afisare_timpi_servire(tis)
tis.sort(key = lambda x: x[1])
afisare_timpi_servire(tis)