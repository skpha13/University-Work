import json
import os
import time

import matplotlib.pyplot as plt
import numpy as np
from utils.fourier import fourier_transform

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

N = [128, 256, 512, 1024, 2048, 4096, 8192]


def calcutate_times(N: list[int]) -> dict[str, list[float]]:
    times: dict[str, list[float]] = {"my_dft": [], "np_fft": []}

    for n in N:
        signal = np.random.uniform(-1, 1, n)

        start_my_dft = time.perf_counter()
        fourier_transform(signal)
        end_my_dft = time.perf_counter()

        start_np_fft = time.perf_counter()
        np.fft.fft(signal)
        end_np_fft = time.perf_counter()

        times["my_dft"].append(end_my_dft - start_my_dft)
        times["np_fft"].append(end_np_fft - start_np_fft)

    return times


file_path = "misc/times.json"
try:
    with open(file_path, "r") as input_file:
        times = json.load(input_file)
except FileNotFoundError:
    times = calcutate_times(N)

    with open(file_path, "w", encoding="utf-8") as output_file:
        json.dump(times, output_file, indent=4)


fig, axs = plt.subplots(1)
fig.suptitle("Time Benchmark")
axs.plot(N, times["my_dft"], color="r")
axs.plot(N, times["np_fft"], color="b")

plt.yscale("log")
plt.savefig("plots/Time Benchmark.pdf", format="pdf")
plt.savefig("plots/Time Benchmark.png", format="png")
plt.show()
