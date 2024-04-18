from queue import PriorityQueue
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
        drum = [nod]
        while nod.parinte is not None:
            nod = nod.parinte
            drum = [nod] + drum
        return drum

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

    def __gt__(self, other):
        return self.f > other.f or (self.f == other.f  and self.g < other.g)

    def __str__(self):
        return f"({str(self.informatie)}, g:{self.g}, f:{self.f})"

    def __repr__(self):
        return "{} ({})".format(str(self.informatie), "->".join([str(x) for x in self.drumRadacina()]))

class Graf:
    def __init__(self, m, nod_start, lista_scopuri, h):
        self.matr = m
        self.nod_start = nod_start
        self.lista_scopuri = lista_scopuri
        self.h = h

    def scop(self, informatieNod):
        return informatieNod in self.lista_scopuri

    def estimeaza_h(self, infoNod):
        return self.h[infoNod]

    def succesori(self, nod):
        lSuccesori = []

        for infoSuccesor in range(len(self.matr)):
            if self.matr[nod.informatie][infoSuccesor] != 0 and not nod.inDrum(infoSuccesor):
                lSuccesori.append(NodArbore(infoSuccesor, nod.g + self.matr[nod.informatie][infoSuccesor], self.estimeaza_h(infoSuccesor), nod))

        return lSuccesori

def aStarSolMultiple(graf, nsol=1):
    queue = [NodArbore(graf.nod_start)]

    while queue:
        nod_curent = queue.pop(0)
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent)
        queue += succesori
        queue.sort()

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

def a_star(graf: Graf, nsol=1):
    open = [NodArbore(graf.nod_start)]
    closed = []

    while open:
        nod_curent = open.pop(0)

        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent)
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

with open("configuratie_graf.txt", "r") as input:
    m = [
        [0, 3, 5, 10, 0, 0, 100],
        [0, 0, 0, 4, 0, 0, 0],
        [0, 0, 0, 4, 9, 3, 0],
        [0, 3, 0, 0, 2, 0, 0],
        [0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 4, 0, 5],
        [0, 0, 3, 0, 0, 0, 0],
    ]
    h=[0,1,6,2,0,3,0]

    start = 0
    scopuri = [4,6]

    graf = Graf(m, start, scopuri, h)

    start_normal = time.perf_counter_ns()
    aStarSolMultiple(graf, 10)
    end_normal = time.perf_counter_ns()

    graf = Graf(m, start, scopuri, h)

    start_pq = time.perf_counter_ns()
    aStarSolMultiplePQ(graf, 10)
    end_pq = time.perf_counter_ns()

    graf = Graf(m, start, scopuri, h)
    print()

    aStarSolMultiple2(graf, 1)

    print(f"\nTime normal: {(end_normal - start_normal) / 1000} ms\nTime PQ: {(end_pq - start_pq) / 1000} ms")

"""
Pentru graful de mai sus si nsol = 1
    Time normal: 39.8 ms
    Time PQ: 58.8 ms
    
nsol = 10
    Time normal: 134.8 ms
    Time PQ: 162.2 ms
"""