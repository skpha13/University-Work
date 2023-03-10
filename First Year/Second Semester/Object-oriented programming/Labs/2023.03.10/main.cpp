#include <iostream>
#include <string.h>

using namespace std;
//clase- fiecare cuvant cu litera mare la inceput
//metode- prima litera mica,urm mari

class StupAlbine {
private:
    static int contorId;
    const int idStup;
    char *numeStup;
    string tipMiere;
    char culoare;
    int nrLuni;
    float *cantitateMiereNLuni;
    bool regina;

public:
    //constructori
    //operatori
    //Metode --chestii care calculeaza
    //get+set
    //destructor
    StupAlbine();

    StupAlbine(char *numeStup, string tipMiere, char culoare, int nrLuni, float *cantitateMiereNLuni, bool regina);

    StupAlbine(const StupAlbine &obj);

    static int getContorid(){ return StupAlbine::contorId; }

    string gettipMiere(){ return tipMiere; }

    ~StupAlbine();

};

int StupAlbine::contorId = 1000;

StupAlbine::StupAlbine() : idStup(contorId++){
    ///ce e dupa : sn lista initializatorilor
    ///se pun cu virgula dupa : toate alea gen culoare('/'),nrLuni(0)...
    ///pt char* ne trebuie astea 2 randuri
    numeStup = new char[strlen("Anonim") + 1]; ///am alocat memorie
    strcpy(numeStup, "Anonim"); ///initializez variabila
    ///la string e destul atat
    tipMiere = "Anonim";

    culoare = '/';
    nrLuni = 0;
    cantitateMiereNLuni = NULL;
    regina = false;
}

StupAlbine::StupAlbine(char *numeStup, string tipMiere, char culoare, int nrLuni, float *cantitateMiereNLuni,
                       bool regina) : idStup(contorId++){

    this->numeStup = new char[strlen("Anonim") + 1];
    strcpy(this->numeStup, numeStup);
    this->tipMiere = tipMiere;
    this->culoare = culoare;
    this->nrLuni = nrLuni;
    this->cantitateMiereNLuni = cantitateMiereNLuni;
    this->regina = regina;
}

StupAlbine::StupAlbine(const StupAlbine &obj) : idStup(contorId++){

    this->numeStup = new char[strlen("Anonim") + 1];
    strcpy(this->numeStup, numeStup);
    this->tipMiere = tipMiere;
    this->culoare = culoare;
    this->nrLuni = obj.nrLuni;
    this->cantitateMiereNLuni = obj.cantitateMiereNLuni;
    this->regina = obj.regina;

}

StupAlbine::~StupAlbine(){
    if(this->numeStup != NULL) {
        delete[] this->numeStup;
        this->numeStup = NULL;
    }

}

int main(){
    StupAlbine a;
    char numeStup[] = {"ZOOOOM"};
    float n = 1.2;
    float n2 = 1.3;
    float n3 = 1.5;
    float cantitateMiereNLuni[] = {n, n2, n3};
    StupAlbine a2(numeStup, "Good Honey", 'g', 3, cantitateMiereNLuni, true);
    cout << a2.gettipMiere() << endl;
    cout << a.gettipMiere();
    StupAlbine a3(a2), a4 = a2;
    cout << a.gettipMiere();

    return 0;


}
