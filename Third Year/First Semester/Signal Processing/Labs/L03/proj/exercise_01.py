"""Exercise 1"""

import os

import numpy as np
from matplotlib import pyplot as plt

from utils.fourier import fourier_transform_matrix

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

N = 8

fm = fourier_transform_matrix(N)
fhm = np.transpose(np.conjugate(fm))

fhfm = np.matmul(fhm, fm)
fhfm = np.subtract(fhfm, np.diag(np.full(N, fhfm[0, 0])))

eps = 1e-5
print(f"Norm: {np.linalg.norm(fhfm, ord="fro")}")
print(f"Is unitary: {0 - eps <= np.linalg.norm(fhfm, ord="fro") <= 0 + eps}")

fig, axs = plt.subplots(N, sharex=True, sharey=True)
fig.suptitle("Fourier Components")

components_numbered = [i + 1 for i in range(N)]
for i in range(N):
    axs[i].plot(components_numbered, fm[i].real)
    axs[i].plot(components_numbered, fm[i].imag, linestyle="dashed")

plt.savefig("plots/Fourier Components.pdf", format="pdf")
plt.savefig("plots/Fourier Components.png", format="png")
plt.show()
