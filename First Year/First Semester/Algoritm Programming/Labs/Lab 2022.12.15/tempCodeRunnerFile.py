    mij = (st + dr) // 2
    if lista[mij] > lista[mij-1] and lista[mij] > lista[mij+1]:
        return mij,lista[mij]
    else:
        stanga = divide(lista,st,mij)
        dreapta = divide(lista,mij+1,dr)
