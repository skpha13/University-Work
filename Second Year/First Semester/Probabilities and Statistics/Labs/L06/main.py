import numpy as np
import matplotlib.pyplot as plt

def ex1():
    def c():
        N = 1_000_000
        n = 6
        p = 0.5
        
        zar = np.random.binomial(n,p,N)
        zar_patrat = np.square(zar)

        medie = np.sum(zar)/N
        medie_patrat = np.sum(zar_patrat)/N

        print("Media normala a zarurilor =",medie)
        print("Media cu elementele la patrat =", medie_patrat)
        print("Media la patrat =",np.square(medie))
        print("Variatia =", medie_patrat - np.square(medie))
        print("n * p =",n*p)

        plt.hist(zar, bins=100, density=True)
        plt.show()

    def b():
        n = 1_000
        p = 0.5

        X = np.random.binomial(1,p,n)
        
        print(X)

        plt.hist(X, bins=100, density=True)
        plt.show()

    c()

def ex2():
    N = 1_000_000
    n = 500
    p = 0.03
    k = 10

    X = np.random.binomial(n,p,N)
    prob = np.mean(X < k)

    print("Probabilitate =",1 - prob)


ex2()