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

            maxx = max(a1[4],a2[4],a3[4],a4[4])
            if maxx == a1[4]:
                return a1
            if maxx == a2[4]:
                return a2
            if maxx == a3[4]:
                return a3
            if maxx == a4[4]:
                return a4
            break
    else:
        lungime = x_dr - x_st
        latime = y_sus - y_jos
        arie = lungime * latime
        return x_st,y_jos,x_dr,y_sus,arie

def afisare(rez):
    with open("pb3_dreptunghi.out",'w') as g:
        g.write("Coordonate dreptunghi:\n")
        g.write(f"({rez[0]}, {rez[1]})\n({rez[2]}, {rez[3]})\n\n")
        g.write(f"Arie maxima: {rez[4]}")

dreptunghi,copaci = citire()
sol = divide(dreptunghi[0][0],dreptunghi[0][1],dreptunghi[1][0],dreptunghi[1][1],copaci)
afisare(sol)