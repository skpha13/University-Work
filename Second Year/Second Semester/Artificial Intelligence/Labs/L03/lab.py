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

# Optimized BFS
def breadthFirstOpt(graf, nsol=1):
    queue = [NodArbore(graf.nod_start)]

    while queue:
        nod_curent = queue.pop(0)

        succesori = graf.succesori(nod_curent)

        for succesor in succesori:
            queue.append(succesor)

            if graf.scop(succesor.informatie):
                print(repr(succesor))
                nsol -= 1

                if nsol == 0:
                    return

# Recursive DFS
def depthFirst(graf, node, nsol=1):
    if graf.scop(node.informatie):
        print(repr(node))
        nsol -= 1
        return nsol

    succesori = graf.succesori(node)

    for succ in succesori:
        if nsol > 0:
            nsol = depthFirst(graf, succ, nsol)

    return nsol

# Linear DFS
def depthFirstLinear(graf, start_node, nsol=1):
    stack = [start_node]

    while stack and nsol > 0:
        current_node = stack.pop()

        if graf.scop(current_node.informatie):
            print(repr(current_node))
            nsol -= 1
        else:
            successors = graf.succesori(current_node)
            stack.extend(successors)

    return nsol

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

    aStarSolMultiple(graf, 1)