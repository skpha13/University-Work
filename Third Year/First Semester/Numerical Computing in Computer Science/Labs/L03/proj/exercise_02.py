import os
import random

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.image import imread
from skimage.color import rgb2gray

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

seed = 0
np.random.seed(seed)
random.seed(seed)

img = rgb2gray(imread("./imgs/lena.png"))
U, S, V = np.linalg.svd(img)

ks = [220, 100, 10]

for k in ks:
    U_truncated = U[:, 1:k]
    S_truncated = np.diag(S)[1:k, 1:k]
    V_truncated = V[1:k, :]

    A_compressed = np.matmul(U_truncated, S_truncated)
    A_compressed = np.matmul(A_compressed, V_truncated)

    plt.savefig(f"./plots/lenna_compressed_{k:02}.png", format="png")
    plt.imshow(A_compressed, cmap="grey")
    plt.show()
