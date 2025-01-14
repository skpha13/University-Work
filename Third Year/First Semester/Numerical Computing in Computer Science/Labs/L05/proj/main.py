import matplotlib.pyplot as plt
import numpy as np
import scipy
from dictlearn import DictionaryLearning, methods
from skimage.color import rgb2gray
from sklearn.feature_extraction.image import extract_patches_2d, reconstruct_from_patches_2d
from sklearn.preprocessing import normalize


def calculate_psnr(original, reconstructed, max_pixel_value=1.0):
    """
    Calculate the PSNR (Peak Signal-to-Noise Ratio) between two images.

    Parameters:
    original (ndarray): The original image.
    reconstructed (ndarray): The reconstructed image.
    max_pixel_value (float): The maximum pixel value of the images (default is 1.0 for 8-bit images).

    Returns:
    float: The PSNR value in decibels (dB).
    """
    mse = np.mean((original - reconstructed) ** 2)
    if mse == 0:
        return float("inf")  # PSNR is infinite if MSE is zero (images are identical)
    psnr = 10 * np.log10(max_pixel_value**2 / mse)
    return psnr


if __name__ == "__main__":
    p = 8  # dimension of patch (number of pixels)
    s = 16  # sparsity
    N = 625  # number of total patches
    n = 1000  # number of atoms in dictionary
    K = 50  # number of iterations of DL
    sigma = 0.075  # standard deviation of noise
    image_shape = (32, 32)

    image = rgb2gray(scipy.datasets.face())
    image = image[250 : 250 + image_shape[0], 500 : 500 + image_shape[1]]
    shape = image.shape
    print(f"Original Image Shape: {image.shape}")

    image_noisy = image + sigma * np.random.randn(*image.shape)
    Ynoisy = extract_patches_2d(image_noisy, patch_size=(p, p))
    print(f"Noisy Image Shape Patches: {Ynoisy.shape}")

    Ynoisy = Ynoisy.reshape(Ynoisy.shape[0], -1)
    print(f"Noisy Image Shape Patches after Reshape: {Ynoisy.shape}")

    Ynoisy = Ynoisy.T
    print(f"Noisy Image Shape Patches after Reshape and Transpose: {Ynoisy.shape}")

    patches_mean = np.mean(Ynoisy, axis=0, keepdims=True)
    Ynoisy = Ynoisy - patches_mean

    choices = np.random.choice(Ynoisy.shape[1], N)
    patches = Ynoisy[:, choices]
    patches_mean_selected = patches_mean[:, choices].T
    print(f"Selected Patches Shape: {patches.shape}")

    D0 = np.random.randn(p * p, n)
    D0 = normalize(D0, axis=0, norm="max")

    dl = DictionaryLearning(
        n_components=n,
        max_iter=K,
        fit_algorithm="ksvd",
        n_nonzero_coefs=s,
        code_init=None,
        dict_init=D0,
        params=None,
        data_sklearn_compat=False,
    )
    dl.fit(patches)
    D = dl.D_

    Xc, err = methods.omp(patches, D, n_nonzero_coefs=s)

    image_reconstructed_patches = (D @ Xc).T + patches_mean_selected
    image_reconstructed = reconstruct_from_patches_2d(
        np.reshape(image_reconstructed_patches, shape=(N, p, p)),
        image_size=shape,
    )
    print(f"Reconstructed Image Shape: {image_reconstructed.shape}")

    fig, axs = plt.subplots(1, 3, figsize=(16, 7))
    fig.suptitle("Image Comparison")

    cmap = "gray"
    titles = ["Original image", "Noisy image", "Reconstructed image"]
    images = [image, image_noisy, image_reconstructed]
    psnrs = [
        calculate_psnr(image, image),
        calculate_psnr(image, image_noisy),
        calculate_psnr(image, image_reconstructed),
    ]

    for i, ax in enumerate(axs):
        ax.imshow(images[i], cmap=cmap)
        ax.axis("off")
        ax.text(
            0.5,
            -0.05,
            f"{titles[i]}, PSNR: {psnrs[i]:.4f}",
            ha="center",
            va="center",
            fontsize=16,
            transform=ax.transAxes,
        )

    fig.tight_layout()
    fig.show()
