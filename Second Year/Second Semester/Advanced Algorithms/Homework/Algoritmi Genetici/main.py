import io
import time

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation


class Logging:
    LOGGING_ENABLED = True
    SHOW_TITLE = True
    def __init__(self, file_stream: io):
        self.out = file_stream

    def log(self, function, *args):
        if self.LOGGING_ENABLED == True:
            function(*args)

    def log_maximum(self, maximum, average):
        if self.SHOW_TITLE == True:
            self.out.write(f"Evolutia maximului\n")
            self.SHOW_TITLE = False

        self.out.write(f"Maximum:{maximum}\t\tmedia:{average}\n")

    def log_initial(self, string: str):
        self.out.write("Populatia initiala\n")
        self.out.write(string)
        self.out.write("\n")

    def log_dupa_selectie(self, string: str):
        self.out.write("Dupa selectie\n")
        self.out.write(string)
        self.out.write("\n")

    def log_dupa_recombinare(self, string: str):
        self.out.write("\nDupa recombinare\n")
        self.out.write(string)
        self.out.write("\n")

    def log_dupa_mutatie(self, string: str):
        self.out.write("\nDupa mutatie\n")
        self.out.write(string)
        self.out.write("\n")

    def log_probabilitati_selectie(self, fitness_relativ):
        self.out.write("Probabilitati Selectie\n")
        for (index, it) in enumerate(fitness_relativ):
            self.out.write(f"cromozom {index + 1} probabilitate {it}\n")
        self.out.write("\n")

    def log_intervale_probabilitati(self, probabilitati):
        self.out.write("Intervale probabilitati Selectie\n")
        for (index, it) in enumerate(probabilitati):
            self.out.write(f"{it} ")
        self.out.write("\n")

    def log_cromozomi_selectati(self, probabilitati, u_generati):
        for it in u_generati:
            self.out.write(f"u={it} selectam cromozomul {np.searchsorted(probabilitati, it) + 1}\n")
        self.out.write("\n")

    def log_crossover_selectie(self, cromozomi, probabilitati_crossover, probabilitate):
        self.out.write(f"Probabilitatea de incrucisare {probabilitate}\n")
        for (index, it) in enumerate(cromozomi):
            self.out.write(f"{index + 1}: {it[2]} u={probabilitati_crossover[index]}")

            if probabilitati_crossover[index] < probabilitate:
                self.out.write(f"<{probabilitate} participa")

            self.out.write("\n")
        self.out.write("\n")

    def log_recombinare(self, selected_indices, element1, element2, result1, result2, index):
        self.out.write(f"Recombinare dintre cromozomul {selected_indices[0]} cu cromozomul {selected_indices[1]}\n")
        self.out.write(f"{element1[2]} {element2[2]} punct {index}\n")
        self.out.write(f"Rezultat:\t{result1} {result2}\n")

    def log_mutatie_selectie(self, indices, probabilitate):
        self.out.write(f"Probabilitate de mutatie pentru fiecare gena {probabilitate}\nAu fost modificati cromozomii:\n")
        for it in indices:
            self.out.write(f"{it + 1}\n")

