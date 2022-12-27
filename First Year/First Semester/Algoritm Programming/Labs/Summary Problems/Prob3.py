def cifra_control(n):
    while n > 9:
        s = 0
        while n != 0:
            s += n%10
            n //= 10
        n = s
    return n

def insereaza_cifra_control(l):
    n = len(l)
    i = 0
    while i < n:
        l.insert(i+1,cifra_control(l[i]))
        n += 1
        i += 2

def egale(*liste):
    for i in range(len(liste)-1):
        if liste[i] != liste[i+1]:
            return False
    return True

def d():
    with open("numere.in") as f:
        l = [int(x) for x in f.read().split()]
        for i in l:
            print(i,cifra_control(i))

def e():
    with open("numere.in") as f:
        l1 = [int(x) for x in f.read().split()]
    with open("numere2.in") as e:
        l2 = [int(x) for x in e.read().split()]
    l1 = list(set(l1))
    l2 = list(set(l2))
    l1.sort()
    l2.sort()
    if len(l1) != len(l2):
        print("NU")
        return
    for i in range(len(l1)):
        if cifra_control(l1[i]) != cifra_control(l2[i]):
            print("NU")
            return
    print("DA")

e()