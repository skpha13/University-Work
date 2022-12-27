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