class Algoritm:
    LUNGIME_CROMOZOM = 0
    PAS_DISCRETIZARE = 0
    OUTPUT_FILE = open("output.txt", "w")
    file = Logging(OUTPUT_FILE)

    def __init__(self, numarCromozomi, a, b, coeficienti, p,
                probabilitateCrossover, probabilitateMutatie, numarEtape):
        self.numarCromozomi = numarCromozomi
        self.a = a
        self.b = b
        self.f = lambda x : coeficienti[0] * (x ** 2) + coeficienti[1] * x + coeficienti[2]
        self.p = p
        self.probabilitateCrossover = probabilitateCrossover
        self.probabilitateMutatie = probabilitateMutatie
        self.numarEtape = numarEtape

        self.cromozomi = [[x, self.f(x), ""] for x in np.random.uniform(self.a, self.b, numarCromozomi)]

        # ======= LOGGING IN OUPUT FILE =======
        self.file.log(self.file.log_initial, repr(self))
        # self.file.log_initial(repr(self))
        # =====================================

    def __repr__(self):
        output = ""
        for (index, it) in enumerate(self.cromozomi):
            output += f"{index + 1}: {it[2]} x= {it[0]} f={it[1]}\n"
        return output

    def getMaximum(self):
        return max(self.cromozomi, key=lambda x: x[1])[1]

    def getMaximumCoordinates(self):
        max_cromozom = max(self.cromozomi, key=lambda x: x[1])
        return max_cromozom[0], max_cromozom[1]

    def getAverage(self):
        return np.mean([x[1] for x in self.cromozomi])

    def getAverageCoordinates(self):
        mean_value = np.mean([x[1] for x in self.cromozomi])
        valueList = [0 for _ in range(len(self.cromozomi))]

        for (index, it) in enumerate(self.cromozomi):
            valueList[index] = abs(it[1] - mean_value)

        lowest_cromozom = self.cromozomi[np.argmin(valueList)]
        return lowest_cromozom[0], lowest_cromozom[1]

    def codificare(self):
        for number in self.cromozomi:
            index = int(np.floor((number[0] - self.a) / self.PAS_DISCRETIZARE))

            binary_string = bin(index)[2:]
            padded_binary_string = binary_string.zfill(self.LUNGIME_CROMOZOM)

            number[-1] = padded_binary_string

    def decodificare(self):
        for index in range(len(self.cromozomi)):
            function_index = int(self.cromozomi[index][2], 2)
            self.cromozomi[index][0] = self.a + function_index * self.PAS_DISCRETIZARE
            self.cromozomi[index][1] = self.f(self.cromozomi[index][0])

    def selectie(self):
        fitness_total = np.sum([sub_array[1] for sub_array in self.cromozomi])

        fitness_relativ = [cromozom[1]/fitness_total for cromozom in self.cromozomi]
        elitist = max(self.cromozomi, key=lambda sub_array : sub_array[1])
        probabilitati = np.cumsum(fitness_relativ)

        # ======= LOGGING PROBABILITATI SELECTIE =======
        self.file.log(self.file.log_probabilitati_selectie, fitness_relativ)
        # self.file.log_probabilitati_selectie(fitness_relativ)
        # ==============================================

        # ======= LOGGING INTERVALE PROBABILITATI SELECTIE =======
        self.file.log(self.file.log_intervale_probabilitati, probabilitati)
        # self.file.log_intervale_probabilitati(probabilitati)
        # ========================================================

        u_generati = np.random.random(self.numarCromozomi - 1)
        cromozomi_selectati = [self.cromozomi[np.searchsorted(probabilitati, u)] for u in u_generati]
        cromozomi_selectati.append(elitist)

        # ======= LOGGING CROMOZOMI SELECTATI =======
        self.file.log(self.file.log_cromozomi_selectati, probabilitati, u_generati)
        # self.file.log_cromozomi_selectati(probabilitati, u_generati)
        # ===========================================

        self.cromozomi = cromozomi_selectati
        #  ======= LOGGING CROMOZOMI DUPA SELECTIE =======
        self.file.log(self.file.log_dupa_selectie, repr(self))
        # self.file.log_dupa_selectie(repr(self))
        # ================================================

    def incrucisare(self):
        def incrucisarePereche(binary1, binary2, index):
            return binary1[:index] + binary2[index:], binary2[:index] + binary1[index:]

        probabiliate_crossover = np.random.rand(self.numarCromozomi)
        participa_crossover = [cromozom for cromozom, prob in zip(self.cromozomi, probabiliate_crossover) if prob < self.probabilitateCrossover]
        nu_participa_crossover = [cromozom for cromozom, prob in zip(self.cromozomi, probabiliate_crossover) if prob >= self.probabilitateCrossover]

        # ======= LOGGING PROBABILITATE INCRUCISARE =======
        self.file.log(self.file.log_crossover_selectie, self.cromozomi, probabiliate_crossover, self.probabilitateCrossover)
        # self.file.log_crossover_selectie(self.cromozomi, probabiliate_crossover, self.probabilitateCrossover)
        # =================================================

        while len(participa_crossover) >= 2:
            selected_indices = np.random.choice(len(participa_crossover), size=2, replace=False)
            element1, element2 = participa_crossover[selected_indices[0]], participa_crossover[selected_indices[1]]

            # toList in converteste toate elementele la str
            participa_crossover = np.delete(participa_crossover, selected_indices, 0).tolist()
            # fac conversia in float pentru x si f(x)
            for index in range(len(participa_crossover)):
                participa_crossover[index][0] = float(participa_crossover[index][0])
                participa_crossover[index][1] = float(participa_crossover[index][1])

            punct_rupere = np.random.randint(0, self.LUNGIME_CROMOZOM)
            result1, result2 = incrucisarePereche(element1[2], element2[2], punct_rupere)

            # ======= LOGGING RECOMBINARE INCRUCISARE =======
            self.file.log(self.file.log_recombinare, selected_indices, element1, element2, result1, result2, punct_rupere)
            # self.file.log_recombinare(selected_indices, element1, element2, result1, result2, punct_rupere)
            # ===============================================

            element1[2] = result1
            element2[2] = result2
            nu_participa_crossover.append(element1)
            nu_participa_crossover.append(element2)
        else:
            if len(participa_crossover) == 1:
                nu_participa_crossover.append(participa_crossover[0])

        self.cromozomi = nu_participa_crossover
        # ======= LOGGING DUPA RECOMBINARE =======
        self.file.log(self.file.log_dupa_recombinare, repr(self))
        # self.file.log_dupa_recombinare(repr(self))
        # =====================================

    def mutatie(self):
        probabiliate_mutatie = np.random.rand(self.numarCromozomi)
        participa_mutatie_index = [index for index, prob in enumerate(probabiliate_mutatie) if prob < self.probabilitateCrossover]

        for index in participa_mutatie_index:
            pozitie_bit = np.random.randint(0, self.LUNGIME_CROMOZOM)
            bit_string = list(self.cromozomi[index][2])

            if bit_string[pozitie_bit] == '0':
                bit_string[pozitie_bit] = '1'
            else:
                bit_string[pozitie_bit] = '0'

            new_string = ''.join(bit_string)
            self.cromozomi[index][2] = new_string

        # ======= LOGGING DUPA RECOMBINARE =======
        self.file.log(self.file.log_mutatie_selectie, participa_mutatie_index, self.probabilitateMutatie)
        # self.file.log_mutatie_selectie(participa_mutatie_index, self.probabilitateMutatie)
        # =====================================

        # ======= LOGGING DUPA RECOMBINARE =======
        self.file.log(self.file.log_dupa_mutatie, repr(self))
        # self.file.log_dupa_mutatie(repr(self))
        # =====================================

