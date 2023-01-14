d = {}
with open("cinema.in") as f:
    for line in f:
        temp = line.strip().split('%')
        temp[0] = temp[0][:-1]
        temp[1] = temp[1][1:]
        temp[1] = temp[1][:-1]
        temp[2] = temp[2].split()
        
        if temp[0] not in d:
            d[temp[0]] = {temp[1]:temp[2]}
        else:
            d[temp[0]][temp[1]] = temp[2]

def sterge_ore(d,cinema,film,ore):
    for i in ore.split(" % "):
        d[cinema][film].remove(i)    
    return d

def cinema_film(d,cinematografe,ora_min,ora_max):
    l = []

    for c in cinematografe:
        for i in d[c]:
            temp = []
            verif = False
            for ora in d[c][i]:
                if ora_min <= ora and ora_max >= ora:
                    temp.append(ora)
                    verif = True
            if verif:
                l.append((i,c,temp))
    l.sort(key=lambda x:(x[0],-len(x[2])))
    return l

print(cinema_film(d,input("cinemauri: ").split(' % '),input("ora minima: "),input("ora maxima: ")))


