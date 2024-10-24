import os

import matplotlib.pyplot as plt
import numpy as np
from utils.sinewave import sinusoidal_signal

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

t = 1
n = 1000
ns = 7

x_domain = np.linspace(0, t, n)
nts = np.linspace(0, t, ns)

base_signal_16 = sinusoidal_signal(1, 16, t, 0, 1000)
samples_signal_16 = sinusoidal_signal(1, 16, t, 0, ns)

base_signal_8 = sinusoidal_signal(1, 10, t, 0, 1000)
samples_signal_8 = sinusoidal_signal(1, 10, t, 0, ns)

base_signal_4 = sinusoidal_signal(1, 4, t, 0, 1000)
samples_signal_4 = sinusoidal_signal(1, 4, t, 0, ns)

fig, axs = plt.subplots(4)
fig.suptitle("Sub-Nyquist Frequencies")

axs[0].plot(x_domain, base_signal_16, color="slateblue")

axs[1].plot(x_domain, base_signal_16, color="slateblue", zorder=1)
axs[1].scatter(nts, samples_signal_16, color="yellow", alpha=1, zorder=2)

axs[2].plot(x_domain, base_signal_8, color="purple", zorder=1)
axs[2].scatter(nts, samples_signal_8, color="yellow", alpha=1, zorder=2)

axs[3].plot(x_domain, base_signal_4, color="green", zorder=1)
axs[3].scatter(nts, samples_signal_4, color="yellow", alpha=1, zorder=2)

plt.tight_layout()
plt.savefig("plots/Sub-Nyquist Frequencies.pdf", format="pdf")
plt.savefig("plots/Sub-Nyquist Frequencies.png", format="png")
plt.show()
