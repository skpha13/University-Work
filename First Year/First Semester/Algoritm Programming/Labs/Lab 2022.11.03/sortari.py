def p1():
    l1 = input("propozitie: ").split()
    l2 = []
    for i in range(len(l1)):
        if len(l1[i]) >= 2:
            l2.append(l1[i])
    l2.sort(key=lambda x:len(x))
    print(*l2)


def p2():
    def suma(x):
        s = 0
        while x:
            s += x%10
            x/=10
        return s

    v = [int(x) for x in input().split()]
    v.sort(key=lambda x:(suma(x)))
    print(v)

def p3():
    # a)
    l = []
    n = int(input())
    l = [input().split(maxsplit=3) for x in range(n)]
    for i in range(n):
        l[i][2] = int(l[i][2])
        l[i][3] = [int(x) for x in l[i][3].split()]
    for line in l:
        print(line)
    print()

    # b)
    for i in range(n):
        ok = 1
        for j in range(len(l[i][3])):
            if l[i][3][j] < 5:
                ok = 0
        if ok == 1:
            l[i].append(True)
        else:
            l[i].append(False)
    for line in l:
        print(line)
    print()

    # c)
    l.sort(key=lambda x: (x[2],x[0],x[1]))
    for line in l:
        print(line)
    print()

    # d)
    def medie(x):
        s = sum(x)
        nr = len(x)
        return s//nr
    def nr_note(x):
        s = 0
        for i in x:
            if i < 5:
                s+=1
        return s

    l.sort(key=lambda x: (x[2],not x[4],-medie(x[3]),x[0],x[1],nr_note(x[3])))
    for line in l:
        print(line)
    print()

    # e)
    res = max(l[i],key=medie(l[i][3]) for i in range(n))
    #l.sort(key=lambda x: max(x[3],key=medie(x[3])))
    #for line in l:
    #    print(line)
    print(res)
    print()


def p4():
    def paritate(x):
        if x%2 == 0:
            return 1
        else:
            return 0
    l = [int(x) for x in input().split()]
    l.sort(key=lambda x:paritate(x))
    for i in range(len(l)):
        if l[i] % 2 == 0:
            break
    odd = l[:i]
    even = l[i:]
    even.sort(reverse=True)
    odd.sort()
    odd.extend(even)
    print(odd)

#p1()
#p2()
p3()
#p4()
