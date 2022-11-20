def p9_a():
    s = input("text: ")
    k = int(input("numar: "))
    rest = k % 26

    lista = list(s)

    for i in range(len(lista)):
        if lista[i].islower():
            lista[i] = chr((ord(lista[i]) + k - ord("a")) % 26 + ord("a"))
        if lista[i].isupper():
            lista[i] = chr((ord(lista[i]) + k - ord("A")) % 26 + ord("A"))
        
    s = "".join(lista) 
    print(s)


def p9_b():
    k = int(input("numar: "))
    s = input("text: ")

    lista = list(s)

    for i in range(len(lista)):
        if lista[i].islower():
            lista[i] = chr((ord(lista[i]) - k - ord("a")) % 26 + ord("a"))
        if lista[i].isupper():
            lista[i] = chr((ord(lista[i]) - k - ord("A")) % 26 + ord("A"))

    s = "".join(lista)
    print(s)

p9_a()
p9_b()