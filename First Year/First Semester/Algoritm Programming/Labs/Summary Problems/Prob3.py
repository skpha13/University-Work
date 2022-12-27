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

lista = [11,24,1,0]
print(lista)
insereaza_cifra_control(lista)
print(lista)

