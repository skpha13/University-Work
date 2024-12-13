import matplotlib.pyplot as plt
import numpy as np
import scipy

np.random.seed(0)


def main():
    mean = 90
    sigma = 10
    n = 1000
    ts = np.linspace(0, 1, n)
    x = np.linspace(mean - 3 * sigma, mean + 3 * sigma, n)

    distribution = scipy.stats.norm.pdf(x, loc=mean, scale=sigma)

    plt.plot(ts, distribution)  # TODO: save plot
    plt.show()


if __name__ == "__main__":
    main()
