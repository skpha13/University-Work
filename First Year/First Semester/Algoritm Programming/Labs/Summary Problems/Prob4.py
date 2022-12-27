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

def spiridusi(date):
    l = []
   
    for i in date:
        nr_distince = 0
        nr_total = 0
        s = set()
        for j in date[i]:
            if j[0] not in s:
                s.add(j[0])
                nr_distince += 1
            nr_total += j[1]
        l.append((i,nr_distince,nr_total))
    l.sort(key=lambda x: (-x[1],-x[2],x[0]))
    return l

def actualizare(date,cod,nume_jucarie):
    if len(date[cod]) > 1:
        for j in date[cod]:
            if j[0] == nume_jucarie:
                date[cod].remove(j)
                print(date[cod])
                return True
    return False

date = citire_date()
actualizare(date,"S1","trenulet")