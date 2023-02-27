#include <iostream>

using namespace std;

class Calculator
{
private:
    const int idCalculator;
    char *nume_procesor;
    string placa_video;
    float pret;
    int *p = new int[3];
    int NrRam;
    bool OnStock;
    char ClasaEnergetica;

public:
    static int contorID; // o zona de memorie care e impartita pentru toate obiectele, daca modific ceva se modifica la toate obiectele
};

// operator de rezolutie(accesare)
int Calculator::contorID=1000;

int main()
{
    cout<<Calculator::contorID;
    return 0;
}