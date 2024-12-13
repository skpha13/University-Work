import numpy as np
import scipy

from utils import my_pdf

np.random.seed(0)


def main():
    mean = 90
    sigma = 10

    x1 = 82
    scipy_verisimility = scipy.stats.norm.pdf(x1, loc=mean, scale=sigma)
    my_verisimility = my_pdf([x1], mean, sigma)[0]

    print(
        f"""
        My verisimility for x1 = {x1}: {my_verisimility:.6f}
        Scipy verisimility for x1 = {x1}: {scipy_verisimility:.6f} 
    """
    )


if __name__ == "__main__":
    main()
