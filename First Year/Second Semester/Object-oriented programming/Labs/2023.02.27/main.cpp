#include <iostream>
#include <string.h>

using namespace std;

class Calculator
{
private:
    const int idCalculator;
    char *NumeProcesor;
    string PlacaVideo;
    float Pret;

    int *MemorieRam; //list<int>MemorieRam; este STL (standard template library)
    int NrRam;

    bool OnStock;
    char ClasaE;
    static int contorID; // o zona de memorie care e impartita pentru toate obiectele, daca modific ceva se modifica la toate obiectele

public:
    //getters
    static int getContorID(){return Calculator::contorID;}
    float getPret();
    string &getPlacaVideo();
    const int* getMemorieRam();
    int getNrRam();
    bool isOnStock();
    char getClasaE();
    static int getContorId();
    const int getIdCalculator();
    char* getNumeProcesor(){return this->NumeProcesor;}

    //setters
    void setPret(float Pret);
    void setNrRam(int NrRam);
    void setOnStock(bool OnStock);
    void setClasaE(char ClasaE);
    void setMemorieRam(int* MemorieRam);
    void setPlacaVideo(string PlacaVideo);
    void setNumeProcesor(char* NumeProcesor);


    Calculator();
    Calculator(char* NumeProcesor,string PlacaVideo,float Pret,int NrRam,int* MemorieRam,bool OnStock,char ClasaE);
    Calculator(const Calculator &obj);
    ~Calculator();
    Calculator &operator= (const Calculator &obj);
};

// atributele constante trebuie initializate la nivel de constructor, ca dupa nu mai pot fi accesate
//Calculator():idCalculator(contorID++),Pret(0){} merge si asa, si scos Pret = 0; 
Calculator::Calculator():idCalculator(contorID++)
{
        NumeProcesor = new char[strlen("Anonim")+1];
        strcpy(NumeProcesor,"ANONIM");
        PlacaVideo = "ANONIM";
        Pret = 0;

        NrRam = 0;
        MemorieRam = NULL;
        OnStock = true;
        ClasaE = 'D';
}

Calculator::Calculator(char* NumeProcesor,string PlacaVideo,float Pret,int NrRam,int* MemorieRam,bool OnStock,char ClasaE):idCalculator(contorID++)
{
    this->NumeProcesor = new char[strlen(NumeProcesor)+1];
    strcpy(this->NumeProcesor,NumeProcesor);
    this->PlacaVideo = PlacaVideo;
    this->Pret = Pret;

    this->NrRam = NrRam;
    this->MemorieRam = new int[NrRam];
    for(int i=0;i<NrRam;i++)
        this->MemorieRam[i] = MemorieRam[i];
    this->OnStock = OnStock;
    this->ClasaE = ClasaE;
}

Calculator::Calculator(const Calculator &obj):idCalculator(contorID++)
{
    this->NumeProcesor = new char[strlen(obj.NumeProcesor)+1];
    strcpy(this->NumeProcesor,obj.NumeProcesor);
    this->PlacaVideo = obj.PlacaVideo;
    this->Pret = obj.Pret;

    this->NrRam = obj.NrRam;
    this->MemorieRam = new int[obj.NrRam];
    for(int i=0;i<obj.NrRam;i++)
        this->MemorieRam[i] = obj.MemorieRam[i];
    this->OnStock = obj.OnStock;
    this->ClasaE = obj.ClasaE;
}

Calculator::~Calculator()
{
    if (this->MemorieRam!=NULL)
    {
        delete[] this->MemorieRam;
        this->MemorieRam = NULL;
    }
    if (this->NumeProcesor!=NULL)
    {
        delete[] this->NumeProcesor;
        this->NumeProcesor = NULL;
    }
}

Calculator& Calculator::operator =(const Calculator &obj)
{
    if(this != &obj)
    {
        if (this->MemorieRam!=NULL)
        {
            delete[] this->MemorieRam;
            this->MemorieRam = NULL;
        }
        if (this->NumeProcesor!=NULL)
        {
            delete[] this->NumeProcesor;
            this->NumeProcesor = NULL;
        }

        this->NumeProcesor = new char[strlen(obj.NumeProcesor)+1];
        strcpy(this->NumeProcesor,obj.NumeProcesor);
        this->PlacaVideo = obj.PlacaVideo;
        this->Pret = obj.Pret;

        this->NrRam = obj.NrRam;
        this->MemorieRam = new int[obj.NrRam];
        for(int i=0;i<obj.NrRam;i++)
            this->MemorieRam[i] = obj.MemorieRam[i];
        this->OnStock = obj.OnStock;
        this->ClasaE = obj.ClasaE;

    }
    return *this;
}

