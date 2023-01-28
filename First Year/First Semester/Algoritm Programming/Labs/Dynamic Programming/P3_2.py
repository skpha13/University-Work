with open("date.in") as f:
    l = [int(x) for x in f.readline().strip().split()]

smax = [0] * len(l)
smax[0] = l[0]

for i in range(1,len(l)):
    if smax[i-1] + l[i] > l[i]:
        smax[i] = smax[i-1] + l[i]
    else:
        smax[i] = l[i]

s = max(smax)
ind = smax.index(s)
sol = []
while s != 0:
    sol.append(l[ind])
    s -= l[ind]
    ind -= 1

print(sol[::-1])