import matplotlib.pyplot as plt
import numpy as np

from fourier import display_matrix, fourier_transform
from sinewave import sinusoidal_signal

"""Exercitiul 1"""
N = 4

fm = fourier_transform(N)
display_matrix(fm)
fhm = np.transpose(np.conjugate(fm))
print()

fhfm = np.matmul(fhm, fm)
display_matrix(np.diag(np.diag(np.full((N, N), fill_value=fhfm[0][0]))))
fhfm = np.subtract(fhfm, np.diag(np.diag(np.full((N, N), fill_value=fhfm[0][0]))))

display_matrix(fhfm)
print()
print(np.linalg.norm(fhfm, ord="fro"))

print()
eps = 1e-5
print(f"Is unitary: {0 - eps <= np.linalg.norm(fhfm, ord="fro") <= 0 + eps}")

fig, axs = plt.subplots(N, sharex=True, sharey=True)
fig.suptitle("Fourier Components")

components_numbered = [i + 1 for i in range(N)]
for i in range(N):
    axs[i].plot(components_numbered, fm[i].real)
    axs[i].plot(components_numbered, fm[i].imag, linestyle="dashed")

plt.show()

"""Exercitiul 2"""
n = 1000
t = 1
ts = np.linspace(0, t, n)
signal = sinusoidal_signal(1, 3, t, 0, n)

fig, axs = plt.subplots(2)
fig.suptitle("")
