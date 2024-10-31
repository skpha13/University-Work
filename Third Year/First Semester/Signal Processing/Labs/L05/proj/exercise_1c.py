import numpy as np

signal = np.genfromtxt("data/train.csv", delimiter=",")[1:, 2]

sample_rate = 1 / 3600
fourier = np.fft.fft(signal)
frequencies = np.fft.fftfreq(len(signal), 1 / sample_rate)

print(f"Maximum Frequency: {max(frequencies)}")
