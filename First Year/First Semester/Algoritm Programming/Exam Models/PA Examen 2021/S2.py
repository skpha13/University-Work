A = [int(x) for x in input("Gramada A: ").split()]
B = [int(x) for x in input("Gramada B: ").split()]

A.sort(reverse=True)
B.sort(reverse=True)

s = 0
for i in range(len(A)):
    if A[i] < 0:
        aux = i
        i = len(A) - 1
        j = len(B) - 1
        while i >= aux:
            s += A[i] * B[j]
            i -= 1
            j -= 1
        break
    s += A[i] * B[i]
        
print(s) 