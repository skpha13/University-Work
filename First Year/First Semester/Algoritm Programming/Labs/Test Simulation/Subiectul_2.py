def citire_date():
    l = []
    with open("cinema.in") as f:
        for line in f:
            temp = line.strip().split('%')
            temp[0] = temp[0][:-1]
            temp[1] = temp[1][1:]
            temp[1] = temp[1][:-1]
            temp[2] = temp[2].split()
            l.append(temp)
    return l

def sterge_ore(lista,cinema,film,ora):
    for x in lista:
        if x[0] == cinema and x[1] == film:
            x[2].remove(ora)

def cinema_film(lista,ora_minima,ora_maxima,*cinema,):
    l_tupluri = []
    lista.sort(key = lambda x: x[0])
    cinema = list(cinema)
    cinema.sort()
    for i in cinema:
        for j in lista:
            if j[0] == i:
                ore = []
                for ora in j[2]:
                    if ora >= ora_minima and ora <= ora_maxima:
                        ore.append(ora)
                if len(ore) != 0:
                    l_tupluri.append((j[1],j[0],ore))
    return l_tupluri

date = citire_date()
#sterge_ore(date,input("cinema: "),input("film: "),input("ora: "))
#for line in date:
#    print(*line)
l = cinema_film(date,"10:00","18:00","Cinema 1","Cinema 2")
for line in l:
    print(line)

