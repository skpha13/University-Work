import io
import numpy as np

class Logging:
    def __init__(self, file_stream: io):
        self.out = file_stream

    def log_initial(self, string: str):
        self.out.write("Populatia initiala\n")
        self.out.write(string)
        self.out.write("\n")

    def log_dupa_selectie(self, string: str):
        self.out.write("Dupa selectie\n")
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
        self.file.log_initial(repr(self))
        # =====================================

    def __repr__(self):
        output = ""
        for (index, it) in enumerate(self.cromozomi):
            output += f"{index + 1}: {it[2]} x= {it[0]} f={it[1]}\n"
        return output

    def codificare(self):
        for number in self.cromozomi:
            index = int(np.floor((number[0] - self.a) / self.PAS_DISCRETIZARE))

            binary_string = bin(index)[2:]
            padded_binary_string = binary_string.zfill(self.LUNGIME_CROMOZOM)

            number[-1] = padded_binary_string

    def selectie(self):
        fitness_total = np.sum([sub_array[1] for sub_array in self.cromozomi])

        fitness_relativ = [cromozom[1]/fitness_total for cromozom in self.cromozomi]
        elitist = max(self.cromozomi, key=lambda sub_array : sub_array[1])
        probabilitati = np.cumsum(fitness_relativ)

        # ======= LOGGING PROBABILITATI SELECTIE =======
        self.file.log_probabilitati_selectie(fitness_relativ)
        # ==============================================

        # ======= LOGGING INTERVALE PROBABILITATI SELECTIE =======
        self.file.log_intervale_probabilitati(probabilitati)
        # ========================================================

        u_generati = np.random.random(self.numarCromozomi - 1)
        cromozomi_selectati = [self.cromozomi[np.searchsorted(probabilitati, u)] for u in u_generati]
        cromozomi_selectati.append(elitist)

        # ======= LOGGING CROMOZOMI SELECTATI =======
        self.file.log_cromozomi_selectati(probabilitati, u_generati)
        # ===========================================

        #  ======= LOGGING CROMOZOMI DUPA SELECTIE =======
        self.file.log_dupa_selectie(repr(self))
        # ================================================

        return cromozomi_selectati

    def incrucisare(self):
        def incrucisarePereche(binary1, binary2, index):
            return binary1[:index] + binary2[index:], binary2[:index] + binary1[index:]

        probabiliate_crossover = np.random.rand(self.numarCromozomi)
        participa_crossover = [cromozom for cromozom, prob in zip(self.cromozomi, probabiliate_crossover) if prob < self.probabilitateCrossover]
        nu_participa_crossover = [cromozom for cromozom, prob in zip(self.cromozomi, probabiliate_crossover) if prob >= self.probabilitateCrossover]

    #   TODO: do crossover in array and then union the result with the non-participating chromosomes

    def mutatie(self):
        pass

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
    alg.codificare()
    alg.selectie()
    pass

if __name__ == "__main__":
    main()