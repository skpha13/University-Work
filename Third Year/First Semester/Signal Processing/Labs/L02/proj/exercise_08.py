"""Exercise 8"""

import numpy as np
from matplotlib import pyplot as plt

error = lambda true, pred: (true - pred) ** 2
pade = lambda a: (a - (7 * a**3) / 60) / (1 + (a**2) / 20)

interval = [-np.pi / 2, np.pi / 2]
n = 10_000
nts = np.linspace(interval[0], interval[1], n)
sin = np.sin(nts)
errors_x = error(sin, nts)
errors_pade = error(sin, pade(nts))


def plot(name: str, set_yaxis_logarithmic: bool = False):
    fig, axs = plt.subplots(4, figsize=(6, 8))
    fig.suptitle("Aproximations")

    for ax in axs.flat:
        ax.set_xlim(interval)

        if set_yaxis_logarithmic:
            ax.set_yscale("log")

    axs[0].title.set_text("Sin(x) vs X")
    axs[0].plot(nts, sin, label="sin(x)")
    axs[0].plot(nts, nts, label="x")
    axs[0].legend()

    axs[1].title.set_text("Sin(x) vs Pade(x)")
    axs[1].plot(nts, sin, label="sin(x)")
    axs[1].plot(nts, pade(nts), label="pade(x)")
    axs[1].legend()

    axs[2].title.set_text("Error Graph for Sin(x) vs X")
    axs[2].plot(nts, errors_x)

    axs[3].title.set_text("Error Graph for Sin(x) vs Pade(x)")
    axs[3].plot(nts, errors_pade)

    plt.tight_layout()
    plt.savefig(fname=f"./plots/{name}.pdf", format="pdf")
    plt.show()


# approximations plots
plot(name="Approximations")

# Approximations with y axis logarithmic
plot(name="Approximations with y axis logarithmic", set_yaxis_logarithmic=True)