class Animation:
    a = 0
    b = 0
    f = None
    maximum = (0, 0)
    average = (0, 0)

    def __init__(self, a, b, f):
        self.a = a
        self.b = b
        self.f = f

        self.x_values = np.linspace(self.a, self.b, 1000)
        self.y_values = self.f(self.x_values)

        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim(self.a, self.b)
        self.ax.set_ylim(min(self.y_values), max(self.y_values) + 0.1)

        self.line, = self.ax.plot(self.x_values, self.y_values, lw=2, color='b', label='Function')

        self.max_point, = self.ax.plot([], [], 'ro', markersize=8, label='Maximum')
        self.avg_point, = self.ax.plot([], [], 'go', markersize=8, label='Average')

        self.ax.legend()

    def update(self, frame):
        self.max_point.set_data([], [])
        self.avg_point.set_data([], [])

        self.max_point.set_data(*zip(*self.maximum[:frame+1]))
        self.avg_point.set_data(*zip(*self.average[:frame+1]))

        return self.max_point, self.avg_point


def citireDate():
    with open("input.txt", "r") as file:
        n = int(file.readline().strip())
        a, b = [float(x) for x in file.readline().strip().split(' ')]
        coef = [int(x) for x in file.readline().strip().split(' ')]
        p = float(file.readline().strip())
        pCross = float(file.readline().strip())
        pMutatie = float(file.readline().strip())
        nrEtape = int(file.readline().strip())

        Algoritm.LUNGIME_CROMOZOM = int(np.ceil(np.log2((b-a) * np.power(10, p))))
        Algoritm.PAS_DISCRETIZARE = (b-a)/(2 ** Algoritm.LUNGIME_CROMOZOM)

        alg = Algoritm(n, a, b, coef, p, pCross, pMutatie, nrEtape)

    return alg

def main():
    alg = citireDate()
    anim = Animation(alg.a, alg.b, alg.f)

    max_points = []
    avg_points = []

    for _ in range(alg.numarEtape):
        alg.codificare()
        alg.selectie()
        alg.incrucisare()
        alg.mutatie()

        alg.file.LOGGING_ENABLED = False
        alg.decodificare()

        max_points.append(alg.getMaximumCoordinates())
        avg_points.append(alg.getAverageCoordinates())

        alg.file.log_maximum(alg.getMaximum(), alg.getAverage())

    anim.maximum = max_points
    anim.average = avg_points
    temp = FuncAnimation(plt.gcf(), anim.update, len(max_points), interval=100, blit=True)
    plt.show()


if __name__ == "__main__":
    main()