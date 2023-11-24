import numpy as np

# un programator rezolva in medie 3 probleme intr o ora
# care este probabilitatea sa rezolve mai mult de 3 probleme intr o ora?
def ex3():
    N = 1_000_000
    n = 1_000_000
    _lambda = 3

    pois = np.random.binomial(n,_lambda/n,N)
    prob = np.mean(pois <= _lambda)

    print("Probabilitate nr de prob =",1 - prob)

ex3()

# durata medie de rezolvare a unei probleme de catre un 
# programator este de 30 de minute, care este probabilitatea
# ca el sa rezolve problema mai rapid?
def ex6():
    N = 1_000_000

    N = 1_000_000
    _lambda = 30

    exp = np.random.exponential(scale=_lambda,size=N)

    prob = np.mean(exp <= _lambda)

    print("Probabilitatea durata prob =",1-prob)

ex6()

def ex8():
    N = 1_000_000
    durataTramavai = 4
    durataAutobuz = 8

    expTramvai = np.random.exponential(scale=durataTramavai, size=N)
    expAutobuz = np.random.exponential(scale=durataAutobuz, size=N)

    probA = np.mean(expTramvai <= 5)
    print("a) =", 1-probA)

    probB = np.mean((expTramvai <= 5) | (expAutobuz <= 5))
    print("b) =", 1-probB)


ex8()