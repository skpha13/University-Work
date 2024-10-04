import numpy as np

def sinusoidal_signal(A: float = 1, f: float = 1, t: float = 1, phi: float = 0, n: int = 100) -> np.ndarray:
    ts = np.linspace(0, t, n)
    return A * np.sin(2 * np.pi * f * n * ts + phi)