def citire_date():
    with open("pb11_lungimi.txt") as f:
        l = [(int(line.strip().split()[1]),f"L{i+1}") for i,line in enumerate(f.readlines())]
        return l

def greedy(lungimi):
    k = len(lungimi)
    deplasari = []
    with open("pb11_interclasari.txt",'w') as g:
        n = len(lungimi)
        for i in range(n):
            lungimi.sort(key = lambda x: x[0])
            g.write(f"Pas: {i+1}\n")
            g.write("Structura contine: ")
            for l in lungimi:
                g.write(str(l))
            g.write(".\n")
            if len(lungimi) > 1:
                aux = lungimi[0][0] + lungimi[1][0]
                g.write(f"Din vectorii {str(lungimi[0])} si {str(lungimi[1])} rezulta ({aux},L{k+1}).\n\n")
                deplasari.append(aux)
                lungimi.pop(0)
                lungimi.pop(0)
                lungimi.append((aux,f"L{k+1}"))
                k += 1
        numere = [str(x) for x in deplasari]
        sir = " + ".join(numere)
        aux = sum(deplasari)
        g.write(f"\nNumar total deplasari: {sir} = {aux}")

greedy(citire_date())