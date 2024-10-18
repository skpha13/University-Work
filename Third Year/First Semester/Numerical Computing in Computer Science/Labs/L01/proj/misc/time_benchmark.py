from misc.matrix import gaussian_elimination_hessenberg, gaussian_elimination_upper_matrix, gaussian_elimination
import numpy as np
import time


def benchmark(number_of_elements: int = 100):
    matrix = np.random.randint(low=1, high=10_000, size=(number_of_elements, number_of_elements))
    b = np.random.randint(low=1, high=10_000, size=number_of_elements)

    start_normal = time.monotonic()
    gaussian_elimination(matrix, b)
    end_normal = time.monotonic()

    start_hessenberg = time.monotonic()
    gaussian_elimination_hessenberg(matrix)
    end_hessenberg = time.monotonic()

    start_upper = time.monotonic()
    gaussian_elimination_upper_matrix(matrix)
    end_upper = time.monotonic()

    print(
        f"\tBenchmarks for size: {number_of_elements}\nNormal: {end_normal-start_normal}\nHessenberg: {end_hessenberg-start_hessenberg}\nUpper: {end_upper-start_upper}\n"
    )


benchmark(10)
benchmark(100)
benchmark(200)

"""
Results:

	Benchmarks for size: 10
Normal: 0.0
Hessenberg: 0.0
Upper: 0.0

	Benchmarks for size: 100
Normal: 0.23499999999989996
Hessenberg: 0.0
Upper: 0.0

	Benchmarks for size: 200
Normal: 1.4839999999999236
Hessenberg: 0.031000000000176442
Upper: 0.015999999999849024
"""
