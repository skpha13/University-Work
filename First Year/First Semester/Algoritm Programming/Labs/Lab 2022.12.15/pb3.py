def citire():
    with open("pb3_copaci.in") as f:
        temp = f.readline()
        x = [int(i) for i in temp.split()]
        temp = f.readline()
        y = [int(i) for i in temp.split()]
        l = [(int(line.strip().split()[0]),int(line.strip().split()[1])) for line in f.readlines()]
        return (x,y),l

def divide(x_st,y_jos,x_dr,y_sus,l_copaci):
    for c in copaci:
        if c[0] > x_st and c[0] < x_dr and c[1] > y_jos and c[1] < y_sus:
           a1 = divide(x_st,c[1],x_dr,y_sus,l_copaci)
           a2 = divide(x_st,y_jos,x_dr,c[1],l_copaci)

           a3 = divide(x_st,y_jos,c[0],y_sus,l_copaci)
           a4 = divide(c[0],y_jos,x_dr,y_sus,l_copaci)
        break
    else:
        lungime = x_dr - x_st
        latime = y_sus - y_jos
        arie = lungime * latime
        return x_st,y_jos,x_dr,y_sus,arie

dreptunghi,copaci = citire()
print(divide(dreptunghi[0][0],dreptunghi[0][1],dreptunghi[1][0],dreptunghi[1][1],copaci))