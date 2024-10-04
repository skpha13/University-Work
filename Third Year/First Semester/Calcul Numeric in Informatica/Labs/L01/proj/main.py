import numpy as np
import decimal

eps = 1.0 * 10 ** -5

def generate_series(x: float, k: int = 1) -> list[float]:
    result: list[float] = [x]

    for _ in range(k):
        if 0 - eps <= result[-1] < 0.5:
            result.append(decimal.Decimal(2*result[-1]).quantize(decimal.Decimal('0.00'), rounding=decimal.ROUND_DOWN))
        elif 0.5 < result[-1] <= 1 + eps:
            result.append(decimal.Decimal(2*result[-1] - 1).quantize(decimal.Decimal('0.00'), rounding=decimal.ROUND_DOWN))

    return result

series = generate_series(0.1, 60)
print(series[-1])

for number in series:
    print(f"{number:.4f}", end=" ")

n = 3
A = np.array([
    [2, 4, -2],
    [4, 9, -3],
    [-2, -3, 7]
])
b = np.array([2, 8, 10])

def gaussian_elimination(matrix: np.ndarray, b: np.ndarray) -> np.ndarray:
    n = len(matrix)
    for k in range(0,n-1):
        for i in range(k+1,n):
            # Calculeaza multiplicatorii Gaussieni
            matrix[i][k] = -matrix[i][k]/matrix[k][k]   # Se suprascriu in triunghiul inferior
            b[i] = b[i] + b[k] * matrix[i][k] # transformarea termenului liber
            # Aplica multiplicatorii
            for j in range(k+1,n):
                matrix[i][j] = matrix[i][j] + matrix[k][j]*matrix[i][k]

    return np.triu(matrix)

print()
A_gauss = gaussian_elimination(A, b)
print(A_gauss)
print(b)

def UTRIS(L: np.ndarray, b: np.ndarray) -> np.ndarray:
    n = len(L) - 1
    x = b
    for i in range(n, -1, -1):
        for j in range(0, n - i):
            x[i] = x[i] - L[i][n-j] * x[j]
        x[i] = x[i] / L[i][i]

    return x

print(UTRIS(A_gauss, b))

test_matrix = np.random.randint(0, 10, (6, 6))
test_b = np.random.randint(0, 10, 6)
gaussian_elimination(test_matrix, test_b)
print(test_matrix)
