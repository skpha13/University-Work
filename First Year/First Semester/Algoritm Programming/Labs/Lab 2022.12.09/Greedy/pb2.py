def citire_date():
    l = []
    with open("pb2_spectacole.txt") as f:
        lines = f.readlines()
        for line in lines:
            name = line.strip().split(maxsplit=1)[1]
            line = line.replace('-',' ')
            line = line.replace(':',' ')
            temp = line.split()
            l.append((temp[0],temp[1],temp[2],temp[3],) + (name,))
    return l

def greedy(date):
    date.sort(key=lambda x: (x[2],x[3]))

    sol = []
    sol.append(date[0])
    k = 0
    for i in range(1,len(date)):
        if date[i][0] > sol[k][2]:
            k += 1
            sol.append(date[i])
        elif date[i][0] == sol[k][2] and date[i][1] > sol[k][3]:
            k += 1
            sol.append(date[i])
    return sol

def afisare(l):
    for cuv in l:
        print(f"{cuv[0]}:{cuv[1]}-{cuv[2]}:{cuv[3]} {cuv[4]}")

date = citire_date()
sol = greedy(date)
afisare(sol)