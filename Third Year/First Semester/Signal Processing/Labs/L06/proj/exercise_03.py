import numpy as np
from utils.sinewave import sinusoidal_signal

N = 10_000
t = 1
nts = np.linspace(0, t, N)

signal = sinusoidal_signal(1, 100, t, 0, N)
