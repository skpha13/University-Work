line = input().strip().split(" ")
a = int(line[0])
b = int(line[1])

n = int(input())
intervale = []

for i in range(n):
    line = input().strip().split(" ")
    intervale.append(((int(line[0]), int(line[1])), i + 1))

intervale.sort(key=lambda x: x[0][0])
start = a
end = b - 1
sol = [intervale[0]]

i = 0
while i < len(intervale):
    if intervale[i][0][0] <= start:
        end = max(intervale[i][0][1], end)
        i += 1
    else:
        start = end
        sol.append(intervale[i])

        if intervale[i][0][0] > end or end >= b:
            break

# check to see if it covers
covers = True
if not (sol[0][0][0] <= a and sol[-1][0][1] >= b):
    covers = False

for i in range(len(sol) - 1):
    current_el = sol[i][0]
    next_el = sol[i+1][0]

    if current_el[1] + 1 < next_el[0]:
        covers = False

if covers:
    print(len(sol))
    if len(sol) > 0:
        for interval in sol:
            print(interval[1], end=" ")
else:
    print(0)