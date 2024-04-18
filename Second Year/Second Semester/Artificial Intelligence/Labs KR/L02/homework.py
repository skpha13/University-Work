class NodArbore:
    def __init__(self, informatie, parinte=None):
        self.informatie = informatie
        self.parinte = parinte

    def drumRadacina(self):
        nod = self
        drum = []
        while nod:
            drum.append(nod)
            nod = nod.parinte

        return drum[::-1]

    def inDrum(self, infonod):
        nod = self
        while nod:
            if nod.informatie == infonod:
                return True
            nod = nod.parinte
        return False

    def __str__(self):
        return str(self.informatie)

    def __repr__(self):
        return "{} ({})".format(self.informatie, "->".join([str(x) for x in self.drumRadacina()]))

    def afisSolFisier(self, file, output):
        output = output[11:-1].split("->")
        optiuni = [
            ("(Stanga: <barca>)", "<Dreapta>"),
            ("(Stanga)", "(Dreapta: <barca>)")
        ]
        counter_optiuni = 0
        file_string = ""
        output.append("(0, 0, 0)")

        n = 0
        for i in range(len(output) - 1):
            pozitie_barca = optiuni[counter_optiuni % 2]
            numbers = output[i].replace('(', ' ').replace(')', ' ').replace(',', ' ').split(' ')
            next_numbers = output[i + 1].replace('(', ' ').replace(')', ' ').replace(',', ' ').split(' ')

            misionari = int(numbers[1])
            canibali = int(numbers[3])
            misionari_nou = int(next_numbers[1])
            canibali_nou = int(next_numbers[3])

            if i == 0:
                n = misionari
            misionari_right = n - misionari
            canibali_right = n - canibali

            file_string += f"{pozitie_barca[0]} {canibali} canibali {misionari} misionari ...... {pozitie_barca[1]} {canibali_right} canibali {misionari_right} misionari\n"
            if counter_optiuni % 2 == 0 and i != len(output) - 2:
                file_string += f"\n>>> Barca s-a deplasat de la malul stang la malul drept cu {canibali - canibali_nou} canibali si {misionari - misionari_nou} misionari.\n"
            elif counter_optiuni % 2 == 1 and i != len(output) - 2:
                file_string += f"\n>>> Barca s-a deplasat de la malul drept la malul stang cu {canibali_nou - canibali} canibali si {misionari_nou - misionari} misionari.\n"

            counter_optiuni += 1

        file.writelines(file_string)


class Graf:
    def __init__(self, nod_start, lista_scopuri):
        self.nod_start = nod_start
        self.lista_scopuri = lista_scopuri

    def scop(self, informatieNod):
        return informatieNod in self.lista_scopuri

    def succesori(self, nod):
        lSuccesori = []

        def testConditie(m, c):
            return m == 0 or m >= c

        if nod.informatie[2] == 1:
            misMalCurent = nod.informatie[0]
            canMalCurent = nod.informatie[1]
            misMalOpus = Graf.N - nod.informatie[0]
            canMalOpus = Graf.N - nod.informatie[1]
        else:
            misMalOpus = nod.informatie[0]
            canMalOpus = nod.informatie[1]
            misMalCurent = Graf.N - nod.informatie[0]
            canMalCurent = Graf.N - nod.informatie[1]

        minMisBarca = 1
        maxMisBarca = min(misMalCurent, Graf.M)

        for mb in range(minMisBarca, maxMisBarca + 1):
            if mb == 0:
                minCanBarca = 1
                maxCanBarca = min(canMalCurent, Graf.M)
            else:
                minCanBarca = 0
                maxCanBarca = min(canMalCurent, mb, Graf.M - mb)

            for cb in range(minCanBarca, maxCanBarca + 1):
                misMalCurentNou = misMalCurent - mb
                canMalCurentNou = canMalCurent - cb
                misMalOpusNou = misMalOpus + mb
                canMalOpusNou = canMalOpus + cb

                misBarca = abs(misMalCurentNou - misMalCurent)
                canBarca = abs(canMalCurentNou - canMalCurent)

                if canBarca > misBarca:
                    continue

                if (not testConditie(misMalCurentNou, canMalCurentNou)) and nod.informatie[2] == 0:
                    continue

                if (not testConditie(misMalOpusNou, canMalOpusNou)) and (nod.informatie[2] + 1) % 2 == 0:
                    continue

                if nod.informatie[2] == 1:
                    infoNodSuccesor = (misMalCurentNou, canMalCurentNou, 0)
                else:
                    infoNodSuccesor = (misMalOpusNou, canMalOpusNou, 1)

                if not nod.inDrum(infoNodSuccesor):
                    lSuccesori.append(NodArbore(infoNodSuccesor, nod))

        return lSuccesori


def breadthFirst(graf, nsol=1):
    file = open("output.txt", "a")
    file.truncate(0)
    queue = [NodArbore(graf.nod_start)]

    while queue:
        nod_curent = queue.pop(0)
        if graf.scop(nod_curent.informatie):
            nod_curent.afisSolFisier(file, repr(nod_curent))
            file.write("--------------------------------------------------------------------------------------\n\n\n")
            print(repr(nod_curent))
            nsol -= 1

            if nsol == 0:
                return

        succesori = graf.succesori(nod_curent)
        queue += succesori

    file.close()


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


# graf = Graf(m, start, scopuri)
# depthFirstLinear(graf, NodArbore(0), 5)

with open("configuratie_graf.txt", "r") as input:
    string = input.read().strip().split(" ")
    n = int(string[0])
    m = int(string[1])

    Graf.N = n
    Graf.M = m

    start = (Graf.N, 0, 1)
    scopuri = [(0, Graf.N, 0)]

    graf = Graf(start, scopuri)

    breadthFirst(graf, 2)
