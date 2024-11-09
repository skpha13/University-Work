import matplotlib.pyplot as plt
import numpy as np
from utils.sinewave import sinusoidal_signal
from utils.windows import hanning_window, rectangle_window

N = 1000
Nw = 200
t = 1
nts = np.linspace(0, t, N)
signal = sinusoidal_signal(1, 100, t, 0, N)

rectangle = np.pad(rectangle_window(Nw), pad_width=(0, N - Nw), mode="constant", constant_values=0)
hanning = np.pad(hanning_window(Nw), pad_width=(0, N - Nw), mode="constant", constant_values=0)

rectangle_signal = signal * rectangle
hanning_signal = signal * hanning

plot_name = "Windows"
fig, axs = plt.subplots(2)
plt.suptitle(plot_name)

axs[0].plot(nts, rectangle_signal)
axs[0].set_title("Rectangle")

axs[1].plot(nts, hanning_signal)
axs[1].set_title("Hanning")

fig.tight_layout()

fig.savefig(fname=f"plots/{plot_name}.pdf", format="pdf")
fig.savefig(fname=f"plots/{plot_name}.png", format="png")
fig.show()
