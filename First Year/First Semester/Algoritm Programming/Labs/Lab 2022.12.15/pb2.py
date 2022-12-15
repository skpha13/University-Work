k = 1
def divide(m,l_sus,c_st,latura):
    global k
    if latura == 1:
        m[l_sus][c_st] = k
        k += 1
        return 
    latura //= 2
    divide(m,l_sus,c_st + latura,latura)
    divide(m,l_sus + latura,c_st,latura)
    divide(m,l_sus,c_st,latura)
    divide(m,l_sus + latura,c_st + latura, latura)

n = int(input("numar: "))
m = [[0]*(2**n) for i in range (2**n)]
    
divide(m,0,0,2**n)

for line in m:
    print(*line)