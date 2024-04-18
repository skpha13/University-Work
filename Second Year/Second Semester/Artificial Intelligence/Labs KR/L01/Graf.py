class NodArbore:
    def __init__(self, informatie, parinte=None):
        self.informatie = informatie
        self.parinte = parinte

    def drumRadacina(self):
        nod=self
        drum=[]
        while nod:
            drum.append(nod)
            nod=nod.parinte

        return drum[::-1]

    def inDrum(self, infonod):
        return any(node.informatie == infonod for node in self.drumRadacina())

    def __str__(self):
        return str(self.informatie)

    def __repr__(self):
        return "{} ({})".format(self.informatie, "->".join([str(x) for x in self.drumRadacina()]))

class Graf:
    def __init__(self, matrice_adiacenta, nod_start, lista_scopuri):
        self.matrice_adiacenta = matrice_adiacenta
        self.nod_start = nod_start
        self.lista_scopuri = lista_scopuri

    def scop(self, informatieNod):
        return informatieNod in self.lista_scopuri

    def succesori(self, nod):
        succesori = []
        for index in range(len(self.matrice_adiacenta)):
            if self.matrice_adiacenta[nod.informatie][index] == 1 and not nod.inDrum(index):
                succesori.append(NodArbore(index, nod))

        return succesori


a = NodArbore(1)
b = NodArbore(2, a)
c = NodArbore(3, b)

print(c.drumRadacina())
print(c.inDrum(2))
print(c.inDrum(5))
print(c.__str__())
print(repr(c))
print()

m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
]
start = 0
scopuri = [5, 9]

def breadthFirst(graf, nsol=1):
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

graf = Graf(m, start, scopuri)
depthFirstLinear(graf, NodArbore(0), 5)