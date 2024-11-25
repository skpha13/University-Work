from dataclasses import dataclass

import numpy as np


@dataclass
class Signals:
    """Represents a signal with its characteristics and visualization options.

    Used in L04 for both exercise 2 and exerice 3.

    Attributes:
        frequency (str): The frequency of the signal represented as a string.
                         Also used as title when plotting the graph.

        plot (np.ndarray): A NumPy array containing data points for plotting the
                           signal.

        scatter (np.ndarray): A NumPy array containing data points for plotting
                              the sample points.

        color (str): A string representing the color used for matplotlib.pyplot.plt
    """

    frequency: str
    plot: np.ndarray
    scatter: np.ndarray
    color: str
