import random

import numpy as np

seed = 0
np.random.seed(seed)
random.seed(seed)

N = 100
UPPER_INTEGER_LIMIT = 1000

p = np.random.randint(UPPER_INTEGER_LIMIT, size=N)
q = np.random.randint(UPPER_INTEGER_LIMIT, size=N)

r_convolution = np.convolve(p, q)

p_fft = np.fft.fft(p, 2 * N - 1)
q_fft = np.fft.fft(q, 2 * N - 1)
F = np.multiply(p_fft, q_fft)
r_fft = np.real(np.fft.ifft(F))

are_results_close = np.allclose(r_convolution, r_fft)
print(f"Similar results: {are_results_close}")
