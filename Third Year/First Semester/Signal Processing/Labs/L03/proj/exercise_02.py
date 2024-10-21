"""Exercise 2"""

import os

import matplotlib.pyplot as plt
import numpy as np

from utils.distance import normalized_distances
from utils.fourier import winding_frequency_on_unit_circle
from utils.sinewave import sinusoidal_signal

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

plt.rcParams["lines.linewidth"] = 0.9
plt.rcParams["lines.markersize"] = 2
nbins = 3

n = 1000
t = 1000
ts = np.linspace(0, t, n)
signal = sinusoidal_signal(1, 3, t, np.pi / 2, n)

nrows = 3
ncols = 2
fig, axs = plt.subplots(nrows=nrows, ncols=ncols, figsize=(8, 12))
fig.suptitle("Winding frequency")

for i in range(nrows):
    for j in range(ncols):
        axs[i, j].axhline(0, color="black")
        axs[i, j].locator_params(axis="x", nbins=nbins)
        axs[i, j].locator_params(axis="y", nbins=nbins)

        if i > 0 or j > 0:
            axs[i, j].axvline(0, color="black")

            axs[i, j].set_xlim(-1.1, 1.1)
            axs[i, j].set_ylim(-1.1, 1.1)
            axs[i, j].set_aspect("equal")
            axs[i, j].set_xlabel("Real")
            axs[i, j].set_ylabel("Imaginary")

omegas = [1, 3, 4, 5, 10]
z = winding_frequency_on_unit_circle(signal, omegas)

cmap = plt.get_cmap("inferno")
points = np.array(list(zip(ts, signal)))
colors = cmap(normalized_distances(points))

axs[0][0].scatter(ts, signal, color=colors)
axs[0][0].set_xlabel("Time (samples)")
axs[0][0].set_ylabel("Amplitude")

colors = cmap(normalized_distances(z[0]))
axs[0][1].scatter(z[0].real, z[0].imag, color=colors)

for index in range(1, len(z)):
    i = (index - 1) // ncols + 1
    j = (index - 1) % ncols

    colors = cmap(normalized_distances(z[index]))

    axs[i][j].scatter(z[index].real, z[index].imag, color=colors)

fig.tight_layout()
plt.savefig("plots/Winding Frequency.pdf", format="pdf")
plt.savefig("plots/Winding Frequency.png", format="png")
plt.show()
