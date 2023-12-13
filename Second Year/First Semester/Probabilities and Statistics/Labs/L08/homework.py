import numpy as np
import matplotlib.pyplot as plt

def ex4():
    n = 1_000
    N = 100
    p = 0.5
    
    pasi = np.random.rand(n)
    values = np.where(pasi <= p, 1, -1)
    cumulativeSum = np.cumsum(values)
    
    nPoz = np.random.rand(n)
    valueNPoz = np.where(pasi <= p, 1, -1)
    
        # subpunctul a
    # plt.figure()
    # plt.plot(np.arange(1, n+1), cumulativeSum)
    # plt.xlabel('Index')
    # plt.ylabel('Cumulative sum of values')
    # plt.grid(True)
    # plt.show()
    
        # subpunctul b
    plt.hist(valueNPoz, bins=100, density=True, color='blue' )
    
        # subpunctul c
    E = np.mean(values)
    patrat = np.square(values)
    niu = E
    sigma = np.sqrt(np.mean(patrat) - E**2)
    f = lambda x: 1/(np.sqrt(2*np.pi*sigma)) * np.exp((-(x-(n * niu))**2)/(2*n*sigma))
    x = np.linspace(-1, 1, N)
    y = f(x)
    plt.plot(x, y, color = 'black', label = 'f(x)')
    plt.show()
    
    
# ex4()


def ex5():
    n = 1_000
    N = 100
    
    pasi = np.random.rand(n)
    values = np.zeros(n)
    values[pasi < 0.25] = -1
    values[(pasi >= 0.25) & (pasi < 0.75)] = 0
    values[pasi >= 0.75] = 1
    cumulativeSum = np.cumsum(values)
    
    nPoz = np.random.rand(N)
    valuesNPoz = np.zeros(N)
    valuesNPoz[nPoz < 0.25] = -1
    valuesNPoz[(nPoz >= 0.25) & (nPoz < 0.75)] = 0
    valuesNPoz[nPoz >= 0.75] = 1
        
        # subpunctul a 
    # plt.figure()
    # plt.plot(np.arange(1, n+1), cumulativeSum)
    # plt.xlabel('Index')
    # plt.ylabel('Cumulative sum of values')
    # plt.grid(True)
    # plt.show()
    
        # subpunctul b
    plt.hist(valuesNPoz, bins = 100, density = True, color='red')

        # subpunctul c
    E = np.mean(values)
    patrat = np.square(values)
    niu = E
    sigma = np.sqrt(np.mean(patrat) - E**2)
    f = lambda x: 1/(np.sqrt(2*np.pi*sigma)) * np.exp((-(x-(n * niu))**2)/(2*n*sigma))
    x = np.linspace(-1, 1, N)
    y = f(x)
    plt.plot(x, y, color = 'black', label = 'f(x)')
    plt.show()

    
ex5()