def citire_date():
    l = [int(x) for x in input("numere: ").split()]
    return l

def divide(lista,st,dr):
    if st<dr:
        mij = (st + dr) // 2
        if lista[mij] > lista[mij-1] and lista[mij] > lista[mij+1]:
            return mij,lista[mij]
        elif lista[mij] > lista[mij-1] and lista[mij] < lista[mij+1]:
            return divide(lista,mij+1,dr)
        elif lista[mij] < lista[mij-1] and lista[mij] > lista[mij+1]:
            return divide(lista,st,mij)


lista = citire_date()
if len(lista) < 3:
    print("Lungimea prea mica")
else:
    poz,elem = divide(lista,0,len(lista)-1)
    print(f"A fost gasit ca varf elementul: {elem} la pozitia: {poz}")
