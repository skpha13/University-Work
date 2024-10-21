import os

import matplotlib.pyplot as plt
import numpy as np

from utils.fourier import fourier_transform, fourier_transform_using_winding_frequency
from utils.sinewave import sinusoidal_signal

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

plt.rcParams["lines.linewidth"] = 0.9
nbins = 3

n = 1000
t = 1
ts = np.linspace(0, t, n)
f = np.arange(start=0, stop=n, step=1)  # sampling frequency = n, DFT number of components = n => n/n = 1

signal = (
    sinusoidal_signal(1, 3, t, np.pi / 2, n)
    + sinusoidal_signal(1 / 4, 9, t, 0, n)
    + sinusoidal_signal(4, 15, t, np.pi * 3 / 4, n)
)

omegas = [3, 9, 15]
fourier_transform_over_signal = fourier_transform(signal)
fourier_transform_winding_frequency = fourier_transform_using_winding_frequency(signal, omegas=omegas)

fig, axs = plt.subplots(nrows=1, ncols=3, figsize=(12, 4))
fig.suptitle("Fourier Transform")

for ax in axs:
    ax.locator_params(axis="x", nbins=nbins)
    ax.locator_params(axis="y", nbins=2 * nbins)

axs[0].plot(ts, signal, color="blue")
axs[0].set_xlabel("Time (s)")
axs[0].set_ylabel("x(t)")

(stemlines, stemmarkers, baseline) = axs[1].stem(
    f,
    np.abs(fourier_transform_over_signal),
    linefmt="k-",
    markerfmt="ko",
    basefmt=" ",
)

plt.setp(stemmarkers, "linewidth", 0.3)
plt.setp(stemlines, "markerfacecolor", "none")
baseline.set_color("k")

axs[1].set_xlabel("Frequency (Hz)")
axs[1].set_ylabel("| X(w) |")
axs[1].locator_params(axis="x", nbins=5)
axs[1].set_xlim([0, 100])


(stemlines, stemmarkers, baseline) = axs[2].stem(
    fourier_transform_winding_frequency.keys(),
    np.abs(list(fourier_transform_winding_frequency.values())),
    linefmt="k-",
    markerfmt="ko",
    basefmt=" ",
)

plt.setp(stemmarkers, "linewidth", 0.3)
plt.setp(stemlines, "markerfacecolor", "none")
baseline.set_color("k")

axs[2].set_xlabel("Frequency (Hz)")
axs[2].set_ylabel("| X(w) |")
axs[2].locator_params(axis="x", nbins=5)
axs[2].set_xlim([0, 100])


plt.tight_layout()
plt.savefig(f"plots/Fourier Transform.pdf", format="pdf")
plt.savefig(f"plots/Fourier Transform.png", format="png")
plt.show()
