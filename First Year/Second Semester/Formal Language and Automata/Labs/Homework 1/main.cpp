#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("graf2.in");

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
    void setValues();

    //methods
    void afiseazaInfo() const;
    void verificaCuvant(char cuvant[]);
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

void Graf::setValues() {
    int nod_curent,nod_tranzitie,stare_finala;
    char valoare;
    Drum d;

    f>>NrNod>>NrMuchii>>NrStariFinale;

    for(int j=0;j<NrMuchii;j++)
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

void Graf::verificaCuvant(char cuvant[]) {
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

class Meniu{
private:
    static bool TipCitire;
    char* NumeFisier;

public:
    //getters & setters
    bool getTipCitire();
    void setTipCitire(bool TipCitire);

    const char* const getNumeFisier();
    void setNumeFisier(char* NumeFisier);

    //methods
    void afisareMeniu(int lungimeBreak = 20);
    const void prelucrareOptiune(const Graf &obj);
    void selectareModCitire(int opt = 0);
};

//initializare tip citire
bool Meniu::TipCitire = 0;

bool Meniu::getTipCitire() {
    return this->TipCitire;
}

void Meniu::setTipCitire(bool TipCitire) {
    this->TipCitire = TipCitire;
}

const char* const Meniu::getNumeFisier() {
    if(this->NumeFisier != NULL)
    {
        delete[] this->NumeFisier;
        this->NumeFisier = NULL;
    }
    this->NumeFisier = new char[strlen(NumeFisier)+1];
    strcpy(this->NumeFisier,NumeFisier);
}

void Meniu::setNumeFisier(char* NumeFisier) {
    this->NumeFisier = NumeFisier;
}

void Meniu::afisareMeniu(int lungimeBreak) {
    for(int i=0;i<lungimeBreak/2;i++) cout<<"-";
    cout<<" MENIU ";
    for(int i=lungimeBreak/2;i<lungimeBreak;i++) cout<<"-";

    cout<<endl<<endl;
    cout<<"1. Afisare informatii graf"<<endl;
    cout<<"2. Selectare mod citire"<<endl;
    cout<<"3. Citire cuvant"<<endl;
    cout<<"4. Apasati 4 pentru ajutor"<<endl;
    cout<<"5. Iesiti din program"<<endl;

    // +7 pt lungimea cuvaantului meniu
    cout<<endl;
    for(int i=0;i<lungimeBreak + 7;i++) cout<<"-";
    cout<<endl;
}

const void Meniu::prelucrareOptiune(const Graf &obj) {
    Meniu m;
    int nrCitit;

    cout<<endl<<"Optiune:";
    cin>>nrCitit;

    switch (nrCitit) {
        case 1:
            obj.afiseazaInfo();
            Meniu::afisareMeniu();
            Meniu::prelucrareOptiune(obj);

        case 2:
            Meniu::selectareModCitire();
            Meniu::afisareMeniu();
            Meniu::prelucrareOptiune(obj);

        case 3:
            break;

        case 4:
            cout<<endl<<"\t"<<"Tastati un numar(cu optiunea pe care o doriti) si apasati enter"<<endl;
            Meniu::prelucrareOptiune(obj);

        case 5:
            break;

        default:
            cout<<endl<<"\t"<<"Selectati o optiune valida"<<endl;
            Meniu::prelucrareOptiune(obj);
    }
}

void Meniu::selectareModCitire(int tipCitire) {
    //if anything besides 0 and 1 are entered it doesn't work
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
        char input[256];
        cout<<"\t"<<"Introduceti numele fisierului:";
        cin>>input;
        cin.get();
        Meniu::setNumeFisier(input);
    }
}

int main() {
    // 0 va fi by default stare initiala
    Graf g;
    g.setValues();

    Meniu menu;
    menu.afisareMeniu();
    menu.prelucrareOptiune(g);
//    g.afiseazaInfo();
//
//    //procesare cuvant
//    char cuvant[256];
//
//    cout<<"Introduceti cuvantul:";
//    cin.getline(cuvant,255);
//    g.verificaCuvant(cuvant);

    return 0;
}

/*

    cuvinte:
110001010
110101002
10101010

bbabbabba
abbabba
ababababababaaaaaba
bbbbbbaaaaabbbabbaaaaaaab

*/