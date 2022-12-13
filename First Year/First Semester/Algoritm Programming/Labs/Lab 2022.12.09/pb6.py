def citire_date():
    l = []
    with open("pb6_evenimente.txt") as f:
        lines = f.readlines()
        for line in lines:
            name = line.strip().split(maxsplit=1)[1]
            line = line.replace('-',' ')
            line = line.replace(':',' ')
            temp = line.split()
            l.append((temp[0],temp[1],temp[2],temp[3],) + (name,))
    return l

def greedy(evenimente):
    evenimente.sort(key = lambda x: (x[2],x[3]))
    

def afisare():
    pass

afisare(greedy(citire_date()))
