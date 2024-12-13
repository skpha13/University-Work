import numpy as np
import scipy

np.random.seed(0)


def main():
    def compute_probability(xs: list[float], mean: float, sigma: float):
        x1 = mean

        mean_apriori = scipy.stats.norm.pdf(x1, 100, 50)
        dispersion_apriori = scipy.stats.uniform.pdf(sigma, 1, 70)
        probability_apriori = mean_apriori * dispersion_apriori

        verisimilities = scipy.stats.norm.pdf(xs, mean, sigma)
        verisimility = np.prod(verisimilities)

        return verisimility * probability_apriori

    xs = [82, 106, 120, 68, 83, 89, 130, 92, 99, 89]
    means = [70, 75, 80, 85, 90, 95, 100]
    sigmas = [5, 10, 15, 20]
    results = []

    for mean in means:
        for sigma in sigmas:
            probability = compute_probability(xs, mean, sigma)
            results.append((probability, mean, sigma))

    max_probability = max(results, key=lambda x: x[0])
    print(f"Value: {max_probability[0]}, Mean: {max_probability[1]}, Sigma: {max_probability[2]}")


if __name__ == "__main__":
    main()
