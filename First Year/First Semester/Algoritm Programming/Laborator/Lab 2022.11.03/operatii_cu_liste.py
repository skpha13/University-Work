def p1():
    n = int(input("n="))
    l1 = input("lista1: ")
    l2 = input("lista2: ")

    for i in range(n):
        if i%2 == 0:
            l1 = l1[:i] + l2[i] + l1[i+1:]
    print(*l1)

def p2():
    l = [int(x) for x in input("lista: ").split()]
    i = 0
    while i < len(l):
        if l[i] == 0:
            l.pop(i)
            while l[i] != 0:
                l.pop(i)
            l.pop(i)
        else:
            i+=1
    print(*l)

def p3():
    l = [int(x) for x in input("lista: ").split()]
    i = 0
    while i < len(l):
        if l[i] == 0:
            l.pop(i)
        else:
            i+=1
    print(*l)

def p4():
    l = [int(x) for x in input("lista: ").split()]
    k = int(input("nr= "))
    s = 0
    mx = sum(l)
    for i in range(len(l)-k+1):
        s=0
        for j in range(i,i+k):
            s+=l[j]
        if s < mx:
            mx = s
            a = i
            b = i + k - 1
    for i in range(a,b+1):
        l.pop(a)
    print(*l)

def p5():
    l = [int(x) for x in input("lista: ").split()]
    i = 0
    while i < len(l)-1:
        if l[i] == l[i+1]:
            l.pop(i)
        else:
            i+=1
    print(*l)

def p6():
    l = [float(x) for x in input("lista: ").split()]
    i = 0
    n = len(l)
    while i < n:
        if l[i] < 0:
            l.insert(i+1,0)
            i+=1
            n+=1
        i+=1
    print(*l)

#p1()
#p2()
#3()
#p4()
#p5()
#p6()