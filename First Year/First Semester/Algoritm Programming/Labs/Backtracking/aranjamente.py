n = int(input("n: "))
k = int(input("k: "))
s = [0] * (n + 1)

def afisare(v):
    for i in range(1,v+1):
        print(s[i],end=" ")
    print()

def valid(v):
    for i in range(1,v):
        if s[v] == s[i]:
            return False
    return True

def bkt(v):
    global s,n,k

    for i in range(1,n+1):
        s[v] = i
        if s[v] not in s[:v]:
            if v == k:
                print(*s[1:k+1])
                #afisare(v)
            else:
                bkt(v+1)

bkt(1)