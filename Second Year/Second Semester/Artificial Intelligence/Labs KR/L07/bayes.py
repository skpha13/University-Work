import copy


class Nod:
    def __init__(self, identificator, probabl=None,parinti=[], fii=[], tabel=[]):
        self.identificator=identificator
        self.parinti=parinti
        self.fii=[]
        self.tabel=tabel
        self.probabl=probabl

    def __str__(self):
        sir= f"{self.identificator}"
        if self.probabl is not None:
            sir+=f" prob: {self.probabl}"
        return sir
    
    def __repr__(self):
        sirTabel='\n'.join([str(linie) for linie in self.tabel])
        sir=f"Identificator: {self.identificator}\n"
        if self.probabl is not None:
            sir+=f"Probabilitate: {self.probabl}\n"
        sir+=f"Fii: {', '.join(self.fii)}\n"+ \
            f"Parinti: {', '.join(self.parinti)}\n"+ \
            f"Tabel probabilitati conditionate:\n{sirTabel}\n"
        

        return sir


class Retea:
    def __init__(self, fisier):
        self.graf={}

        f=open(fisier, "r")
        continut=f.read()
        textNoduri, auxInterog=continut.split("observatii:")
        textNoduri=textNoduri.strip()
        texteNoduri=textNoduri.split("nod:")
        for text in texteNoduri:
            if not text:
                continue
            liniiNod=text.strip().split("\n")
            identif=liniiNod[0].strip()
            probabilitate=None
            parinti=[]
            tabelProb=[]
            try:
                probabilitate=float(liniiNod[1])
            except:
                #nu am probabilitate data ci tabel de parinti
                parinti=liniiNod[1].split(", ")
                for linie in liniiNod[2:]:
                    linie=linie.strip().split()
                    linie=list(map(lambda x: True if x=="1" else False, linie[:-1]))+[float(linie[-1])]
                    tabelProb.append(linie)
            nodRetea=Nod(identificator=identif, probabl=probabilitate, parinti=parinti,tabel=tabelProb)
            self.graf[identif]=nodRetea
        textObservatii, varInterogare=auxInterog.strip().split("interogare:")
        textObservatii=textObservatii.strip()
        
        listaObservatii=[] if textObservatii=="#" else textObservatii.split("; ")
        self.observatii=[]
        for textObs in listaObservatii:
            identif, val=textObs.strip().split(":")
            identif=identif.strip()
            self.observatii+=[identif]
            self.graf[identif].valoare=float(val)            
            self.graf[identif].probabl=1 if val=='1' else 0
        for k,nd in self.graf.items():
            for pr in nd.parinti:
                self.graf[pr].fii.append(k) 
        self.interogare=varInterogare.strip()

    def dovezi(self,x):
        """
        verific daca toti parintii lui x sunt cunoscuti
        """
        ok=True
        for p in x.parinti:
            p=self.graf[p]
            if not p.probabl:
                ok=False
        return ok

    def interogare_retea(self,x):
        return self.suport_except(self.graf[x], None)

    def suport_except(self,x, v):
        alpha=1
        #if self.dovezi(x):
        if x.probabl:
            #returnez doar probabilitatea pentru valoare True (fiinca false se calculeaza cu 1-probabl)
            return x.probabl 
        else:
            prob_e=self.dovezi_except(x,v)
            if not x.parinti:
                return alpha*prob_e*x.probabl
            else:
                l_prob=[]
                for p in x.parinti:
                    p_true=self.suport_except(self.graf[p], x)
                    l_prob.append(p_true)

                sumProb=0
                for linie in x.tabel:
                    prodProb=linie[-1]
                    for i,valAdev in enumerate(linie[:-1]):
                        prodProb*=l_prob[i] if valAdev else (1-l_prob[i])
                    sumProb+=prodProb
                
                return alpha*prob_e*sumProb

    def dovezi_except(self, x,v):
        y=list(x.fii)
        if v:
            y.remove(v.identificator)
        if not y:
            #return 0.5 #variabila booleana
            return 1
        prod_prob=1
        for yi in y:
            yi=self.graf[yi]
            proabl_yi=self.dovezi_except(yi, None)
            zi=list(yi.parinti)
            zi_sters=zi.index(x.identificator)
            zi.remove(x.identificator)
            tabel_yi=copy.deepcopy(yi.tabel)
            for linie in tabel_yi:
                linie.pop(zi_sters)
            l_probz=[]
            
            for zij in zi:
                l_probz.append(self.suport_except(self.graf[zij], yi))
            sum_zi_true=0
            sum_zi_false=0
            for linie in tabel_yi:
                prodProb=1                
                for j,valAdev in enumerate(linie[:-1]):
                    prodProb*=l_probz[j] if valAdev else (1-l_probz[j])
                sum_zi_true+=prodProb*linie[-1]
                sum_zi_false+=prodProb*(1-linie[-1])
            sum_yi=proabl_yi*sum_zi_true+(1-proabl_yi)*sum_zi_false
            prod_prob*=sum_yi
        return prod_prob



    def __str__(self):
        sir="Noduri: \n"
        for nod in self.graf.values():
            sir+="NOD:"+repr(nod)+"-------------\n"
        sir+="Observatii: "+", ".join([str(self.graf[x]) for x in self.observatii])+"\n"
        sir+="Interogare: "+self.interogare
        return sir


r=Retea("input1.txt")
rez=r.interogare_retea(r.interogare)
rez_fals=1-rez
#print(str(r))
print(f"Pentru {r.interogare} probabilitatea să fie:\n" + \
       f"- True este {rez}\n" + \
       f"- False este {rez_fals}")
                
                
                














            
        
