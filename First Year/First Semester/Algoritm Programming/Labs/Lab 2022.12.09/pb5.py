def citire_date():
    with open("pb5_activitati.txt",'r') as f:
        n = int(f.readline().strip())
        l_activitati = [(i+1,) + tuple([int(x) for x in linie.split()]) for i,linie in enumerate(f)]
        return l_activitati

def greedy(l_activitati):
    l = sorted(l_activitati, key = lambda x: x[-1])

    t = 0
    h = max(0,t + l[0][1]-l[0][2])
    sol = [l[0] + (t,h)]
    t += l[0][1]

    for a in l[1:]:
        h = max(0,t + a[1]-a[2])
        sol.append(a + (t,h))
        t += a[1]

    h_max = max([a[-1] for a in sol])

    return sol,h_max

def afisare(l_activitati,h_max):
    with open("pb5_intarzieri.txt",'w') as g:
        sir = "Interval\tTermen\tIntarziere\n"
        g.write(sir)
        sir = "\n".join([f"{f'({a[3]}->{a[3]+a[1]})' : <10}\t{a[2] : ^6}\t{a[-1] : >10}"
            for a in l_activitati])
        sir += f"\nIntarziere maxima: {h_max}"
        g.write(sir)

activitati = citire_date()
rez = greedy(activitati)
afisare(*rez)