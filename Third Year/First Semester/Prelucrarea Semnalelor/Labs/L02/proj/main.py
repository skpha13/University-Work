import matplotlib.pyplot as plt
import numpy as np
import numpy.random
import scipy.io.wavfile as sw
import sounddevice
from numpy import ndarray

from sinewave import cosinus_signal, sinusoidal_signal

"""Exercise 1"""

t = 1
n = 1000
nts = np.linspace(0, t, n)
sin = sinusoidal_signal(n=n)
cos = cosinus_signal(phi=-np.arcsin(np.sin(np.pi / 2)), n=n)

fig, axs = plt.subplots(2)
fig.suptitle("Sin vs Cos")
axs[0].plot(nts, sin)
axs[1].plot(nts, cos)
plt.show()


"""Exercise 2"""
t = 1
n = 10_000
nts = np.linspace(0, t, n)
f = 200
sin1 = sinusoidal_signal(1, f, t, 1, n)
sin2 = sinusoidal_signal(1, f, t, 0.5, n)
sin3 = sinusoidal_signal(1, f, t, 2, n)
sin4 = sinusoidal_signal(1, f, t, 4, n)

fig, axs = plt.subplots(4)
fig.suptitle("4 Sin Signals")

for ax in axs.flat:
    ax.set_xlim([0, 0.1])

axs[0].plot(nts, sin1)
axs[1].plot(nts, sin2)
axs[2].plot(nts, sin3)
axs[3].plot(nts, sin4)
plt.show()

z = numpy.random.normal(size=(1, n))[0]


def find_gamma(x: ndarray, z: ndarray, SNR: float) -> float:
    x_norm = np.linalg.norm(x)
    z_norm = np.linalg.norm(z)

    return np.sqrt((x_norm / z_norm) / SNR)


SNRs = [0.1, 1, 10, 100]
new_sin = []
for SNR in SNRs:
    gamma = find_gamma(sin1, z, SNR)
    new_sin.append(sin1 + gamma * z)

fig, axs = plt.subplots(4)
fig.suptitle("4 SNRs")

for ax in axs.flat:
    ax.set_xlim([0, 0.1])

axs[0].plot(nts, new_sin[0])
axs[1].plot(nts, new_sin[1])
axs[2].plot(nts, new_sin[2])
axs[3].plot(nts, new_sin[3])
plt.show()

"""Exercise 3"""
fs = 44100
rate = int(10e5)

# (a)
t = 1
n = 1600
sin_wav_1 = sinusoidal_signal(1, 400, t, 0, n)

# (b)
t = 3
n = 800
sin_wav_2 = sinusoidal_signal(1, 800, t, 0, n)

# (c)
t = 1
n = 1_000_000
signal = sinusoidal_signal(1, 240, t, 0, n)
sawtooth_signal = np.arcsin(np.abs(signal))
sawtooth_signal = np.mod(sawtooth_signal, 0.1)

# (d)
t = 1000
n = 10_000
square = np.sign(sinusoidal_signal(1, 300, t, 0, n))

# TODO: same for the others
sw.write("sin1.wav", rate, sin_wav_1)
rate, x = sw.read("sin1.wav")
sounddevice.play(x, fs)


"""Exericise 4"""

fig, axs = plt.subplots(3)
fig.suptitle("Added Samplings")


axs[0].set_xlim([0, 0.01])
axs[1].set_xlim([0, 0.001])
axs[2].set_xlim([0, 0.005])

t = 1
n = 1_000_000
nts = np.linspace(0, t, n)

sin_add = sinusoidal_signal(1, 240, t, 0, n)
signal_add = sinusoidal_signal(1, 240, t, 0, n)
sawtooth_add = np.arcsin(np.abs(signal_add))
sawtooth_add = np.mod(sawtooth_add, 0.1)
added = np.add(sin_add, sawtooth_add)

axs[0].plot(nts, sin_add)
axs[1].plot(nts, sawtooth_add)
axs[2].plot(nts, added)

plt.show()

"""Exercise 5"""
t = 1
n = 1000
sin_low = sinusoidal_signal(1, 200, t, 0, n)
sin_high = sinusoidal_signal(1, 1000, t, 0, n)
low_high_concat = np.concatenate((sin_low, sin_high))

# TODO: create folder for wav files
# TODO: create folder and save plot files
sw.write("low_vs_high.wav", rate, low_high_concat)
rate, x = sw.read("low_vs_high.wav")
sounddevice.play(x, fs)

"""Exercise 6"""
t = 1
n = 1000
nts = np.linspace(0, t, n)
sin_f_1 = sinusoidal_signal(1, n / 2, t, 0, n)
sin_f_2 = sinusoidal_signal(1, n / 4, t, 0, n)
sin_f_3 = sinusoidal_signal(1, 0, t, 0, n)

fig, axs = plt.subplots(3)
fig.suptitle("Fundamental Frequency")

for ax in axs.flat:
    ax.set_xlim(0, 0.1)

axs[0].plot(nts, sin_f_1)
axs[1].plot(nts, sin_f_2)
axs[2].plot(nts, sin_f_3)
plt.show()

"""Exercise 7"""
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
plt.show()

"""Exercise 8"""
error = lambda true, pred: (true - pred) ** 2

interval = [-np.pi / 2, np.pi / 2]
n = 10_000
nts = np.linspace(interval[0], interval[1], n)
sin_aproximation = np.sin(nts)
error_values = error(sin_aproximation, nts)
pade = lambda a: (a - (7 * a**3) / 60) / 1 + (a**2) / 20

fig, axs = plt.subplots(4)
fig.suptitle("Aproximations")

for ax in axs.flat:
    ax.set_xlim(interval)

axs[0].plot(nts, sin_aproximation)
axs[1].plot(nts, nts)
axs[2].plot(nts, error_values)
axs[3].plot(nts, pade(nts))
plt.show()
