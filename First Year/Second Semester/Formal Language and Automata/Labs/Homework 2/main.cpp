#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

//global variable for menu
char NumeFisier[50];
// array for bkt
char x[25];
// bool variable to see if word is accepted or not
bool stareVerif = 0;
// to see number of results
int contor = 0;

struct Drum{
    int urmatorul;
    char litera;
};

class Graf{
private:
    int NrNod,NrMuchii,NrStariFinale,StareInitiala;
    vector<int> StariFinale;
    set<char> Litere;
    vector<vector<Drum>> Matrice;

public:
    //getters
    int getNrNod();
    int getNrMuchii();
    int getNrStariFinale();
    int getStareInitiala() const;
    const vector<int> &getStariFinale();
    const vector<vector<Drum>> &getMatrice();

    //setter
    void setValues(char numeFisier[]);

    //methods
    void afiseazaInfo() const;
    void verificaCuvantNFA(char cuvant[],vector<int> path,int i,int stare) const;
    void verif(char cuvant[],int n,int i,int stare,bool &drum) const;
    void verifAcceptat(char cuvant[],int n,int i,int stare,bool &stop) const;
    bool valid(int k) const;
    void bkt(int lungime,int k) const;
    void afisareCuvant(int n) const;
    void verificaLambda(char cuvant[],int i,int stare,bool &ok) const;
};

int Graf::getStareInitiala() const {
    return StareInitiala;
}

int Graf::getNrMuchii() {
    return NrMuchii;
}

int Graf::getNrNod() {
    return NrNod;
}

int Graf::getNrStariFinale() {
    return NrStariFinale;
}

const vector<int> &Graf::getStariFinale() {
    return StariFinale;
}

const vector<vector<Drum>> &Graf::getMatrice() {
    return Matrice;
}

void Graf::setValues(char numeFisier[]) {
    ifstream f(numeFisier);
    int nod_curent,nod_tranzitie,stare_finala;
    char valoare;
    Drum d;
    f>>NrNod>>NrMuchii>>NrStariFinale>>StareInitiala;

    for(int j=0;j<NrNod;j++)
    {
        vector<Drum> linie;
        Matrice.push_back(linie);
    }

    for(int i=0;i<NrMuchii;i++)
    {
        f>>nod_curent>>nod_tranzitie>>valoare;
        if(valoare != '^') Litere.insert(valoare);
        d.urmatorul = nod_tranzitie;
        d.litera = valoare;
        Matrice[nod_curent].push_back(d);
    }

    for(int i=0;i<NrStariFinale;i++)
    {
        f>>stare_finala;
        StariFinale.push_back(stare_finala);
    }
    f.close();
}

void Graf::afiseazaInfo() const {
    cout<<"Numar stari: "<<NrNod<<endl;
    cout<<"Numar tranzitii: "<<NrMuchii<<endl;
    cout<<"Stare initiala: "<<StareInitiala<<endl;
    cout<<"Numar stari finale: "<<NrStariFinale<<endl;

    cout<<"Tranzitii:"<<endl;
    for(int i=0;i<NrNod;i++) {
        cout<<"\t";
        cout<<"Starea: q"<<i;
        for (int j=0;j<Matrice[i].size();j++)
        {
            cout<<" are tranzitie cu: q"<< Matrice[i][j].urmatorul<< ", daca litera == " << Matrice[i][j].litera<<" ";
            cout<<"\t";
        }
        cout<<endl;
    }

    cout<<"Stari finale: ";
    for(int i=0;i<NrStariFinale;i++)
        cout<<StariFinale[i]<<" ";
    cout<<endl;
}

void Graf::afisareCuvant(int n) const {
    cout<<"\t";
    for(int i=0;i<=n;i++)
        cout<<x[i];
    cout<<endl;
}

void Graf::verifAcceptat(char cuvant[],int n,int i,int stare,bool &stop) const {
    for(int j=0;j<Matrice[stare].size();j++)
        if(Matrice[stare][j].litera == cuvant[i] && Matrice[stare][j].litera != '^')
            verifAcceptat(cuvant,n,i+1,Matrice[stare][j].urmatorul,stop);
        else if(Matrice[stare][j].litera == '^')
            verifAcceptat(cuvant,n,i,Matrice[stare][j].urmatorul,stop);
    if(i == n + 1)
        for(int j=0;j<StariFinale.size();j++)
            if(stare == StariFinale[j])
                stop = true;
}

