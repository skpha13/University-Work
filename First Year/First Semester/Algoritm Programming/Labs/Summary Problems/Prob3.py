def cifra_control(n):
    while n > 9:
        s = 0
        while n != 0:
            s += n%10
            n //= 10
        n = s
    return n


