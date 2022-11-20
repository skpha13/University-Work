import math

def f1():
    x=int(input("x="))
    y = 2**len(bin(x)[2:]) - 1
    x = x ^ y
    print(x)


def f2():
    x=int(input("x="))
    y=int(input("y="))
    if (x ^ y) < 0:
        print("nu au acelasi semn")
    else:
        print("au acelasi semn")

def f3():   
    x=int(input("x="))
    y=int(input("y="))
    x= x ^ y
    y= x ^ y
    x= x ^ y
    print("x=" + str(x),"y=" + str(y))

def f4():
    n = int(input("n="))
    msb = int(math.log2(n))
    a = 1 << msb
    result = 0

    while a!=0:
        if (result + a) * (result + a) <= n:
            result += a
        a >>= 1
    if (result * result) == n:
        print("da")
    else:
        print("nu")

def f5():
    x=int(input("x="))
    y=int(input("y="))
    z=int(input("z="))

    a = y ^ ((x ^ y) & -(x < y))
    print(z ^ ((a ^ z) & -(a < z)))

#f1()
#f2()
#f3()
#f4()
#f5()