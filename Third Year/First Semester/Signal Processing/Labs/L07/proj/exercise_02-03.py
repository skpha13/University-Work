import os

import numpy as np
import scipy
from matplotlib import pyplot as plt
from utils.fourier import filter_noise_2d
from utils.signal_to_noise_ratio import compute_snr_of_image

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

np.random.seed(0)

cmap = plt.colormaps["gray"]

raccoon = scipy.datasets.face(gray=True)

pixel_noise = 200
noise = np.random.randint(-pixel_noise, high=pixel_noise + 1, size=np.shape(raccoon))
raccoon_noise = raccoon + noise

plt.imshow(raccoon, cmap=cmap)
plt.savefig("plots/Initial Raccoon.pdf", format="pdf")
plt.show()

snr = compute_snr_of_image(raccoon, raccoon_noise)
print("DESIRED SNR: 7")
print(f"COMPUTED SNR before filtering: {snr:.2f} Db")

radiuses = [47, 48, 49, 50, 51, 52, 53]
snrs = []

for radius in radiuses:
    filtered_raccoon = filter_noise_2d(raccoon_noise, radius)
    snrs.append(compute_snr_of_image(raccoon, filtered_raccoon))


optimal_radius_index = np.argmin(snrs)
print(f"COMPUTED SNR after filtering: {snrs[optimal_radius_index]:.2f} Db")
print(f"RADIUS: {radiuses[optimal_radius_index]}")

filtered_raccoon = filter_noise_2d(raccoon_noise, radiuses[optimal_radius_index])
plt.imshow(filtered_raccoon, cmap=cmap)
plt.savefig("plots/Filtered Raccoon.pdf", format="pdf")
plt.show()
