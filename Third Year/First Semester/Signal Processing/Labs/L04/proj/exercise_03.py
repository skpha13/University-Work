import os

from exercise_02 import SamplingFrequencyAnalysis

dir_path = f"{os.getcwd()}/plots"
if not os.path.exists(dir_path):
    os.makedirs(dir_path)

obj = SamplingFrequencyAnalysis(ns=33)
obj.plot("Over-Nyquist Frequency")
