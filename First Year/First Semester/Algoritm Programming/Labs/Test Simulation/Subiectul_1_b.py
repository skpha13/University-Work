def prelucrare_lista(l):
    for i in range(len(l)):
        aux = minn = 0
        while aux == minn:
            minn = min(l[i])
            l[i].remove(minn)
            aux = min(l[i])

    temp = []
    for line in l:
        temp.append(len(line))
    m = min(temp)
    for i in range(len(l)):
        if len(l[i]) > 1:
            l[i] = l[i][:m]                

l = [[100,54,101,54,2,81,92],[10,1,1,2,2,1,70],[12,81,10,8,9,8,10]]
prelucrare_lista(l)
print(l)