n = int(input("numar: "))
nr_pasi = [0] * (n+1)
nr_pasi[1] = 1

for i in range(2,n+1):
    aux = i
    count = 0
    while aux != 0:
        if aux & 1 == 0:
            aux //= 2
        else:
            aux = 3*aux + 1
        count += 1
        if aux <= n and nr_pasi[aux] != 0:
            break

    nr_pasi[i] = count + nr_pasi[aux]

print(nr_pasi[n]-1)
