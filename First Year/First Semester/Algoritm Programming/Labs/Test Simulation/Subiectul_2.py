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

date = citire_date()
sterge_ore(date,input("cinema: "),input("film: "),input("ora: "))
for line in date:
    print(*line)