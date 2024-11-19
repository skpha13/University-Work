import os

import matplotlib.pyplot as plt
import numpy as np
from utils.images import compute_image

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)


shape = (256, 256)
cmap = "grey"

f1 = lambda x, y: np.sin(2 * np.pi * x + 3 * np.pi * y)
matrix1 = compute_image(shape, f1, True)

f2 = lambda x, y: np.sin(4 * np.pi * x) + np.cos(6 * np.pi * y)
matrix2 = compute_image(shape, f2, True)

plt.imshow(matrix1, cmap=cmap)
plt.savefig("plots/First Function.pdf", format="pdf")
plt.show()

plt.imshow(matrix2, cmap=cmap)
plt.savefig("plots/Second Function.pdf", format="pdf")
plt.show()

f3 = lambda x, y: 1 if (x == 0 and y == 5) or (x == 0 and y == shape[0] - 5) else 0
matrix3 = compute_image(shape, f3)
reverse_matrix3 = np.real(np.fft.ifft2(matrix3))

plt.imshow(reverse_matrix3, cmap=cmap)
plt.savefig("plots/First Spectrum.pdf", format="pdf")
plt.show()

matrix4 = matrix3.T
reverse_matrix4 = np.real(np.fft.ifft2(matrix4))

plt.imshow(reverse_matrix4, cmap=cmap)
plt.savefig("plots/Second Spectrum.pdf", format="pdf")
plt.show()

matrix5 = matrix3 + matrix4
reverse_matrix5 = np.real(np.fft.ifft2(matrix5))

plt.imshow(reverse_matrix5, cmap=cmap)
plt.savefig("plots/Third Spectrum.pdf", format="pdf")
plt.show()
