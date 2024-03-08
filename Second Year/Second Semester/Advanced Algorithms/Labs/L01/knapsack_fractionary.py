line = input().split(" ")
n = int(line[0])
c = int(line[1])

valori = [int(x) for x in input().split(" ")]
greutati = [int(x) for x in input().split(" ")]
raporturi = sorted([(i, valori[i]/greutati[i]) for i in range(len(valori))], reverse=True, key=lambda x: x[1])

s = 0
for obj in raporturi:
    if greutati[obj[0]] <= c:
        s += valori[obj[0]]
        c -= greutati[obj[0]]
    else:
        s += valori[obj[0]] * c / greutati[obj[0]]
        break

print(s)