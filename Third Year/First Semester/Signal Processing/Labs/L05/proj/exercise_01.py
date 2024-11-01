import os

import numpy as np
from matplotlib import pyplot as plt
from utils.signal import SignalAnalyzer

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)


train_signal = np.genfromtxt("data/train.csv", delimiter=",")[1:, 2]
train_samples = np.genfromtxt("data/train.csv", delimiter=",")[1:, 0]
train_sample_rate = 1 / 3600


answers = f"""
        a)
        
    The signal is sampled once every hour. This means the sampling frequency (rate) is 1 sample per hour.
    To express this in Hz, note that 1 hour is 3600 seconds:
    fs = 1 / 3600 Hz
    
        b)
        
    We have a total of 18,288 samples, and since samples are taken every hour, there are 24 samples per day. 
    Dividing the total samples by the daily sample rate gives:
    
    18288 / 24 = 762 days
    
    Looking at the train.csv file, the first sample is recorded on 25-08-2012, and the last sample is on 25-09-2014. This confirms a time span of 762 days.
    
        c)
        
    Maximum Frequency: {SignalAnalyzer.find_max_frequency(train_signal, train_sample_rate)}    
"""

# a) & b) & c)
print(answers)

# d)
SignalAnalyzer.plot_frequency_magnitude("Magnitude of Signal", train_signal, train_sample_rate)

# e)
try:
    train_signal_norm = SignalAnalyzer.remove_continuous_component(train_signal)
    name = "Signal Without Continous Component"

    fig, ax = plt.subplots(1, figsize=(10, 5))
    fig.suptitle(name)

    plt.xlim([np.min(train_samples), np.max(train_samples)])

    ax.plot(train_samples, train_signal_norm, linewidth=0.75)

    plt.savefig(f"plots/{name}.pdf", format="pdf")
    plt.savefig(f"plots/{name}.png", format="png")

    plt.show()

except ValueError as err:
    print(err)

# f)
train_signal_norm = SignalAnalyzer.remove_continuous_component(train_signal)
top_k_frequencies = SignalAnalyzer.get_top_k_frequencies(train_signal_norm, train_sample_rate, 4)
time_in_seconds = np.divide(1, top_k_frequencies)
time_in_days = np.divide(time_in_seconds, 3600 * 24)
time_in_months = np.divide(time_in_days, 31)
time_in_years = np.divide(time_in_months, 12)

print(top_k_frequencies)
print(time_in_seconds)
print(time_in_days)
print(time_in_months)
print(time_in_years)

print(np.multiply(top_k_frequencies, 3600 * 24 * 365))