void Graf::verif(char cuvant[],int n,int i,int stare,bool &drum) const {
    if(i == n + 1)
        drum = true;
    else
        for(int j=0;j<Matrice[stare].size();j++)
            if(Matrice[stare][j].litera == cuvant[i] && Matrice[stare][j].litera != '^')
                verif(cuvant,n,i+1,Matrice[stare][j].urmatorul,drum);
            else if(Matrice[stare][j].litera == '^')
                verif(cuvant,n,i,Matrice[stare][j].urmatorul,drum);
}

bool Graf::valid(int k) const {
    bool drum = false;
    verif(x,k,0,StareInitiala,drum);
    return drum;
}

void Graf::bkt(int lungime,int k) const {
    for(auto index:Litere)
    {
        x[k] = index;
        // verfica doar daca legaturile sunt corecte nu si daca e acceptat
        if(valid(k))
        {
            bool stop = false;
            verifAcceptat(x,k,0,StareInitiala,stop);
            if(k+1 < lungime)
            {
                // verifica daca cunvatul este acceptat
                if(stop == true)
                    afisareCuvant(k),contor++;
                bkt(lungime,k+1);
            }
            else if (k+1 == lungime && stop == true)
                afisareCuvant(k),contor++;
        }
    }
}

void Graf::verificaCuvantNFA(char cuvant[],vector<int> path,int i,int stare) const {
    for(int j=0;j<Matrice[stare].size();j++)
    {
        if(Matrice[stare][j].litera == cuvant[i])
        {
            path.push_back(stare);
            verificaCuvantNFA(cuvant,path,i+1,Matrice[stare][j].urmatorul);
            path.pop_back();
        }
        else if(Matrice[stare][j].litera == '^')
        {
            path.push_back(stare);
            verificaCuvantNFA(cuvant,path,i,Matrice[stare][j].urmatorul);
            path.pop_back();
        }
    }
    if(i == strlen(cuvant))
    {
        for(int j=0;j<StariFinale.size();j++)
            if(stare == StariFinale[j])
            {
                path.push_back(stare);
                cout<<"Accepta ";
                stareVerif = true;

                cout<<endl<<"Drum: ";
                for(int k=0;k<path.size();k++)
                    cout<<"q"<<path[k]<<" ";
                cout<<endl;
            }
    }
}

void Graf::verificaLambda(char *cuvant, int i, int stare,bool &ok) const {
        for(int j=0;j<Matrice[stare].size();j++)
            if(Matrice[stare][j].litera == cuvant[i])
                verificaLambda(cuvant,i+1,Matrice[stare][j].urmatorul,ok);
            else if(Matrice[stare][j].litera == '^')
                verificaLambda(cuvant,i,Matrice[stare][j].urmatorul,ok);
        if(i == strlen(cuvant))
            for(int j=0;j<StariFinale.size();j++)
                if(stare == StariFinale[j])
                    ok = true;
}


class Meniu{
private:
    static bool TipCitire;

public:
    //getters & setters
    bool getTipCitire();
    void setTipCitire(bool TipCitire);

    const char* const getNumeFisier();
    void setNumeFisier(char* NumeFisier);

    //methods
    void afisareMeniu(int lungimeBreak = 20);
    const void prelucrareOptiune(const Graf &obj);
    void selectareModCitire(const Graf &obj,int opt = 0);
    void verificaCuvant(const Graf &obj);
};

//initializare tip citire
bool Meniu::TipCitire = 0;

bool Meniu::getTipCitire() {
    return this->TipCitire;
}

void Meniu::setTipCitire(bool TipCitire) {
    this->TipCitire = TipCitire;
}

