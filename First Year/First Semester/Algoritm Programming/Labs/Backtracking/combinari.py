n = int(input("n: "))
m = int(input("m: "))
s = [0] * (n + 1)

def bkt(k):
    global s,n,m
    
    for v in range(s[k-1]+1,n+1):
        s[k] = v
        if k == m:
            print(*s[1:m+1])
        else:
            bkt(k+1)

bkt(1)
