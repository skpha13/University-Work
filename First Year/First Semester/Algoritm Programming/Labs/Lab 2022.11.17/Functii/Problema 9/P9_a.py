def function(*args):
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

print(function(4251,73,8,133))