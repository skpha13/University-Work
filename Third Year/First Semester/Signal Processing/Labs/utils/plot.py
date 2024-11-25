import os
from typing import Literal, Union

import matplotlib.pyplot as plt
import numpy as np

from utils.custom_types import Signals

# create folder if it does not exist
os.makedirs(f"{os.getcwd()}/plots", exist_ok=True)


def plot(
    name: str,
    x: Union[np.ndarray, list],
    *ys: Union[np.ndarray, list[list]],
    xlim: list[float] | None = None,
    titles: list[str] | None = None,
    file_format: Literal["pdf", "png", "svg"] = "pdf",
) -> None:
    """Plots multiple line graphs in subplots and saves them as a file.

    Args:
        name (str): The name of the plot, used for the title and the file name.
        x (np.ndarray, list): The x values for the plot.
        *ys (np.ndarray, list[list]): Any number of y arrays for the plots.
        xlim (list[float], optional): The limits for the x-axis as a list [xmin, xmax]. If None, default limits are used.
        titles (list[str], optional): The titles for each subplot. If None, no titles.
        file_format: (Literal["pdf", "png", "svg"], optional): The format in which to save the plot file. Defaults to "png".

    Returns:
        None
    """
    fig, axs = plt.subplots(len(ys), squeeze=False)
    fig.suptitle(name)

    index_title = 0
    for ax, y in zip(axs.flat, ys):
        ax.plot(x, y)

        if xlim is not None:
            ax.set_xlim(xlim)

        if titles is not None:
            ax.set_title(titles[index_title])

        index_title += 1

    plt.tight_layout()
    plt.savefig(fname=f"./plots/{name}.{file_format}", format=f"{file_format}")
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


def plot_with_samples(
    name: str, x: np.ndarray, ys: list[Signals], x_samples: np.ndarray, xlim: list[float] | None = None
) -> None:
    """Plots signals along with specified sample points.

    This function generates a series of subplots for a list of signals and marks
    sample points on each signal plot. It saves the resulting plots as both
    PDF and PNG files.

    Args:
        name (str): The name used for the title of the plot and the filenames for saving the plots.

        x (np.ndarray): A NumPy array representing the x-axis values (e.g., time values) for plotting the signals.

        ys (List[Signals]): A list of `Signals` objects that contain the properties of each signal to be plotted.
                            Each object should include its frequency, plot data, scatter data, and color for visualization.

        x_samples (np.ndarray): A NumPy array containing x-axis values for the sample points to be plotted on each signal's
                                graph. These points are highlighted with scatter plots.

        xlim (Optional[List[float]]): A list containing two float values that specify the limits for the x-axis.
                                      If None, the default limits will be set based on the signal data.
    """

    fig, axs = plt.subplots(len(ys) + 1)
    fig.suptitle(name)

    axs[0].plot(x, ys[0].plot, color="slateblue")
    axs[0].set_title(ys[0].frequency)
    axs[0].set_xlim([0, 1])

    for ax, signal in zip(axs[1:], ys):
        ax.plot(x, signal.plot, color=signal.color, zorder=1)
        ax.scatter(x_samples, signal.scatter, color="yellow", alpha=1, zorder=2, clip_on=False)

        ax.set_title(signal.frequency)

        if xlim is not None:
            ax.set_xlim(xlim)

    plt.tight_layout()

    plt.savefig(f"./plots/{name}.pdf", format="pdf")
    plt.savefig(f"./plots/{name}.png", format="png")
    plt.show()
