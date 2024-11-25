import os

import matplotlib.pyplot as plt
import numpy as np
from utils.plot import plot_with_samples
from utils.sinewave import sinusoidal_signal
from utils.custom_types import Signals

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

plt.rc("axes", titlesize=10)


class SamplingFrequencyAnalysis:
    def __init__(self, ns: int = 7) -> None:
        self.t = 1
        self.n = 1000
        self.ns = ns

        self.x_domain = np.linspace(0, self.t, self.n)
        self.nts = np.linspace(0, self.t, self.ns)

        self.signals: list[Signals] = [
            Signals(
                "16Hz",
                sinusoidal_signal(1, 16, self.t, 0, self.n),
                sinusoidal_signal(1, 16, self.t, 0, self.ns),
                "slateblue",
            ),
            Signals(
                "10Hz",
                sinusoidal_signal(1, 10, self.t, 0, self.n),
                sinusoidal_signal(1, 10, self.t, 0, self.ns),
                "purple",
            ),
            Signals(
                "4Hz",
                sinusoidal_signal(1, 4, self.t, 0, self.n),
                sinusoidal_signal(1, 4, self.t, 0, self.ns),
                "green",
            ),
        ]

    def plot(self, name: str) -> None:
        plot_with_samples(name, self.x_domain, self.signals, self.nts, [0, 1])


if __name__ == "__main__":
    obj = SamplingFrequencyAnalysis(ns=7)
    obj.plot("Sub-Nyquist Frequency")
