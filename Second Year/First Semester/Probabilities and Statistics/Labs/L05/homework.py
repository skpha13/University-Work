import numpy as np

# A = se trage o carte din pachet si este inima neagra
# B = se trage o carte din pachet si este K
# C = se trage o carte din pachet si este K negru 

def ex4():
    N = 100_000_000
    A = np.random.uniform(0,1,N)
    B = np.random.randint(2,15,N)
    C = np.random.randint(1,57,N)

    p1 = np.mean(A < 0.25) 
    p2 = np.mean(B == 14)
    p3 = np.mean((C == 1) | (C == 2)) 

    print("Prob A =",p1)  
    print("Prob B =",p2)  
    print("Prob C =",p3)  

    p4 = np.mean((A < 0.25 ) & (B == 14))
    p5 = np.mean((A < 0.25 ) & ((C == 1) | (C == 2)))

    p6 = np.mean(((C == 1) | (C == 2)) & (B == 14))

    p7 = np.mean((A < 0.25 ) & ((C == 1) | (C == 2)) & (B == 14))

    print("Prob A|B =",p4,"| A*B = ",p1*p2)
    print("Prob A|C =",p5,"| A*C = ",p1*p3)

    print("Prob B|C =",p6,"| A*C = ",p2*p3)

    print("Prob A|B|C =",p7,"| A*C = ",p1*p2*p3)


# un jucator alege un numar intre 1 si 6 si o suma anume din banii lui, 
# se arunca un zar daca numarul de la zar e egal cu numarul ales de el
# atunci dubleaza suma de banii, altfel o pierde
def ex6():
    N = 10_000
    m = 20
    M = 40
    p = 0

    def game(m, M):
        N = 100_000
        sum = m/4

        choice = np.random.randint(1,7,N)
        number = np.random.randint(1,7,N)

        for index in range(len(choice)):
            if m == 0:
                return 0
            elif m == M:
                return 1

            if choice[index] == number[index]:
                m += sum
            else:
                m -= sum

        return 0
    
    for i in range(N):
        if game(m,M) == 1:
            p += 1

    print("Prob sa castige jocul:",p/N)

ex6()