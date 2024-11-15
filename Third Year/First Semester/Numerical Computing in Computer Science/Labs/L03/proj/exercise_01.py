import random

import numpy as np

seed = 0
np.random.seed(seed)
random.seed(seed)

m = 10
r = 4
A = np.random.rand(m, r)

# a)
rank = np.linalg.matrix_rank(A)
print(f"Rank A: {rank}")

# b)
first_column = (A[:, 0] + A[:, 1] + A[:, 2]).reshape(-1, 1)
second_column = (A[:, 3] + A[:, 1] + A[:, 2]).reshape(-1, 1)
third_column = (A[:, 0] + A[:, 2] + A[:, 3]).reshape(-1, 1)
fourth_column = (A[:, 0] + A[:, 1] + A[:, 3]).reshape(-1, 1)

A_extended = np.hstack((A, first_column, second_column, third_column, fourth_column))

rank_A_extended = np.linalg.matrix_rank(A_extended)
print(f"Rank A Extended: {rank_A_extended}")

# c)
noise = np.random.normal(0, 0.02, np.shape(A_extended))
A_noise = A_extended + noise
rank_A_noise = np.linalg.matrix_rank(A_noise)
print(f"Rank A Noise: {rank_A_noise}")

# d)
U, S, V = np.linalg.svd(A_noise)
print(f"Singular values: {S}")

answer_d = f"""
    4 out of those values are negligible if we take eps = 0.07
    That means the rank of our A_noise matrix will be 4
"""

print(answer_d)
