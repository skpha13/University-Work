import decimal

eps = 1.0 * 10**-5


def generate_series(x: float, k: int = 1) -> list[float]:
    """Generates a series using the following formula:
    x(k+1) =
        2 * x(k) if x(k) is in [0, 0.5)
        2 * x(k) - 1 if x(k) is in (0.5, 1]

    Args:
        x (float):
            The initial value for the series.
        k (int, optional):
            The number of transformations to apply to `x`. Default is 1.

    Returns:
        List[float]: A list containing the generated series of transformed values.
    """
    result: list[float] = [x]

    for _ in range(k):
        if 0 - eps <= result[-1] < 0.5:
            result.append(
                decimal.Decimal(2 * result[-1]).quantize(decimal.Decimal("0.00"), rounding=decimal.ROUND_DOWN)
            )
        elif 0.5 < result[-1] <= 1 + eps:
            result.append(
                decimal.Decimal(2 * result[-1] - 1).quantize(decimal.Decimal("0.00"), rounding=decimal.ROUND_DOWN)
            )

    return result
