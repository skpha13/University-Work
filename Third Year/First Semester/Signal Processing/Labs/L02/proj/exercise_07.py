"""Exercise 7"""

import matplotlib.pyplot as plt
import numpy as np

from utils.sinewave import sinusoidal_signal

t = 1
n = 1000
nts = np.linspace(0, t, n)
nts_4 = np.linspace(0, t, int(n / 4))
nts_16 = np.linspace(0, t, int(n / 16))

f_signal = sinusoidal_signal(1, 200, t, 0, n)
decimated_4 = sinusoidal_signal(1, 200, t, 0, int(n / 4))
decimated_16 = sinusoidal_signal(1, 200, t, 0, int(n / 16))

fig, axs = plt.subplots(3)
fig.suptitle("Decimation of Frequency")

for ax in axs.flat:
    ax.set_xlim([0, 0.1])

axs[0].plot(nts, f_signal)
axs[1].plot(nts_4, decimated_4)
axs[2].plot(nts_16, decimated_16)

plt.savefig(fname=f"./plots/Decimation of Frequency.pdf", format="pdf")
plt.show()

"""Observations:

    It is observed that the more we decrease the sampling frequency, the more the plotted graph
becomes indistinguishable from the original signal.
    Furthermore, if the frequency is divisible and is a multiple of the time period, its 
like cutting entire cycles from the sinusoidal signal (same as decreasing the frequency of the signal)
In other words, we sample at intervals that allign with the period of the wave.
"""
