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

    //metode
    void afiseazaInfo();
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

void Graf::afiseazaInfo() {
    cout<<"Numar noduri: "<<NrNod<<endl;
    cout<<"Numar muchii: "<<NrMuchii<<endl;
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
    bool TipCitire;
    char* NumeFisier;

public:

};

int main() {
    // 0 va fi by default stare initiala
    Graf g;
    g.setValues();

    g.afiseazaInfo();

    //procesare cuvant
    char cuvant[256];

    cout<<"Introduceti cuvantul:";
    cin.getline(cuvant,256);
    g.verificaCuvant(cuvant);

    return 0;
}
