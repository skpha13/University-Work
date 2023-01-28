n = int(input("numar: "))

if n == 0:
    print(0)
elif n == 1:
    print(1)
else:
    x = 0
    y = 1

    for i in range(n):
        z = x + y
        x = y
        y = z

    print(z)