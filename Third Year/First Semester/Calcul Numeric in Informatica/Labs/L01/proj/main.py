import numpy as np

from matrix import gaussian_elimination, UTRIS
from series import generate_series

"""First exercise"""

print("\tFirst Exercise:")
x0 = 0.1
k = 60
series = generate_series(x0, k)
print(f"X at step {k} = {series[-1]}")

print(f"\nComplete series for X0: {x0} and k: {k}:")
for number in series:
    print(f"{number:.4f}", end=" ")
print("\n=================================\n")

"""Second exercise"""
n = 3
A = np.array([[2, 4, -2], [4, 9, -3], [-2, -3, 7]])
b = np.array([2, 8, 10])

print("Initial matrix:")
print(A)

A_gauss = gaussian_elimination(A, b)
print("\nMatrix after Gaussian elimination:")
print(A_gauss)
print("\nb values after Gaussian elimination:")
print(b)

print("\nX solutions for the system Ax = b:")
print(UTRIS(A_gauss, b))


test_matrix = np.random.randint(2, 10, (6, 6))
test_b = np.random.randint(2, 10, 6)

print("\nInitial 6x6 matrix:")
print(test_matrix)
print("\n6x6 matrix after Gaussian elimination")
test_matrix_gauss = gaussian_elimination(test_matrix, test_b)
print(test_matrix_gauss)

print("\nX solutions for the 6x6 matrix:")
print(UTRIS(test_matrix_gauss, test_b))
