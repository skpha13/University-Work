n = int(input("n: "))
sol = [0] * (n + 1)
use = [0] * (n + 1)

def bkt(k):
    for i in range(1,n + 1):
        if use[i] == 0:
            sol[k] = i
            use[i] = 1
            if sol[k]%2 != 0 or sol[k] == k:
                if k == n:
                    print(*sol[1:])
                else:
                    bkt(k+1)
            use[i] = 0

bkt(1)