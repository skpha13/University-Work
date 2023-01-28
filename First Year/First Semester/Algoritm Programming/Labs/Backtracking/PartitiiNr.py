n = int(input("n: "))
sol = [0] * (n + 1)
suma = 0

def afisare(k):
    for i in range(1,k+1):
        print(sol[i],end=" ")
    print()

def bkt(k):
    global n,sol,suma
    for i in range(sol[k-1]+1,n+1):
        sol[k] = i
        suma += sol[k]
        if suma <= n:
            if suma == n:
                afisare(k)
            else:
                bkt(k+1)
        suma -= sol[k]

bkt(1)