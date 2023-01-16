d = {}

with open("magazine.in") as f:
    temp = tuple(f.readline().split())
    m = int(temp[0])
    n = int(temp[1])

    for i in range(m):
        temp = f.readline().split(maxsplit=1)
        d[temp[0]] = {temp[1]: 0}
    for i in range(n):
        temp = f.readline().split()
        if d[temp[0]] in d:
            d[temp[0]]        
print(n,m,d,sep="\n")