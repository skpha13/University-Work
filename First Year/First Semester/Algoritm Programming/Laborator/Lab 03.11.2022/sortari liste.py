def a():
    l = [5,10,2,11]
    l.sort(key=str)
    print(l)

def b():
    l = [5,10,2,11]
    l.sort(key=lambda x:str(x)[::-1])
    print(l)

def c():
    l = [5,10,2,11]
    l.sort(key=lambda x:len(str(x)))
    print(l)


def d():
    l = [10,555,21231345,1]
    l.sort(key=lambda x:len(set(str(x))))
    print(l)


def e():
    l = [11111,222,323,123,2]
    l.sort(key=lambda x:(len(str(x)),str(x)))
    print(l)

#a()
#b()
#c()
#d()
#e()