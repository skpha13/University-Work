import numpy as np
from matplotlib import pyplot as plt
from scipy.io import wavfile
from utils.signal import segment_signal

sample_rate, audio_signal = wavfile.read("wavs/vocals.wav")

segmented_signal = segment_signal(audio_signal)

fft_signal = np.fft.fft(segmented_signal, axis=1)

spectrogram = np.transpose(
    np.abs(fft_signal)[:, : fft_signal.shape[1] // 2]  # only take the first half of values since its simetrical
)

# applied logarithmic scaling, and a small constant to avoid log(0)
spectrogram = 10 * np.log10(spectrogram + 1e-10)

# extract the samples frequencies
frequencies = np.fft.fftfreq(segmented_signal.shape[1], d=1 / sample_rate)[: fft_signal.shape[1] // 2]

plt.figure(figsize=(10, 6))
plt.imshow(
    spectrogram,
    aspect="auto",
    extent=(0, len(audio_signal) / sample_rate, frequencies[0], frequencies[-1]),
    origin="lower",
    cmap="magma",
    vmin=0,
    vmax=100,
)
plt.colorbar(label="Magnitude")
plt.xlabel("Time (s)")
plt.ylabel("Frequency (kHz)")

name = "Spectrogram of Audio Signal"
plt.title(name)
plt.savefig(f"plots/{name}.pdf", format="pdf")
plt.savefig(f"plots/{name}.png", format="png")

plt.show()
