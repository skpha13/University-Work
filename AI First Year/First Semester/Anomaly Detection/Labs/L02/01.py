import numpy as np
import matplotlib.pyplot as plt

np.random.seed(42)

n = 100
mean = 0
sigmas = [0.1, 1, 3]
a, b = 2, 1


def generate_linear_model(n, x_var, y_var):
    x = np.random.normal(0, x_var, size=n // 4)
    eps = np.random.normal(0, np.sqrt(y_var), size=n // 4)
    y = a * x + b + eps

    return x, y


for idx, sigma in enumerate(sigmas):
    x_normal, y_normal = generate_linear_model(n, sigma / 2, sigma)
    x_high_x, y_high_x = generate_linear_model(n, sigma, sigma)
    x_high_y, y_high_y = generate_linear_model(n, sigma / 2, sigma * 1e2)
    x_high_xy, y_high_xy = generate_linear_model(n, sigma, sigma * 1e2)

    x = np.concatenate([x_normal, x_high_x, x_high_y, x_high_xy])
    y = np.concatenate([y_normal, y_high_x, y_high_y, y_high_xy])

    X = np.column_stack([x, np.ones_like(x)])
    U, _, _ = np.linalg.svd(X, full_matrices=False)
    H = U @ U.T
    top_k = np.argsort(np.diag(H))[-20:]

    plt.figure(figsize=(6, 4))
    plt.scatter(x, y, label="Points", color="b", alpha=0.5)
    plt.scatter(x[top_k], y[top_k], color="r", label="High Leverage")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title(f"Noise variance $\sigma^2$ = {sigma}")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"./pdfs/leverage_{idx}.pdf")
