s = input("cuvant 1: ")
t = input("cuvant 2: ")

M = [[0 for x in range(len(t))] for y in range(len(s))]

for i in range(1,len(s)):
    for j in range(1,len(t)):
        if s[i] == t[j]:
            M[i][j] = M[i-1][j-1] + 1
        else:
            M[i][j] = max(M[i-1][j],M[i][j-1])

for line in M:
    print(*line)

sol = []
for i in range(M[len(s)-1][len(t)-1],0,-1):
    ind = M[len(s)-1].index(i)
    sol.append(t[ind])

print("".join(sol[::-1]))
