import os

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from scipy.signal import butter, cheby1, lfilter

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)


def save_plot(name: str) -> None:
    global fig

    fig.savefig(fname=f"plots/{name}.pdf", format="pdf")
    fig.savefig(fname=f"plots/{name}.png", format="png")


train_df = pd.read_csv("data/train.csv", parse_dates=["Datetime"], dayfirst=True)
train_samples = train_df["ID"].values[1:]
train_signal = train_df["Count"].values[1:]
train_sample_rate = 1 / 3600

# a)

size = 72
x = train_signal[:size]
x_samples = train_samples[:size]
ws = [5, 9, 13, 17]
plot_name = "Moving Average"

# b)

filtered_signals: list[np.ndarray] = []
for w in ws:
    filtered_signals.append(np.convolve(x, np.ones(w), "valid") / w)

fig, ax = plt.subplots(1)
fig.suptitle(plot_name)

for filtered_signal in filtered_signals:
    ax.plot(np.linspace(0, size, len(filtered_signal)), filtered_signal)

fig.legend([f"window_size = {w}" for w in ws])

save_plot(plot_name)
fig.show()

# c)

answer_c = """
        c)
        
    I decided to have a cutoff frequency at the 95th percentile from the spectrum of frequencies. In the
previous lab it worked quite well for the whole dataset.

    So in our case fs = 1 / 3600 => Cutoff Frequency = 1 / 3600 * 0.05 = 1 / 72_000 Hz
    
    Now, if we want to normalize the frequency between 0 and 1 (with respect to the Nyquist frequency),
we note that 5% of the total frequency corresponds to 10% of the Nyquist frequency. This gives a normalized frequency of: 0.1
"""
print(answer_c)

# d) & e)

cutoff_frequency = train_sample_rate * 0.05
order = 5
rp = 5

b, a = butter(order, cutoff_frequency, "low", analog=False, output="ba", fs=train_sample_rate)
filtered_butter = lfilter(b, a, x)

b_cheby, a_cheby = cheby1(order, rp, cutoff_frequency, "low", analog=False, output="ba", fs=train_sample_rate)
filtered_cheby = lfilter(b_cheby, a_cheby, x)

plot_name = "Filtered Signal"
fig, ax = plt.subplots(1)
fig.suptitle(plot_name)

ax.plot(x_samples, x)
ax.plot(x_samples, filtered_butter)
ax.plot(x_samples, filtered_cheby)

plt.legend(["Rough Signal", "Butterwroth filter", "Chebyshev filter"])

save_plot(plot_name)
fig.show()

answer_e = """
        e)
    
    I would choose the Chebyshev filter because it has a steeper transition meaning it cuts abruptly than the Butterworth one.
Although the Butterworth filter doesn't have ripples in the passband I find it better to be more harsh on the transition.
"""
print(answer_e)

# f)
