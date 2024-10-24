import os
from dataclasses import dataclass

import matplotlib.pyplot as plt
import numpy as np
from utils.sinewave import sinusoidal_signal

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

plt.rc("axes", titlesize=10)

t = 1
n = 1000
ns = 7

x_domain = np.linspace(0, t, n)
nts = np.linspace(0, t, ns)


@dataclass
class Signals:
    frequency: str
    plot: np.ndarray
    scatter: np.ndarray
    color: str


signals: list[Signals] = [
    Signals("16Hz", sinusoidal_signal(1, 16, t, 0, 1000), sinusoidal_signal(1, 16, t, 0, ns), "slateblue"),
    Signals("10Hz", sinusoidal_signal(1, 10, t, 0, 1000), sinusoidal_signal(1, 10, t, 0, ns), "purple"),
    Signals("4Hz", sinusoidal_signal(1, 4, t, 0, 1000), sinusoidal_signal(1, 4, t, 0, ns), "green"),
]

fig, axs = plt.subplots(4)
fig.suptitle("Sub-Nyquist Frequencies")

axs[0].plot(x_domain, signals[0].plot, color="slateblue")
axs[0].set_title(signals[0].frequency)

for ax, signal in zip(axs[1:], signals):
    ax.plot(x_domain, signal.plot, color=signal.color, zorder=1)
    ax.scatter(nts, signal.scatter, color="yellow", alpha=1, zorder=2)
    ax.set_title(signal.frequency)


plt.tight_layout()
plt.savefig("plots/Sub-Nyquist Frequencies.pdf", format="pdf")
plt.savefig("plots/Sub-Nyquist Frequencies.png", format="png")
plt.show()
