from queue import PriorityQueue
import time

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

    start_pq = time.perf_counter_ns()
    aStarSolMultiplePQ(graf, 10)
    end_pq = time.perf_counter_ns()

    print(f"\nTime normal: {(end_normal - start_normal) / 1000} ms\nTime PQ: {(end_pq - start_pq) / 1000} ms")

"""
Pentru graful de mai sus si nsol = 1
    Time normal: 39.8 ms
    Time PQ: 58.8 ms
    
nsol = 10
    Time normal: 134.8 ms
    Time PQ: 162.2 ms
"""