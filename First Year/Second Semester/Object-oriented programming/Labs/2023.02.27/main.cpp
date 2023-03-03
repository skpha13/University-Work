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
    static int getContorID(){return Calculator::contorID;}
    float getPret();
    char* getNumeProcesor(){return this->NumeProcesor;}

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

float Calculator::getPret() {return Pret;}
// operator de rezolutie(accesare) ::
// variabilele statice poat fi accesate de o instanta(numele clasei), nu neaparat de un obiect
// in metode statice avem voie sa folosim doar atribute statice
int Calculator::contorID=1000;

int main()
{
    cout<<Calculator::getContorID();
    int a[] = {1,2,3,4};
    char c[] = "Intel";

    Calculator C1;
    Calculator C2(c,"Nvidia",100,4,a,true,'A');

    cout<<endl<<C2.getPret()<<endl<<C2.getNumeProcesor()<<endl;

    Calculator C3(C2), C4 = C2;
    cout<<endl<<C3.getPret()<<endl<<C3.getNumeProcesor()<<endl;
    cout<<endl<<C4.getPret()<<endl<<C4.getNumeProcesor()<<endl;

    C1 = C2;
    return 0;
}

//tema toti get eri si toti set eri