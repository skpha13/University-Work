def permutari(c,k):
    return c[k:] + c[:k]

print(permutari("test",2))

def sub_medie(l):
    if len(l) > 0:
        ma = sum(l)//len(l)

        nr = 0
        for i in l:
            if i < ma:
                nr += 1
        return ma,nr
    return None

k = int(input())
l = []
lista = []
with open("circular.out",'w') as g:
    with open("circular.in") as f:
        for line in f:
            temp = line.split()
            nr = 0
            for i in range(len(temp)):
                if len(temp[i]) >= k+1:
                    temp[i] = permutari(temp[i],k)
                    nr += 1
            lista.append(nr)
            l.append(temp)
    for line in l:
        sol = " ".join(line)
        g.writelines(sol + "\n")
    print(sub_medie(lista))

