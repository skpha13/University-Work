import os

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from utils.plot import plot
from utils.signal import SignalAnalyzer

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

train_df = pd.read_csv("data/train.csv", parse_dates=["Datetime"], dayfirst=True)
train_samples = train_df["ID"].values[1:]
train_signal = train_df["Count"].values[1:]
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
# print(answers)

# d)
# SignalAnalyzer.plot_frequency_magnitude("Magnitude of Signal", train_signal, train_sample_rate)

# e)
# try:
#     train_signal_norm = SignalAnalyzer.remove_continuous_component(train_signal)
#     name = "Signal Without Continous Component"
#
#     fig, ax = plt.subplots(1, figsize=(10, 5))
#     fig.suptitle(name)
#
#     plt.xlim([np.min(train_samples), np.max(train_samples)])
#
#     ax.plot(train_samples, train_signal_norm, linewidth=0.75)
#
#     plt.savefig(f"plots/{name}.pdf", format="pdf")
#     plt.savefig(f"plots/{name}.png", format="png")
#
#     plt.show()
#
# except ValueError as err:
#     print(err)

# f)
train_signal_norm = SignalAnalyzer.remove_continuous_component(train_signal)
top_k_frequencies = SignalAnalyzer.get_top_k_frequencies(train_signal_norm, train_sample_rate, 4)

frequency_in_year = np.multiply(top_k_frequencies, 3600 * 24 * 365)

answer_f = f"""
    The top 4 frequencies of the signal are: 
    \t{', '.join(f'{freq:.12f}' for freq in top_k_frequencies)}

    The represented frequencies by year are: 
    \t{', '.join(f'{freq:.2f}' for freq in frequency_in_year)}

    For each frequency:
        - 0.48   ≈ Every half a year
        - 0.96   ≈ Every year
        - 365.00 ≈ Every day 
        - 1.44   ≈ Every year and a half
"""

print(answer_f)

# g)

# number of days in a month
MONTH_SPAN = 28
# number of samples that represent one month of data
MONTH_SAMPLES_COUNT = 24 * MONTH_SPAN

sliced_df = train_df.iloc[1001:]
first_monday_index = sliced_df[sliced_df["Datetime"].dt.weekday == 0].index[0]

month_signal = train_df.loc[first_monday_index : first_monday_index + MONTH_SAMPLES_COUNT - 1, "Count"].values
month_samples = np.array([i + 1 for i in range(MONTH_SAMPLES_COUNT)])

# plot("Month Plot", month_samples, month_signal, xlim=[month_samples.min(), month_samples.max()], file_format="pdf")
# plot("Month Plot", month_samples, month_signal, xlim=[month_samples.min(), month_samples.max()], file_format="png")

# h)

# TODO: solve this
answer_h = """
"""

# i)
filter_amount = 0.95
filtered_signal = SignalAnalyzer.filter_signal(month_signal, filter_amount)

plot("Filtering of Signal", month_samples, month_signal, filtered_signal, file_format="pdf")
plot("Filtering of Signal", month_samples, month_signal, filtered_signal, file_format="png")
