def citire_date():
    d = {}
    with open("spiridusi.txt") as f:
        for line in f:
            temp = line.strip().split(maxsplit=2)
            temp[1] = int(temp[1])
            if temp[0] not in d:
                d[temp[0]] = [(temp[2],temp[1])]
            else:
                d[temp[0]].append((temp[2],temp[1]))
    return d

def despre_spiridus(date,cod):
    if cod in date:
        l = date[cod]
    l.sort(key = lambda x:(-x[1],x[0]))
    return l

def jucarii(date):
    s = set()
    for i in date:
        for j in date[i]:
            s.add(j[0])
    return s

date = citire_date()
print(jucarii(date))
