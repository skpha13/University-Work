line = input().strip().split(" ")
a = int(line[0])
b = int(line[1])

n = int(input())
intervale = []

for i in range(n):
    line = input().strip().split(" ")
    intervale.append(((int(line[0]), int(line[1])), i))

intervale.sort(key=lambda x: x[0][1])
sol = [intervale[0]]

for interval in intervale:
    if interval[0][0] > sol[-1][0][1]:
        sol.append(interval)

print(len(sol))
for interval in sol:
    print(interval[1], end=" ")