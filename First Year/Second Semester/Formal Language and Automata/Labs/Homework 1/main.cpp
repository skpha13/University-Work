#include <iostream>
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

    void setValues();
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

int main() {
    Graf g;
    g.setValues();
    cout<<g.getNrNod()<<" "<<g.getNrMuchii()<<" "<<g.getNrStariFinale()<<endl;
    const vector<int> &v = g.getStariFinale();
    const vector<vector<Drum>> &graf = g.getMatrice();

    for(int i=0;i<g.getNrStariFinale();i++)
        cout<<v[i]<<" ";
    cout<<endl;

    for(int i=0;i<g.getNrNod();i++) {
        for (int j = 0; j < graf[i].size(); j++)
            cout <<"curent: "<<i<<" urmatorul: "<< graf[i][j].urmatorul << " litera: " << graf[i][j].litera<<" ";
        cout<<endl;
    }
    return 0;
}
