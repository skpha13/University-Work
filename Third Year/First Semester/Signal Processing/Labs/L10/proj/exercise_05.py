import numpy as np
from utils.models import AR
from utils.polynomials import get_roots
from utils.signal import predefined_series


def main():
    N = 1000
    series = predefined_series(N)

    p = 16
    m = 128

    model = AR(p, m)
    model.fit(series)

    x = model.x
    # to respect the order of the get_roots function
    x = np.insert(x, 0, 1)[::-1]

    roots = get_roots(x)
    norms = np.abs(roots)
    is_stationary = not any(norm > 1 for norm in norms)

    print(f"Is a stationary model: {is_stationary}")


if __name__ == "__main__":
    main()
