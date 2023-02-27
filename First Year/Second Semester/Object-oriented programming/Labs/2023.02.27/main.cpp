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
    int getPret();

    Calculator();
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
int Calculator::getPret() {return Pret;}
// operator de rezolutie(accesare) ::
// variabilele statice poat fi accesate de o instanta(numele clasei), nu neaparat de un obiect
// in metode statice avem voie sa folosim doar atribute statice
int Calculator::contorID=1000;

int main()
{
    cout<<Calculator::getContorID();
    return 0;
}