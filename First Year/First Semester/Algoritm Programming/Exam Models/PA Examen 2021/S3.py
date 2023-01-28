n = int(input("n: "))
cuvinte = input("cuvinte: ").split()
l_poz = [-1] * (n + 1)
l_max = [1] * (n + 1)
ok = 0

def verificare(cuv1,cuv2):
    x = cuv1[-1]
    y = cuv2[0]

    if abs(ord(x)-ord(y)) == 1:
        return True
    else:
        return False

l_poz[0] = -1
for i in range(1,len(cuvinte)):
    for j in range(i):
        if verificare(cuvinte[j],cuvinte[i]) and l_max[i] < l_max[j] + 1:
            l_max[i] = l_max[j] + 1
            l_poz[i] = j
        elif l_max[i] == l_max[j] + 1:
            ok = 1

ind = l_max.index(max(l_max))
sol = []
while ind != -1:
    sol.append(cuvinte[ind])
    ind = l_poz[ind]

for cuv in cuvinte:
    if cuv not in sol:
        print(cuv,end=" ")
if ok:
    print("\nnu are solutie unica")
else:
    print("\nare solutie unica")        