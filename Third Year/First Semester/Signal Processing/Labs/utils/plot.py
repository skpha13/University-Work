import os
from typing import Union

import matplotlib.pyplot as plt
import numpy as np

# create folder if it does not exist
os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)


def plot(
    name: str, x: Union[np.ndarray, list], *ys: Union[np.ndarray, list[list]], xlim: list[float] | None = None
) -> None:
    """Plots multiple line graphs in subplots and saves them as a PDF file.

    Args:
        name (str): The name of the plot, used for the title and the file name.
        x (np.ndarray): The x values for the plot.
        *ys (np.ndarray): Any number of y arrays for the plots.
        xlim (list[float], optional): The limits for the x-axis as a list [xmin, xmax]. If None, default limits are used.

    Returns:
        None
    """
    fig, axs = plt.subplots(len(ys))
    fig.suptitle(name)

    for ax, y in zip(axs.flat, ys):
        ax.plot(x, y)

        if xlim is not None:
            ax.set_xlim(xlim)

    plt.savefig(fname=f"./plots/{name}.pdf", format="pdf")
    plt.show()


def stem(name: str, x: np.ndarray, y: np.ndarray) -> None:
    """Plots a stem graph and saves it as a PDF file.

    Args:
        name (str): The name of the plot, used for the title and the file name.
        x (np.ndarray): The x values for the plot.
        y (np.ndarray): The y values for the plot.

    Returns:
        None
    """
    fig, ax = plt.subplots()
    fig.suptitle(name)
    ax.stem(x, y)
    plt.savefig(fname=f"./plots/{name}.pdf", format="pdf")
    plt.show()
