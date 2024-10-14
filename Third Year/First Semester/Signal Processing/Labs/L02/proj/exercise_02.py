"""Exercise 2"""

import random

import numpy as np

from utils.plot import plot
from utils.signal_to_noise_ratio import find_gamma
from utils.sinewave import sinusoidal_signal

t = 1
n = 10_000
nts = np.linspace(0, t, n)
f = 200

original_signals = [
    sinusoidal_signal(1, f, t, 1, n),
    sinusoidal_signal(1, f, t, 0.5, n),
    sinusoidal_signal(1, f, t, 2, n),
    sinusoidal_signal(1, f, t, 4, n),
]

plot("4 Sin Signals", nts, *original_signals, xlim=[0, 0.1])

# set seed to have constant results
seed = 1
np.random.seed(seed)
random.seed(seed)

z = np.random.normal(size=(1, n))[0]

SNRs = [0.1, 1, 10, 100]
SNR_signals = []
for SNR in SNRs:
    gamma = find_gamma(original_signals[0], z, SNR)
    SNR_signals.append(original_signals[0] + gamma * z)

plot("4 SNRs on the first Sin Signal", nts, *SNR_signals, xlim=[0, 0.1])
