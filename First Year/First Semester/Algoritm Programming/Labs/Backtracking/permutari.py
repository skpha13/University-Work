x = [0] * 10
n = int(input("n: "))

def afisare(v):
    for i in range(v):
        print(x[i],end=" ")
    print()

def valid(v):
    for i in range(v):
        if x[i] == x[v]:
            return False
    return True

def btk(v):
    global n
    for i in range(1,n+1):
        x[v] = i
        if valid(v):
            if v == n-1:
                afisare(v+1)
            else:
                btk(v+1)

btk(0)