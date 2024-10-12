"""Exercise 6"""

import numpy as np

from utils.plot import plot
from utils.sinewave import sinusoidal_signal

t = 1
n = 1000
nts = np.linspace(0, t, n)
sin_freq_half = sinusoidal_signal(1, n / 2, t, 0, n)
sin_freq_quarter = sinusoidal_signal(1, n / 4, t, 0, n)
sin_freq_zero = sinusoidal_signal(1, 0, t, 0, n)

plot(
    "Fundamental Frequency",
    nts,
    sin_freq_half,
    sin_freq_quarter,
    sin_freq_zero,
    xlim=[0, 0.5],
)

""" Observations:

General observation: The graphs were computed for half of the time period as they are symetrical

    - For the last case where signal frequency is 0, there is only the horizontal line y = 0, because
a frequency of 0 means there is no oscillation, thus resulting in a constant line over the time t.

    - For the half fundamental frequency, according to Nyquits-Shannon sampling theorem, we have
a high enough sampling frequency (at least twice as the highest frequency from the signal) to reconstruct
the waveform correctly.

    - For the quarter fundamental frequency, we have a sampling frequency 4 times bigger, thus having a 
better representation of the waveform.
"""
