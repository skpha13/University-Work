import numpy as np
import scipy

np.random.seed(0)


def main():
    mean = 90
    x1 = 90
    sigma = 10

    mean_apriori = scipy.stats.norm.pdf(x1, 100, 50)
    dispersion_apriori = scipy.stats.uniform.pdf(sigma, 1, 70)
    probability_apriori = mean_apriori * dispersion_apriori

    xs = [82, 106, 120, 68, 83, 89, 130, 92, 99, 89]
    verisimilities = scipy.stats.norm.pdf(xs, mean, sigma)
    verisimility = np.prod(verisimilities)

    print(f"Posteriori Probability: {verisimility * probability_apriori}")


if __name__ == "__main__":
    main()
