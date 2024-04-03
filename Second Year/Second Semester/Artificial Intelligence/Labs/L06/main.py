import time

import pygame, sys, copy, math

ADANCIME_MAX=6

def elem_identice(lista):
    return lista[0] * (lista[0] != InfoJoc.GOL and all(elem == lista[0] for elem in lista[1:]))


class InfoJoc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    NR_COLOANE=3
    JMIN=None
    JMAX=None
    GOL='#'

    @classmethod
    def initializeaza(cls, display, NR_COLOANE=3, dim_celula=100):
        cls.display=display
        cls.dim_celula=dim_celula
        cls.x_img = pygame.image.load('ics.png')
        cls.x_img = pygame.transform.scale(cls.x_img, (dim_celula, math.floor(dim_celula*cls.x_img.get_height()/cls.x_img.get_width())))
        cls.zero_img = pygame.image.load('zero.png')
        cls.zero_img = pygame.transform.scale(cls.zero_img, (dim_celula,math.floor(dim_celula*cls.zero_img.get_height()/cls.zero_img.get_width())))
        cls.celuleGrid=[] #este lista cu patratelele din grid
        for linie in range(NR_COLOANE):
            cls.celuleGrid.append([])
            for coloana in range(NR_COLOANE):
                patr = pygame.Rect(coloana*(dim_celula+1), linie*(dim_celula+1), dim_celula, dim_celula)
                cls.celuleGrid[linie].append(patr)



    def deseneaza_grid(self, marcaj=None): # tabla de exemplu este ["#","x","#","0",......]

        for linie in range(InfoJoc.NR_COLOANE):
            for coloana in range(InfoJoc.NR_COLOANE):
                if marcaj==(linie,coloana):
                    #daca am o patratica selectata, o desenez cu rosu
                    culoare=(255,0,0)
                else:
                    #altfel o desenez cu alb
                    culoare=(255,255,255)
                pygame.draw.rect(self.__class__.display, culoare, self.__class__.celuleGrid[linie][coloana]) #alb = (255,255,255)
                if self.matr[linie][coloana]=='x':
                    self.__class__.display.blit(self.__class__.x_img,(coloana*(self.__class__.dim_celula+1),linie*(self.__class__.dim_celula+1)+ (self.__class__.dim_celula-self.__class__.x_img.get_height())//2))
                elif self.matr[linie][coloana]=='0':
                    self.__class__.display.blit(self.__class__.zero_img,(coloana*(self.__class__.dim_celula+1),linie*(self.__class__.dim_celula+1)+(self.__class__.dim_celula-self.__class__.zero_img.get_height())//2))
        #pygame.display.flip() # !!! obligatoriu pentru a actualiza interfata (desenul)
        pygame.display.update()



    def __init__(self, tabla=None):
        if tabla:
            self.matr = tabla
        else:
            self.matr = [[InfoJoc.GOL] * InfoJoc.NR_COLOANE for _ in range(InfoJoc.NR_COLOANE)]


    @classmethod
    def jucator_opus(cls, jucator):
        return 'x' if jucator == '0' else '0'


    def final(self):
        rez = elem_identice(self.matr[0]) \
              or elem_identice(self.matr[1]) \
              or elem_identice(self.matr[2]) \
              or elem_identice([self.matr[0][0], self.matr[1][0], self.matr[2][0]]) \
              or elem_identice([self.matr[0][1], self.matr[1][1], self.matr[2][1]]) \
              or elem_identice([self.matr[0][2], self.matr[1][2], self.matr[2][2]]) \
              or elem_identice([self.matr[0][0], self.matr[1][1], self.matr[2][2]]) \
              or elem_identice([self.matr[0][2], self.matr[1][1], self.matr[2][0]])
        if rez:
            return rez
        remiza = True
        for linie in self.matr:
            for elem in linie:
                if elem == InfoJoc.GOL:
                    remiza = False
        if remiza:
            return "remiza"
        return False


    def mutari(self, jucator):#jucator = simbolul jucatorului care muta
        lMutari = []
        for linie in range(InfoJoc.NR_COLOANE):
            for coloana in range(InfoJoc.NR_COLOANE):
                if self.matr[linie][coloana] == InfoJoc.GOL:
                    infoSuccesor = copy.deepcopy(self.matr)
                    infoSuccesor[linie][coloana] = jucator
                    lMutari.append(InfoJoc(infoSuccesor))

        return lMutari


    #linie deschisa inseamna linie pe care jucatorul mai poate forma o configuratie castigatoare
    #practic e o linie care nu conține simbolul jucatorului opus
    def linie_deschisa(self, lista, jucator):
        return not InfoJoc.jucator_opus(jucator) in lista


    def linii_deschise(self, jucator):
        return self.linie_deschisa(self.matr[0], jucator) \
            + self.linie_deschisa(self.matr[1], jucator) \
            + self.linie_deschisa(self.matr[2], jucator) \
            + self.linie_deschisa([self.matr[0][0], self.matr[1][0], self.matr[2][0]], jucator) \
            + self.linie_deschisa([self.matr[0][1], self.matr[1][1], self.matr[2][1]], jucator) \
            + self.linie_deschisa([self.matr[0][2], self.matr[1][2], self.matr[2][2]], jucator) \
            + self.linie_deschisa([self.matr[0][0], self.matr[1][1], self.matr[2][2]], jucator) \
            + self.linie_deschisa([self.matr[0][2], self.matr[1][1], self.matr[2][0]], jucator)


    #restAdancime = cat mai are pana ajunge la adancimea maxima
    def estimeaza_scor(self, restAdancime):
        rez = self.final()
        if rez == "remiza":
            return 0

        if rez == InfoJoc.JMAX:
            return 100 + restAdancime

        if rez == InfoJoc.JMIN:
            return -100 - restAdancime

        return self.linii_deschise(InfoJoc.JMAX) - self.linii_deschise(InfoJoc.JMIN)

    def sirAfisare(self):
        sir="  |"
        sir+=" ".join([str(i) for i in range(self.NR_COLOANE)])+"\n"
        sir+="-"*(self.NR_COLOANE+1)*2+"\n"
        for i in range(self.NR_COLOANE): #itereaza prin linii
                sir+= str(i)+" |"+" ".join([str(x) for x in self.matr[i]])+"\n"
        return sir

    def __str__(self):
        return self.sirAfisare()

    def __repr__(self):
        return self.sirAfisare()



class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
    Functioneaza cu conditia ca in cadrul clasei InfoJoc sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa InfoJoc sa fie definita si o metoda numita mutari() care ofera lista cu configuratiile posibile in urma mutarii unui jucator
    """
    def __init__(self, tabla_joc, j_curent, adancime, parinte=None, estimare=None):
        self.tabla_joc=tabla_joc
        self.j_curent=j_curent

        #adancimea in arborele de stari
        self.adancime=adancime

        #estimarea favorabilitatii starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.estimare=estimare

        #lista de mutari posibile din starea curenta
        self.mutari_posibile=[]

        #cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
        self.stare_aleasa=None


    def mutari(self):
        l_mutari=self.tabla_joc.mutari(self.j_curent)
        juc_opus=InfoJoc.jucator_opus(self.j_curent)
        l_stari_mutari=[Stare(mutare, juc_opus, self.adancime-1, parinte=self) for mutare in l_mutari]

        return l_stari_mutari


    def __str__(self):
        sir= str(self.tabla_joc) + "(Juc curent:"+self.j_curent+")\n"
        return sir



""" Algoritmul MinMax """

def min_max(stare):
    if stare.tabla_joc.final() or stare.adancime == 0:
        stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    stare.mutari_posibile = [min_max(mutare) for mutare in stare.mutari()]

    if stare.j_curent == InfoJoc.JMIN:
        stare.stare_aleasa = min(stare.mutari_posibile, key=lambda x: x.estimare)
    else:
        stare.stare_aleasa = max(stare.mutari_posibile, key=lambda x: x.estimare)

    stare.estimare = stare.stare_aleasa.estimare

    return stare


def alpha_beta(alpha, beta, stare):
    if stare.tabla_joc.final() or  stare.adancime == 0:
        stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime)
        return stare

    stare.mutari_posibile = stare.mutari()
    if stare.j_curent == InfoJoc.JMIN:
        stare.estimare = float('inf')
        for mutare in stare.mutari_posibile:
            mutareCuSubarbore =  alpha_beta(alpha, beta, mutare)
            if mutareCuSubarbore.estimare < stare.estimare:
                stare.estimare = mutareCuSubarbore.estimare
                stare.stare_aleasa = mutareCuSubarbore
            if beta > mutareCuSubarbore.estimare:
                beta = mutareCuSubarbore.estimare
                if alpha >= beta:
                    return stare
    else:
        stare.estimare = -float('inf')
        for mutare in stare.mutari_posibile:
            mutareCuSubarbore = alpha_beta(alpha, beta, mutare)
            if mutareCuSubarbore.estimare > stare.estimare:
                stare.estimare = mutareCuSubarbore.estimare
                stare.stare_aleasa = mutareCuSubarbore
            if alpha < mutareCuSubarbore.estimare:
                alpha = mutareCuSubarbore.estimare
                if alpha >= beta:
                    return stare
        stare.stare_aleasa = max(stare.mutari_posibile, key=lambda x: x.estimare)

    stare.estimare = stare.stare_aleasa.estimare

    return stare




def afis_daca_final(stare_curenta):
    final=stare_curenta.tabla_joc.final()
    if(final):
        if (final=="remiza"):
            print("Remiza!")
        else:
            print("A castigat "+final)

        return True

    return False



def main():
    #initializare algoritm
    raspuns_valid=False
    while not raspuns_valid:
        tip_algoritm=input("Algorimul folosit? (raspundeti cu 1 sau 2)\n 1.Minimax\n 2.Alpha-beta\n ")
        if tip_algoritm in ['1','2']:
            raspuns_valid=True
        else:
            print("Nu ati ales o varianta corecta.")
    #initializare jucatori
    raspuns_valid=False
    while not raspuns_valid:
        InfoJoc.JMIN=input("Doriti sa jucati cu x sau cu 0? ").lower()
        if (InfoJoc.JMIN in ['x', '0']):
            raspuns_valid=True
        else:
            print("Raspunsul trebuie sa fie x sau 0.")
    InfoJoc.JMAX= '0' if InfoJoc.JMIN == 'x' else 'x'


    #initializare tabla
    tabla_curenta=InfoJoc();
    print("Tabla initiala")
    print(str(tabla_curenta))

    #creare stare initiala
    stare_curenta=Stare(tabla_curenta,'x',ADANCIME_MAX)

    #setari interf grafica
    pygame.init()
    pygame.display.set_caption('x si 0')
    #dimensiunea ferestrei in pixeli
    #dim_celula=..
    ecran=pygame.display.set_mode(size=(302,302))# N *100+ (N-1)*dimensiune_linie_despartitoare (dimensiune_linie_despartitoare=1)
    InfoJoc.initializeaza(ecran)


    de_mutat=False
    tabla_curenta.deseneaza_grid()
    while True :

        if (stare_curenta.j_curent==InfoJoc.JMIN):
        #muta jucatorul
            #[MOUSEBUTTONDOWN, MOUSEMOTION,....]
            #l=pygame.event.get()
            for event in pygame.event.get():
                if event.type== pygame.QUIT:
                    pygame.quit() #inchide fereastra
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN: #click

                    pos = pygame.mouse.get_pos()#coordonatele clickului

                    for linie in range(InfoJoc.NR_COLOANE):
                        for coloana in range(InfoJoc.NR_COLOANE):

                            if InfoJoc.celuleGrid[linie][coloana].collidepoint(pos):#verifica daca punctul cu coord pos se afla in dreptunghi(celula)
                                ###############################

                                if stare_curenta.tabla_joc.matr[linie][coloana] == InfoJoc.JMIN:
                                    if (de_mutat and linie==de_mutat[0] and coloana==de_mutat[1]):
                                        #daca am facut click chiar pe patratica selectata, o deselectez
                                        de_mutat=False
                                        stare_curenta.tabla_joc.deseneaza_grid()
                                    else:
                                        de_mutat=(linie, coloana)
                                        #desenez gridul cu patratelul marcat
                                        stare_curenta.tabla_joc.deseneaza_grid(de_mutat)
                                elif stare_curenta.tabla_joc.matr[linie][coloana] == InfoJoc.GOL:
                                    if de_mutat:
                                        #### eventuale teste legate de mutarea simbolului
                                        stare_curenta.tabla_joc.matr[de_mutat[0]][de_mutat[1]]=InfoJoc.GOL
                                        de_mutat=False
                                    #plasez simbolul pe "tabla de joc"
                                    stare_curenta.tabla_joc.matr[linie][coloana]=InfoJoc.JMIN
                                    stare_curenta.tabla_joc.deseneaza_grid()
                                    #afisarea starii jocului in urma mutarii utilizatorului
                                    print("\nTabla dupa mutarea jucatorului")
                                    print(str(stare_curenta))


                                    #testez daca jocul a ajuns intr-o stare finala
                                    #si afisez un mesaj corespunzator in caz ca da
                                    if (afis_daca_final(stare_curenta)):
                                        break


                                    #S-a realizat o mutare. Schimb jucatorul cu cel opus
                                    stare_curenta.j_curent=InfoJoc.jucator_opus(stare_curenta.j_curent)


        #--------------------------------
        else: #jucatorul e JMAX (calculatorul)
            #Mutare calculator

            #preiau timpul in milisecunde de dinainte de mutare
            t_inainte=int(round(time.time() * 1000))
            if tip_algoritm=='1':
                stare_actualizata=min_max(stare_curenta)
            else: #tip_algoritm==2
                stare_actualizata=alpha_beta(-500, 500, stare_curenta)
            stare_curenta.tabla_joc=stare_actualizata.stare_aleasa.tabla_joc
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))

            stare_curenta.tabla_joc.deseneaza_grid()
            #preiau timpul in milisecunde de dupa mutare
            t_dupa=int(round(time.time() * 1000))
            print("Calculatorul a \"gandit\" timp de "+str(t_dupa-t_inainte)+" milisecunde.")

            if (afis_daca_final(stare_curenta)):
                break

            #S-a realizat o mutare. Schimb jucatorul cu cel opus
            stare_curenta.j_curent=InfoJoc.jucator_opus(stare_curenta.j_curent)


if __name__ == "__main__" :
    main()
    while True :
        for event in pygame.event.get():
            if event.type== pygame.QUIT:
                pygame.quit()
                sys.exit()
