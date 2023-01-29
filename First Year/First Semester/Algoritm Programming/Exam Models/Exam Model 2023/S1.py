# a

def divizori(*arg):
    d = {}
    for nr in arg:
        aux = nr
        f = 2
        l = []
        while aux > 1:
            if aux % f == 0:
                l.append(f)
            while aux % f == 0:
                aux //= f
            f += 1
        d[nr] = l
    return d

# b

litere_10 = [chr(ord('a') + i) for i in range(10)]

# c