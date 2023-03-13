#include <iostream>
#include <string.h>
using namespace std;

class StupAlbine {
private:
    static int contorId;
    const int idStup;
    char* numeStup;
    string tipMiere;
    char culoare;
    int nrLuni;
    float* cantitateMiereNLuni;
    bool regina;

public:
    //Constructori
    StupAlbine();  // Constructor fara parametrii
    StupAlbine(char* numeStup, string tipMiere, char culoare, int nrLuni, 
        float* cantitateMiereNLuni, bool regina); // Constructor parametrizat
    StupAlbine(const StupAlbine& obj);   // Copy constructor

    //Operator
    StupAlbine& operator = (const StupAlbine&);
    friend ostream& operator <<(ostream& out, const StupAlbine& obj);
    friend istream& operator >>(istream& in, StupAlbine& obj);

    //Metode
    void afisare();
    void citire();
    
    //Get+Set
    static int getContorId() {return StupAlbine::contorId;}
    string getTipMiere() {return tipMiere;}
    int getNrLuni() {return nrLuni;}
    const float* getCantitateMiere() const {this->cantitateMiereNLuni;}

    friend void afisare2(const StupAlbine& obj);


    //Destructor
    ~StupAlbine();

};

int StupAlbine::contorId = 1000;

StupAlbine::StupAlbine():idStup(contorId++) {
    numeStup = new char[strlen("Anonim") + 1]; // Alocat memorie fara sa initializam
    strcpy(numeStup, "Anonim");  // Initializam variabila
    tipMiere = "Anonim";
    culoare = '-';
    nrLuni = 0;
    cantitateMiereNLuni = NULL;
    regina = false;
}

StupAlbine::StupAlbine(char* numeStup, string tipMiere, char culoare, int nrLuni, 
float* cantitateMiereNLuni, bool regina): idStup(contorId++){
    this->numeStup = new char[strlen(numeStup) + 1];
    strcpy(this->numeStup, numeStup);  
    this->tipMiere = tipMiere;
    this->culoare = culoare;
    this->nrLuni = nrLuni;
    this->cantitateMiereNLuni = cantitateMiereNLuni;
    //gresit trebuie alocata memorie pentru this->cantitateMiereNluni
    this->regina = regina;
}

StupAlbine::StupAlbine(const StupAlbine& obj): idStup(contorId++){ 
    this->numeStup = new char[strlen(obj.numeStup) + 1];
    strcpy(this->numeStup, obj.numeStup);  
    this->tipMiere = obj.tipMiere;
    this->culoare = obj.culoare;
    this->nrLuni = obj.nrLuni;
    this->cantitateMiereNLuni = new float[obj.nrLuni];
    for(int i = 0; i < obj.nrLuni; i++)
        this->cantitateMiereNLuni[i] = obj.cantitateMiereNLuni[i];  // Pentru a avea o zona de memorie diferita
    this->regina = obj.regina;   
}

StupAlbine& StupAlbine::operator = (const StupAlbine& obj){
    if(this != &obj){
        if(this->numeStup != NULL){
            delete[] this->numeStup;
            this->numeStup = NULL;
        }

        if(this->cantitateMiereNLuni != NULL){
            delete[] this->cantitateMiereNLuni;
            cantitateMiereNLuni = NULL;
        }

        this->numeStup = new char[strlen(obj.numeStup) + 1];
        strcpy(this->numeStup, obj.numeStup);  
        this->tipMiere = obj.tipMiere;
        this->culoare = obj.culoare;
        this->nrLuni = obj.nrLuni;
        this->cantitateMiereNLuni = new float[obj.nrLuni];
        for(int i = 0; i < obj.nrLuni; i++)
            this->cantitateMiereNLuni[i] = obj.cantitateMiereNLuni[i];  // Pentru a avea o zona de memorie diferita
        this->regina = obj.regina;   
    }
    return *this;
}

void StupAlbine::afisare(){
    cout << "ID: " << this->idStup << endl;
    cout << "Nume: " << this->numeStup << endl;
    cout << "Tip miere: " << this->tipMiere << endl; 
    cout << "Culoare: " << this->culoare << endl; 
    cout << "Nr luni: " << this->nrLuni << endl; 
    cout << "Cantitate: ";
    for(int i = 0; i < this->nrLuni; i++)
        cout << this->cantitateMiereNLuni[i] << " ";
    cout << endl;
    cout << "Regina: " << this->regina << endl; 
} 

