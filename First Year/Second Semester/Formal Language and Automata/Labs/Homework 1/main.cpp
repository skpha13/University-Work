#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("graf.in");

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
    for(int i=0;i<StariFinale.size();i++)
        if(stare == StariFinale[i])
            cout<<"Accepta";
    cout<<endl<<"Drum: ";
    for(int i=0;i<path.size();i++)
        cout<<"q"<<path[i]<<" ";
}

int main() {
    // 0 va fi by default stare initiala
    Graf g;
    g.setValues();

    //afisare graf
    cout<<"Numar noduri: "<<g.getNrNod()<<endl;
    cout<<"Numar muchii: "<<g.getNrMuchii()<<endl;
    cout<<"Numar stari finale: "<<g.getNrStariFinale()<<endl;

    const vector<int> &v = g.getStariFinale();
    const vector<vector<Drum>> &graf = g.getMatrice();

    cout<<"Tranzitii:"<<endl;
    for(int i=0;i<g.getNrNod();i++) {
        cout<<"\t";
        for (int j=0;j<graf[i].size();j++)
            cout<<"curent: "<<i<<" urmatorul: "<< graf[i][j].urmatorul << " litera: " << graf[i][j].litera<<" ";
        cout<<endl;
    }

    cout<<"Stari finale: ";
    for(int i=0;i<g.getNrStariFinale();i++)
        cout<<v[i]<<" ";
    cout<<endl;

    //procesare cuvant
    char cuvant[256];

    cout<<"Introduceti cuvantul:";
    cin.getline(cuvant,256);
    g.verificaCuvant(cuvant);

    return 0;
}
