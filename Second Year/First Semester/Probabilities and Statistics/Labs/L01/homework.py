import numpy as np
import matplotlib.pyplot as plt

plt.figure()
plt.xlim([-1,1])
plt.ylim([-1,1])
plt.axis('equal')
plt.title('Puncte distribuite uniform intr-o elipsa')

def method1():
    #semi-major axis length
    a = 1
    #semi-minor axis length
    b = 0.5
    #center of elipse
    center = (0,0)

    N = 1000
    for i in range(N):
        x = np.random.uniform(-a,a)
        y = np.random.uniform(-b,b)

        if (x/a)**2 + (y/b)**2 <= 1:
            plt.plot(x,y,'.')

    plt.show()

def method2():
    a = 1
    b = 0.5
    N = 1000

    for i in range(N):
        theta = np.random.uniform(0,360)
        r = np.sqrt(np.random.rand())

        x = a/2 * r * np.cos(theta)
        y = b/2 * r * np.sin(theta)

        plt.plot(x,y,'.')

    plt.show()

method2()