void Meniu::afisareMeniu(int lungimeBreak) {
    for(int i=0;i<lungimeBreak/2;i++) cout<<"-";
    cout<<" MENIU ";
    for(int i=lungimeBreak/2;i<lungimeBreak;i++) cout<<"-";

    cout<<endl<<endl;
    cout<<"1. Afisare informatii graf"<<endl;
    cout<<"2. Selectare mod citire"<<endl;
    cout<<"3. Verifica cuvant"<<endl;
    cout<<"4. Apasati 4 pentru ajutor"<<endl;
    cout<<"5. Vezi toate cuvintele acceptate"<<endl;
    cout<<"0. Iesiti din program"<<endl;

    // +7 pt lungimea cuvaantului meniu
    cout<<endl;
    for(int i=0;i<lungimeBreak + 7;i++) cout<<"-";
    cout<<endl;
}

const void Meniu::prelucrareOptiune(const Graf &obj) {
    int nrCitit;

    while(true)
    {
        cout<<endl<<"Optiune:";
        cin>>nrCitit;
        cin.get();

        switch (nrCitit) {
            case 0:
                exit(0);

            case 1:
            {
                system("CLS");
                obj.afiseazaInfo();
                Meniu::afisareMeniu();
                break;
            }

            case 2:
            {
                system("CLS");
                Meniu::selectareModCitire(obj);
                Meniu::afisareMeniu();
                break;
            }

            case 3:
            {
                system("CLS");
                Meniu::verificaCuvant(obj);
                Meniu::afisareMeniu();
                break;
            }

            case 4:
            {
                cout<<endl<<"\t"<<"Tastati un numar(cu optiunea pe care o doriti) si apasati enter"<<endl;
                break;
            }

            case 5:
            {
                system("CLS");
                int nr = 0;
                cout<<"\tIntrodu lungimea cuvantului: "<<endl;
                cin>>nr;
                cin.get();
                cout<<"Cuvinte acceptate de lungime "<<nr<<" : "<<endl;
                bool temp = false;
                obj.verificaLambda("",0,obj.getStareInitiala(),temp);
                contor = 0;
                if(temp) cout<<"\t^\n",contor++;
                obj.bkt(nr,0);
                cout<<endl<<"In total "<<contor<<" cuvinte\n";
                Meniu::afisareMeniu();
                break;
            }

            default:
            {
                cout<<endl<<"\t"<<"Selectati o optiune valida"<<endl;
            }
        }
    }

}

void Meniu::selectareModCitire(const Graf &obj,int tipCitire) {
    cout<<endl<<"\t"<<"Va rog selectati modul de citire al cuvintelor: "<<endl;
    cout<<"\t 1. De la tastatura"<<endl;
    cout<<"\t 2. Din fisier"<<endl;
    cout<<endl<<"Optiune:";
    cin>>tipCitire;
    cin.get();
    if(tipCitire == 1 || tipCitire == 2) Meniu::setTipCitire(tipCitire - 1);
    else return;

    if(Meniu::getTipCitire() == 1)
    {
        char cuvant[256];
        vector <int> path;
        cout<<"\t"<<"Introduceti numele fisierului:";
        cin.getline(NumeFisier,49);
        ifstream a(NumeFisier);

        while (a >> cuvant)
        {
            a.get();
            cout<<endl;
            cout<<cuvant<<": ";
            obj.verificaCuvantNFA(cuvant,path,0,obj.getStareInitiala());
            cout<<endl;
        }
        cout<<endl;
        a.close();
    }
}

void Meniu::verificaCuvant(const Graf &obj) {
    if(Meniu::getTipCitire() == 0)
    {
        vector<int> path;
        char cuvant[256];
        cout<<endl;
        cout<<"Introduceti cuvant:";
        cin.getline(cuvant,255);

        obj.verificaCuvantNFA(cuvant,path,0,obj.getStareInitiala());
        if(stareVerif == 0) cout<<"Nu accepta\n";
        else stareVerif = 0;

        cout<<endl<<endl;
    }
    Meniu::afisareMeniu();
    Meniu::prelucrareOptiune(obj);
}

char* fisier()
{
    char* nume;
    nume = new char[50];
    cout<<"Va rog introduceti numele fisierului care contine graful:";
    cin.getline(nume,255);

    return nume;
}

int main() {
    Graf g;
    g.setValues(fisier());

    Meniu menu;
    menu.afisareMeniu();

    menu.prelucrareOptiune(g);
    return 0;
}