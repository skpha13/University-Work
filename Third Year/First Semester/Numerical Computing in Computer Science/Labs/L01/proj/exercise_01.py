"""Exercise 01"""

from misc.series import generate_series

print("\tExercise 01:")
x0 = 0.1
k = 60
series = generate_series(x0, k)
print(f"(a), (b)\n{k} = {series[-1]}\n")

print(f"(c)")
for number in series:
    print(f"{number:.4f}", end=" ")
print("\n")
"""
(c)

Diferentele apareau din cauza cumularii erorii de precizie
Dar dupa ce am adaugat rounding la fiecare numar am reusit sa scapam de aceasta problema
"""
