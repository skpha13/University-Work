from utils.polynomials import get_roots


def main():
    coefficients = [1, 2, 1]

    roots = get_roots(coefficients)
    print(roots)


if __name__ == "__main__":
    main()
