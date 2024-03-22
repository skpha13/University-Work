a, b, c = [int(x) for x in input().split(' ')]
n = int(input())
numere = [float(x) for x in input().split(' ')]

functie = lambda x: a*x**2 + b*x + c
valori_fitness = [functie(x) for x in numere]
total_sum = sum(valori_fitness)
partial_sum = 0
for i in range(len(valori_fitness)):
    print(partial_sum / total_sum)
    partial_sum += valori_fitness[i]

print(partial_sum / total_sum)