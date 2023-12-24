from pydataset import data
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

def ex2():
    AirPassengers = data('AirPassengers')
    print(AirPassengers)

    time = AirPassengers['time']
    number = AirPassengers['AirPassengers']

    covariance = np.cov(time, number)[0,1]
    correlation = np.corrcoef(time, number)[0,1]

    print("\nCovariance:", covariance)
    print("Correlation:", correlation, end="\n\n")

    slope, intercept, r, _ , _ = linregress(time, number)

    print(f'Slope: {slope}')
    print(f'Intercept: {intercept}')
    print(f'R Value: {r**2}')
    print()

    plt.scatter(time, number, label='Date reale')
    plt.plot(time, slope * time + intercept, color='red', label='Regresie liniara')
    plt.xlabel('Time')
    plt.ylabel('Number of passengers')
    plt.show()

    time80, time20 = np.split(time, [int(0.8 * len(time))])
    number80, number20 = np.split(number, [int(0.8 * len(number))])

    # time = weight
    # numer = height
    slope_pred, intercept_pred, _, _, _ = linregress(time80, number80)
    number_pred = slope_pred * time20 + intercept_pred

    print("\nValori reale vs. Predicția regresiei liniare:")
    comparison = np.column_stack((number20, number_pred))
    print(comparison)


ex2()