"""Exercise 2"""

import matplotlib.pyplot as plt
import numpy as np

from plot import plot, stem
from sinewave import sinusoidal_signal

# (a)
t = 1
n = 1600
stem("1600 samples", np.linspace(0, t, n), sinusoidal_signal(1, 400, t, 0, n))

# (b)
t = 3
n = 800
stem("800 samples 3 seconds", np.linspace(0, t, n), sinusoidal_signal(1, 800, t, 0, n))

# (c)
t = 1
n = 1_000_000
signal = sinusoidal_signal(1, 240, t, 0, n)
sawtooth_signal = np.arcsin(np.abs(signal))
sawtooth_signal = np.mod(sawtooth_signal, 0.1)
plot("Sawtooth", np.linspace(0, t, n), sawtooth_signal, xlim=[0, 6e-4])

# (d)
t = 1000
n = 10_000
plot("Square", np.linspace(0, t, n), np.sign(sinusoidal_signal(1, 300, t, 0, n)))

# (e)
cmap = "binary"
random_signal = np.random.rand(128, 128)
plt.imshow(random_signal, cmap=cmap)
plt.savefig(fname=f"./plots/random_image.pdf", format="pdf")
plt.show()
plt.close()

# (f)
generated_signal = np.zeros((128, 128))

values = np.linspace(0, 2 * np.pi, 128)
for i in range(len(generated_signal)):
    generated_signal[i] = np.sin(values) * np.tan(values)

min_value = np.min(generated_signal)
max_value = np.max(generated_signal)

generated_signal = (generated_signal - min_value) / (max_value - min_value)

plt.imshow(generated_signal, cmap=cmap)
plt.savefig(fname=f"./plots/generated_image.pdf", format="pdf")
plt.show()
