import matplotlib.pyplot as plt
import numpy as np

signal = np.genfromtxt("data/train.csv", delimiter=",")[1:, 2]

sample_rate = 1 / 3600
fourier = np.fft.fft(signal)
magnitude = np.abs(fourier / len(signal))[: len(fourier) // 2]
frequencies = np.fft.fftfreq(len(signal), 1 / sample_rate)[: len(fourier) // 2]

fig, ax = plt.subplots(1)
fig.suptitle("Magnitude of Signal")

plt.yscale("log")
plt.xscale("log")

# TODO: use plot instead of stem
(stemlines, stemmarkers, baseline) = ax.stem(
    frequencies,
    magnitude,
    linefmt="k-",
    markerfmt="ko",
    basefmt=" ",
)

plt.setp(stemmarkers, "linewidth", 0.3)
plt.setp(stemlines, "markerfacecolor", "none")
baseline.set_color("k")

plt.show()
