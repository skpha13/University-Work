#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

//global variable for menu
char NumeFisier[50];

struct Drum{
    int urmatorul;
    char litera;
};

class Graf{
private:
    int NrNod,NrMuchii,NrStariFinale;
    vector<int> StariFinale;
    vector<vector<Drum>> Matrice;

public:
    //getters
    int getNrNod();
    int getNrMuchii();
    int getNrStariFinale();
    const vector<int> &getStariFinale();
    const vector<vector<Drum>> &getMatrice();

    //setter
    void setValues(char numeFisier[]);

    //methods
    void afiseazaInfo() const;
    void verificaCuvant(char cuvant[]) const;
    void verificaCuvantNFA(char cuvant[],vector<int> path,int i,int stare) const;
};

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

    f>>NrNod>>NrMuchii>>NrStariFinale;

    for(int j=0;j<NrNod;j++)
    {
        vector<Drum> linie;
        Matrice.push_back(linie);
    }

    for(int i=0;i<NrMuchii;i++)
    {
        f>>nod_curent>>nod_tranzitie>>valoare;
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

void Graf::verificaCuvant(char cuvant[]) const {
    int stare = 0;
    vector<int> path;
    path.push_back(0);
    for(int i=0;i<strlen(cuvant);i++)
    {
        int ok = 0;
        for(int j=0;j<Matrice[stare].size();j++)
            if(Matrice[stare][j].litera == cuvant[i])
            {
                stare = Matrice[stare][j].urmatorul;
                path.push_back(stare);
                ok = 1;
                break;
            }
        if(ok == 0)
        {
            cout<<"Nu accepta";
            return;
        }
    }
    int stareVerif = 0;
    for(int i=0;i<StariFinale.size();i++)
        if(stare == StariFinale[i])
        {
            cout<<"Accepta";
            stareVerif = 1;
        }
    if(stareVerif == 1)
    {
        cout<<endl<<"Drum: ";
        for(int i=0;i<path.size();i++)
            cout<<"q"<<path[i]<<" ";
    }
    else cout<<"Nu accepta";
}

bool stareVerif = 0;
void Graf::verificaCuvantNFA(char cuvant[],vector<int> path,int i,int stare) const {
    for(int j=0;j<Matrice[stare].size();j++)
    {
        if(Matrice[stare][j].litera == cuvant[i])
        {
            path.push_back(stare);
            verificaCuvantNFA(cuvant,path,i+1,Matrice[stare][j].urmatorul);
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
                stareVerif = 1;

                cout<<endl<<"Drum: ";
                for(int k=0;k<path.size();k++)
                    cout<<"q"<<path[k]<<" ";
                cout<<endl;
            }
    }
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
    cout<<"5. Iesiti din program"<<endl;

    // +7 pt lungimea cuvaantului meniu
    cout<<endl;
    for(int i=0;i<lungimeBreak + 7;i++) cout<<"-";
    cout<<endl;
}

const void Meniu::prelucrareOptiune(const Graf &obj) {
    int nrCitit;

    cout<<endl<<"Optiune:";
    cin>>nrCitit;
    cin.get();

    switch (nrCitit) {
        case 1:
            obj.afiseazaInfo();
            Meniu::afisareMeniu();
            Meniu::prelucrareOptiune(obj);
            break;

        case 2:
            Meniu::selectareModCitire(obj);
            Meniu::afisareMeniu();
            Meniu::prelucrareOptiune(obj);
            break;

        case 3:
            Meniu::verificaCuvant(obj);
            Meniu::afisareMeniu();
            Meniu::prelucrareOptiune(obj);
            break;

        case 4:
            cout<<endl<<"\t"<<"Tastati un numar(cu optiunea pe care o doriti) si apasati enter"<<endl;
            Meniu::prelucrareOptiune(obj);
            break;

        case 5:
            exit(0);

        default:
            cout<<endl<<"\t"<<"Selectati o optiune valida"<<endl;
            Meniu::prelucrareOptiune(obj);
            break;
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
        cout<<"\t"<<"Introduceti numele fisierului:";
        cin.getline(NumeFisier,49);
        ifstream a(NumeFisier);

        while (a >> cuvant)
        {
            cout<<endl;
            cout<<cuvant<<": ";
            obj.verificaCuvant(cuvant);
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
//        DFA:
//        obj.verificaCuvant(cuvant);

//        NFA:
        obj.verificaCuvantNFA(cuvant,path,0,0);
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
    // 0 va fi by default stare initiala
    Graf g;
    g.setValues(fisier());

    Meniu menu;
    menu.afisareMeniu();

    menu.prelucrareOptiune(g);
    return 0;
}