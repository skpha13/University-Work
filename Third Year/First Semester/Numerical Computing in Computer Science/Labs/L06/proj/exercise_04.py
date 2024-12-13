import numpy as np
import scipy

np.random.seed(0)


def main():
    sigma = 10
    x1 = 90

    mean_apriori = scipy.stats.norm.pdf(x1, 100, 50)
    dispersion_apriori = scipy.stats.uniform.pdf(sigma, 1, 70)
    probability_apriori = mean_apriori * dispersion_apriori

    print(f"Apriori Probability: {probability_apriori:.6f}")


if __name__ == "__main__":
    main()
