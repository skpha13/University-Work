def a():
    l = [chr(x) for x in range(ord("a"),ord("z")+1)]
    print(l)

def b():
    n = int(input("n="))
    l = [x if x%2!=0 else -x for x in range(1,n+1)]
    print(l)

def c():
    l = [int(x) for x in input().split()]
    l2 = [x for x in l if x%2!=0]
    print(l2)

def d():
    l = [int(x) for x in input().split()]
    l2 = [l[i] for i in range(len(l)) if i%2==1]
    print(l2)

def e():
    l = [2,4,1,7,5,1,8,10]
    l2 = [l[i] for i in range(len(l)) if i%2==l[i]%2]
    print(l2)

def f():
    l = [1,2,3,4]
    l2 = [tuple(l[i:i+2]) for i in range(len(l)-1)]
    print(l2)

def g():
    n = int(input("n=")) 
    def functie(n):
        l = [[f"{x}*{y}={x*y}" for y in range(1,n+1)] for x in range(1,n+1)]
        return l
    l = functie(n)
    for linie in l:
        print(*linie)

def h():
    sir = "abcde"
    l = [sir[i:]+sir[:i] for i in range(len(sir))]
    print(l)

def i():
    n = int(input("n="))
    def functie(n):
        l = [[j for i in range(0,j)]for j in range(0,n+1)]
        return l
    l = functie(n)
    for linie in l:
        print(linie)

#a()
#b()
#c()
#d()
#e()
#f()
#g()
#h()
#i()