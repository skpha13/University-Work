def prelucrare_lista(l):
    for i in range(len(l)):
        minn = min(l[i])
        for j in range(len(l[i])):
            if l[i][j] == minn:
                aux = j
                break
        l[i].pop(j)
    temp = []
    for line in l:
        temp.append(len(line))
    m = min(temp)
    for i in range(len(l)):
        if len(l[i]) > 1:
            l[i] = l[i][:len(l[i])-m]                 

l = [[1,2,3],[3,4],[54,-3,0,23]]
prelucrare_lista(l)
print(l)