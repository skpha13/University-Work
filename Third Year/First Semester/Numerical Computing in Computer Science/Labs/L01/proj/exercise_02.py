"""Exercise 02"""

import numpy as np

from misc.matrix import UTRIS, gaussian_elimination

np.set_printoptions(precision=4, suppress=True)

print("\tExercise 02:")
print("(a)")
n = 3
A = np.array([[2, 4, -2], [4, 9, -3], [-2, -3, 7]])
b = np.array([2, 8, 10])
print("A:")
print(A)

A_gauss = gaussian_elimination(A, b)
print("\nA Gauss:")
print(A_gauss)
print("\nb Gauss:")
print(b)

print("\n(b)")
print("X:")
print(UTRIS(A_gauss, b))


test_matrix = np.random.randn(6, 6)
test_b = np.random.randn(6)

print("\n(c)")
print("6x6:")
print(test_matrix)
print("\n6x6 Gauss")
test_matrix_gauss = gaussian_elimination(test_matrix, test_b)
print(test_matrix_gauss)

print("\nX:")
print(UTRIS(test_matrix_gauss, test_b))