void afisare2(const StupAlbine& obj){
    cout << "ID: " << obj.idStup << endl;
    cout << "Nume: " << obj.numeStup << endl;
    cout << "Tip miere: " << obj.tipMiere << endl; 
    cout << "Culoare: " << obj.culoare << endl; 
    cout << "Nr luni: " << obj.nrLuni << endl; 
    cout << "Cantitate: ";
    for(int i = 0; i < obj.nrLuni; i++)
        cout << obj.cantitateMiereNLuni[i] << " ";
    cout << endl;
    cout << "Regina: " << obj.regina << endl; 
}

void StupAlbine::citire(){
    cout << "Introduceti numele stupului: " << endl;
    char numeStup[100];
    cin >> numeStup;
    if(this->numeStup != NULL){
        delete this->numeStup;
        this->numeStup = NULL;
    }
    this->numeStup = new char[strlen(numeStup) + 1];
    strcpy(this->numeStup, numeStup);

    cout << "Introduceti tip miere: " << endl;
    cin >> this->tipMiere;

    cout << "Introduceti culoare: " << endl;
    cin >> this->culoare;

    cout << "Introduceti nr luni: " << endl;
    cin >> this->nrLuni;

    cout << "Introduceti cantitate miere: " << endl;
    if(this->cantitateMiereNLuni != NULL){
        delete[] this->cantitateMiereNLuni;
        this->cantitateMiereNLuni = NULL;
    }

    this->cantitateMiereNLuni = new float[this->nrLuni];
    for(int i = 0; i < this->nrLuni; i++)
        cin >> this->cantitateMiereNLuni[i];

    cout << "Introduceti regina: " << endl;
    cin >> this->regina;
}

ostream& operator <<(ostream& out, const StupAlbine& obj){
    out << "ID: " << obj.idStup << endl;
    out << "Nume: " << obj.numeStup << endl;
    out << "Tip miere: " << obj.tipMiere << endl; 
    out << "Culoare: " << obj.culoare << endl; 
    out << "Nr luni: " << obj.nrLuni << endl; 
    out << "Cantitate: ";
    for(int i = 0; i < obj.nrLuni; i++)
        out << obj.cantitateMiereNLuni[i] << " ";
    out << endl;
    out << "Regina: " << obj.regina << endl;
    return out;
}

istream& operator >>(istream& in, StupAlbine& obj){
    cout << "Introduceti numele stupului: " << endl;
    char numeStup[100];
    in >> numeStup;
    if(obj.numeStup != NULL){
        delete obj.numeStup;
        obj.numeStup = NULL;
    }
    obj.numeStup = new char[strlen(numeStup) + 1];
    strcpy(obj.numeStup, numeStup);

    cout << "Introduceti tip miere: " << endl;
    in >> obj.tipMiere;

    cout << "Introduceti culoare: " << endl;
    in >> obj.culoare;

    cout << "Introduceti nr luni: " << endl;
    in >> obj.nrLuni;

    cout << "Introduceti cantitate miere: " << endl;
    if(obj.cantitateMiereNLuni != NULL){
        delete[] obj.cantitateMiereNLuni;
        obj.cantitateMiereNLuni = NULL;
    }

    obj.cantitateMiereNLuni = new float[obj.nrLuni];
    for(int i = 0; i < obj.nrLuni; i++)
        in >> obj.cantitateMiereNLuni[i];

    cout << "Introduceti regina: " << endl;
    in >> obj.regina;
    return in;
}

StupAlbine::~StupAlbine(){
    if(this->numeStup != NULL){
        delete[] this->numeStup;
        this->numeStup = NULL;
    }

    if(this->cantitateMiereNLuni != NULL){
        delete[] this->cantitateMiereNLuni;
        cantitateMiereNLuni = NULL;
    }
}

int main(){
    StupAlbine a;

    char numeStup[] = {"Zooooom"};
    float n = 1.2, n2 = 1.3, n3 = 1.5;
    float cantitateMiereNLuni[] = {n, n2, n3};

    StupAlbine a2(numeStup, "Good Honey", 'g', 3, cantitateMiereNLuni, true);

    //cout << a2.getTipMiere() << endl;

    StupAlbine a3(a2);
    StupAlbine a4;  // Tot copy constructor

    //cout << a3.getTipMiere() << endl;

    //cout << StupAlbine::getContorId(); // 1004, avem 4 stupi

    cin>>a4;
    // cout << a.getTipMiere() << endl;

    //a4.afisare();
    //a4.citire();
    //a4.afisare();
    //cin >> a4;
    cout << a4;

    for(int i = 0; i < a4.getNrLuni(); i++)
        cout << a4.getCantitateMiere()[i] << ' ';
    
    return 0;
}