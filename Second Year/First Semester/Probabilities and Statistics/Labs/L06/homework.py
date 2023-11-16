import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import binom
from scipy.stats import geom

# avem o moneda corecta, care este probabilitatea sa obtinem k heads 
# intr-o serie de n aruncari ?
def ex3():
    n = 5
    p = 0.5

    k = 3
    prob = binom.pmf(k,n,p)
    print(f"Probabilitatea de a obtine {k} heads in {n} aruncari este: {prob}")

ex3()

# mai multi copii trag numere pentru a vedea in ce echipa ajung
# care e probabilitatea ca un copil sa pice in echipa pe care si-o doreste
# din primele k trageri ?
def ex6():
    N = 100_000
    p = 0.3
    k = 10

    numar = np.ceil(np.log(np.random.rand())/ np.log(1-p))

    U = np.random.rand(N)
    X = np.ceil(np.log(U)/ np.log(1-p)).astype(int)

    aparitii_numar = np.count_nonzero(X[:k] == numar)
    prob = aparitii_numar / k

    print(f"Probabilitatea este: {prob}")

ex6()