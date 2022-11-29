def a():
    n = int(input("n: "))
    l = [int(x) for x in input("numere: ").split()]
    return n,l

def b(s,x,i=0,j=-1):
    if j == -1:
        j = len(s)
    s = s[i:j]
    for i in s:
        if i > x:
            return i
    return -1

def c():
    quiz = int(input("Pentru lista apasati 1 si enter, iar pentru cuvinte 0 si enter: "))
    if quiz == 1:
        l = [int(x) for x in input("numere: ").split()]
        x = 0
    else:
        l = input("cuvinte: ").lower()
        x = chr(ord('a') - 1)
    for i in range(1,len(l)+1):
        res = b(l,x,0,i)
        if res != -1:
            if res > x:
                x = res
            else:
                return "NU"
        else:
            return "NU"
    return "DA"

#n,lista = a()
#print(b([1,2,3,4,5],3))
#print(c())