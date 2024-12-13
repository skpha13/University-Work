import numpy as np
import scipy

np.random.seed(0)


def main():
    mean = 90
    sigma = 10

    xs = [82, 106, 120, 68, 83, 89, 130, 92, 99, 89]
    verisimilities = scipy.stats.norm.pdf(xs, mean, sigma)

    print(f"Verisimility: {np.prod(verisimilities)}")


if __name__ == "__main__":
    main()
