nrf = int(input())
nrb = int(input())
s = int(input())
n = nrf + nrb
sol = [0] * (s + 1)

def bkt_fete(k):
    global nrf,s
    for i in range(sol[k-1]+1,nrf+1):
        sol[k] = i
        if sol[k] not in sol[:k]:
            if k == s//2:
                bkt_baieti(k+1)
            else:
                bkt_fete(k+1)

def valid(k):
    for i in range(k):
        if sol[k] < sol[i]:
            return False
    return True

def bkt_baieti(k):
    global nrf,nrb,s,n
    for i in range(nrf+1,n+1):
        sol[k] = i
        # b) in acest if adaug 1 in sol and nrf+1 in sol
        if sol[k] not in sol[:k] and valid(k):
            if k == s:
                print(*sol[1:])
            else:
                bkt_baieti(k+1)

bkt_fete(1)

