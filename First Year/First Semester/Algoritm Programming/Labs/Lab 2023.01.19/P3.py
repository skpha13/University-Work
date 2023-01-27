with open("date.in") as f:
    l = [int(x) for x in f.readline().strip().split()]

sume = []
sume.append([l[0],l[0]])

for i in range(1,len(l)):
    if sume[i-1][0] + l[i] > l[i]:
        sume.append([sume[i-1][0]+l[i]])
        sume[i].extend(sume[i-1][1:])
        sume[i].append(l[i])
    else:
        sume.append([l[i]])
        sume[i].append(l[i])

sol = [str(y) for y in max(sume,key=lambda x: x[0])[1:]]
sol = " ".join(sol)

with open("date.out",'w') as g:
    g.write(sol)