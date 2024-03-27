import io
from queue import PriorityQueue
import copy
import time

def bin_search(listaNoduri, nodNou, ls, ld):
    if len(listaNoduri)==0:
        return 0

    if ls==ld:
        if nodNou <= listaNoduri[ls]:
            return ls
        else:
            return ld + 1
    else:
        mij=(ls+ld)//2

        if nodNou <= listaNoduri[ls]:
            return bin_search(listaNoduri, nodNou, ls, mij)
        else:
            return bin_search(listaNoduri, nodNou, mij + 1, ld)

class NodArbore:
    def __init__(self, informatie, g = 0, h = 0, parinte=None):
        self.informatie = informatie
        self.parinte = parinte
        self.g = g
        self.h = h
        self.f = g + h

    def drumRadacina(self):
        nod = self
        l = []
        while nod:
            l.append(nod)
            nod = nod.parinte
        return l[::-1]

    def inDrum(self, infonod):
        nod = self
        while nod is not None:
            if nod.informatie == infonod:
                return True
            nod = nod.parinte
        return False

    def __eq__(self, other):
        return self.g == other.g and self.f == other.f

    def __le__(self, other):
        return self.f < other.f or (self.f == other.f and self.g >= other.g)

    def __lt__(self, other):
        return self.f < other.f or (self.f == other.f and self.g > other.g)

    def __str__(self):
        return f"({str(self.informatie)}, g:{self.g}, f:{self.f})"

    def __repr__(self):
        return "{} ({})".format(str(self.informatie), "->".join([str(x) for x in self.drumRadacina()]))

class Graf:
    def __init__(self, nod_start, lista_scopuri):
        self.nod_start = nod_start
        self.lista_scopuri = lista_scopuri

    def scop(self, informatieNod):
        return informatieNod in self.lista_scopuri

    def estimeaza_h(self, infoNod, euristica):
        if self.scop(infoNod):
            return 0

        if euristica == "banala":
            return 1

        if euristica == "euristica mutari":
            minH = float('inf')

            for scop in self.lista_scopuri:
                h = 0

                for iStiva, stiva in enumerate(scop):
                    for iBloc, bloc in enumerate(stiva):
                        try:
                            if infoNod[iStiva][iBloc] != bloc:
                                h += 1
                        except:
                            h += 1

                minH = min(minH, h)

            return minH

    def succesori(self, nod, euristica):
        lsuccesori = []
        gasit = False
        for lGol in range(3):
            for cGol in range(3):
                if nod.informatie[lGol][cGol] == 0:
                    gasit = True
                    break
            if gasit:
                break

        directii = [[-1, 0], [1, 0], [0, -1], [0, 1]]
        for directie in directii:
            lPlacuta = lGol + directie[0]
            cPlacuta = cGol + directie[1]

            if not (0 <= lPlacuta <= 2 and 0 <= cPlacuta <= 2):
                continue

            infoSuccesor = copy.deepcopy(nod.informatie)
            infoSuccesor[lGol][cGol], infoSuccesor[lPlacuta][cPlacuta] = infoSuccesor[lPlacuta][cPlacuta], infoSuccesor[lGol][cGol]

            if not nod.inDrum(infoSuccesor):
                lsuccesori.append(NodArbore(infoSuccesor, nod.g + 1, self.estimeaza_h(infoSuccesor, euristica), nod))

        return lsuccesori

    def valideaza(self):
        matriceDesfasurata = self.nod_start[0] + self.nod_start[1] + self.nod_start[2]

        inversiuni = 0
        for i in range(len(matriceDesfasurata)):
            for j in range(i+1, len(matriceDesfasurata)):
                if matriceDesfasurata[i] > matriceDesfasurata[j] != 0:
                    inversiuni += 1

        return inversiuni % 2 == 0

def aStarSolMultiple(graf, nsol, euristica):
    queue = [NodArbore(graf.nod_start)]
    output = open("output.txt", "w")

    while queue:
        nod_curent = queue.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent, euristica)
        queue += succesori
        queue.sort()

    output.close()

def aStarSolMultiplePQ(graf, nsol=1):
    queue = PriorityQueue()
    queue.put(NodArbore(graf.nod_start))

    while queue:
        nod_curent = queue.get()
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent)
        for it in succesori:
            queue.put(it)

def a_star(graf: Graf):
    if not graf.valideaza():
        print("Nu are solutii")
        return

    open = [NodArbore(graf.nod_start)]
    closed = []

    while open:
        nod_curent = open.pop(0)

        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            return

        succesori = graf.succesori(nod_curent, "euristica mutari")
        closed.append(nod_curent)

        for s in succesori:
            nod_nou = None
            if not nod_curent.inDrum(s.informatie):
                if s in open:
                    index_nod = open.index(s)

                    if s.f < open[index_nod].f or (s.f == open[index_nod].f and s.g > open[index_nod].g):
                        open.pop(index_nod)
                        # seteaza pt s parinte g si f
                        s.parinte = nod_curent
                        s.g += nod_curent.g
                        s.h = graf.estimeaza_h(s.informatie)
                        s.f = s.g + s.h
                        nod_nou = s
                if s in closed:
                    index_nod = closed.index(s)

                    if s.f < closed[index_nod].f or (s.f == closed[index_nod].f and s.g > closed[index_nod].g):
                        closed.pop(index_nod)
                        # seteaza pt s parinte g si f
                        s.parinte = nod_curent
                        s.g += nod_curent.g
                        s.h = graf.estimeaza_h(s.informatie)
                        s.f = s.g + s.h
                        nod_nou = s
                else:
                    nod_nou = s

                if nod_nou is not None:
                    open.append(nod_nou)
                    open.sort()

def aStarSolMultiple2(graf, nsol=1):
    queue = [NodArbore(graf.nod_start)]

    while queue:
        nod_curent = queue.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent)
        for it in succesori:
            index = bin_search(queue, it, 0, len(queue)-1)
            queue.insert(index, it)

        # queue += succesori
        # queue.sort()

def calculeazaStive(sir: str):
    return [x.strip().split() if x != "#" else [] for x in sir.strip().split("\n")]

def main():
    with open("input.txt", "r") as input:
        start = [[int(it) for it in line.split(' ')] for line in input.read().split('\n')]

    scopuri = [[
        [1,2,3],
        [4,5,6],
        [7,8,0]
    ]]
    graf = Graf(start, scopuri)
    print()

    a_star(graf)

main()