float Calculator::getPret() {return this->Pret;}
// operator de rezolutie(accesare) ::
// variabilele statice poat fi accesate de o instanta(numele clasei), nu neaparat de un obiect
// in metode statice avem voie sa folosim doar atribute statice
int Calculator::contorID=1000;

string &Calculator::getPlacaVideo() {
    return PlacaVideo;
}

const int* Calculator::getMemorieRam(){
    return MemorieRam;
}

int Calculator::getNrRam() {
    return NrRam;
}

bool Calculator::isOnStock() {
    return OnStock;
}

char Calculator::getClasaE() {
    return ClasaE;
}

int Calculator::getContorId() {
    return contorID;
}

const int Calculator::getIdCalculator() {
    return idCalculator;
}

void Calculator::setPret(float Pret) {
    this->Pret = Pret;
}

void Calculator::setNrRam(int NrRam) {
    this->NrRam = NrRam;
}

void Calculator::setOnStock(bool OnStock) {
    this->OnStock = OnStock;
}

void Calculator::setClasaE(char ClasaE) {
    this->ClasaE = ClasaE;
}

void Calculator::setMemorieRam(int *MemorieRam) {
    if (this->MemorieRam!=NULL)
    {
        delete[] this->MemorieRam;
        this->MemorieRam = NULL;
    }
    this->MemorieRam = new int[NrRam];
    for(int i=0;i<NrRam;i++)
        this->MemorieRam[i] = MemorieRam[i];
}

void Calculator::setNumeProcesor(char *NumeProcesor) {
    if(this->NumeProcesor != NULL)
    {
        delete[] this->NumeProcesor;
        this->NumeProcesor = NULL;
    }
    this->NumeProcesor = new char[strlen(NumeProcesor)+1];
    strcpy(this->NumeProcesor,NumeProcesor);
}

void Calculator::setPlacaVideo(string PlacaVideo) {
    this->PlacaVideo = PlacaVideo;
}

int main()
{
//    cout<<Calculator::getContorID();
    int a[] = {1,2,3,4}, b[] = {4,5};
    char c[] = "Intel",d[] = "AMD";

    Calculator C1;
    Calculator C2(c,"Nvidia",100,4,a,true,'A');

    /*
    cout<<endl<<C2.getPret()<<endl<<C2.getNumeProcesor()<<endl;

    Calculator C3(C2), C4 = C2;
    cout<<endl<<C3.getPret()<<endl<<C3.getNumeProcesor()<<endl;
    cout<<endl<<C4.getPret()<<endl<<C4.getNumeProcesor()<<endl;

    C1 = C2;
    */
    //before setters
    cout<<C2.getPlacaVideo()<<" "<<C2.getClasaE()<<" "<<C2.getIdCalculator()<<" "<<" "<<C2.getNrRam();
    cout<<" "<<C2.getPret()<<" "<<C2.isOnStock()<<" "<<C2.getNumeProcesor()<<" ";
    const int* p = C2.getMemorieRam();
    cout<<"Mem RAM: ";
    for(int i=0;i<C2.getNrRam();i++)
        cout<<p[i]<<" ";
    cout<<endl;

    C2.setPret(200);
    C2.setNrRam(2);
    C2.setPlacaVideo("AMD");
    C2.setNumeProcesor(d);
    C2.setMemorieRam(b);
    C2.setClasaE('B');
    C2.setOnStock(false);

    //after setters
    cout<<C2.getPlacaVideo()<<" "<<C2.getClasaE()<<" "<<C2.getIdCalculator()<<" "<<" "<<C2.getNrRam();
    cout<<" "<<C2.getPret()<<" "<<C2.isOnStock()<<" "<<C2.getNumeProcesor()<<" ";
    p = C2.getMemorieRam();
    cout<<"Mem RAM: ";
    for(int i=0;i<C2.getNrRam();i++)
        cout<<p[i]<<" ";

    // intreaba profesor ce sa fac in acest caz
    const int *v = C2.getMemorieRam();
    v[0] = -100;
    cout<<endl<<"*"<<p[0];
    cout<<endl;
    return 0;
}

//tema toti getters si setters