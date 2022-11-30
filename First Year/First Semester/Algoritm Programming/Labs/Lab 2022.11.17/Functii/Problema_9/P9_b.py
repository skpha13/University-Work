def maxim(*args):
    number = 0
    for i in args:
        aux = i
        c = 0
        while aux != 0:
            if c < aux % 10:
                c = aux % 10
            aux //= 10
        number = number * 10 + c
    return number

def function(a,b,c):
    ok = 0
    if maxim(a) == 1:
        ok += 1
    if maxim(b) == 1:
        ok += 1
    if maxim(c) == 1:
        ok += 1
    if ok == 3:
        return True
    return False

print(function(1001,11,100))