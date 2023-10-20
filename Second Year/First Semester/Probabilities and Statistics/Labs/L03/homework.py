import numpy as np
import matplotlib.pyplot as plt

plt.figure()
plt.axis("equal")

def generareGrid(nr,dist):
    ax = plt.gca()
    ax.set_xlim(-1, nr)
    x_ticks = np.arange(-1, nr, dist)
    ax.set_xticks(x_ticks, minor=False)
    ax.grid(which='major', axis='x', linestyle='-', linewidth='0.5', color='gray')

def stick(lungime,nr):
    global n
    global gap
    x1 = np.random.uniform(0,nr)
    y1 = np.random.uniform(0,nr)

    unghi = np.random.uniform(0 , 2 * np.pi)

    x2 = x1 + lungime * np.cos(unghi)
    y2 = y1 + lungime * np.sin(unghi)

    for i in range(0,nr+1,gap):
        if (x1 < i < x2) or (x1 > i > x2):
            n = n + 1
            break

    plt.plot([x1, x2], [y1, y2], marker='o')


N = 10000
nr = 10
gap = 1
lungimeBat = 1
n = 0

generareGrid(nr+1, gap)

for i in range(N):
    stick(lungimeBat, nr)

print(2*N*lungimeBat/(n*gap))

plt.show()

# Am lucrat impreuna cu Mihai Dogaru