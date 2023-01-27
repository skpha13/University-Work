with open("p4_date.in") as f:
    cuvinte = f.readline().strip().split()

pozitii = [-1] * len(cuvinte)
numere = [0] * len(cuvinte)

for i in range(1,len(cuvinte)):
    for j in range(i):
        if cuvinte[i][:2] == cuvinte[j][-2:] and numere[j] >= numere[i]:
            pozitii[i] = j
            numere[i] = numere[j] + 1

cuv = max(pozitii)
ind = pozitii.index(cuv)
sol = []

while ind != -1:
    sol.append(cuvinte[ind])
    ind = pozitii[ind]

sol = "\n".join(sol[::-1])

with open("p4_date.out", 'w') as g:
    g.write(sol)