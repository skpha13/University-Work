#include <iostream>
#include <vector>
#include<typeinfo>

using namespace std;

class Candidat
{
protected:
    string cod;
    static int nr;
    string nume, serie;
    int CI;
    float bac;
    float proba;
public:
    Candidat(){cod = to_string(nr); nr++;}
    virtual void citire() = 0;
    virtual void afisare() = 0;
    friend istream& operator>>(istream&, Candidat&);
    virtual float medie() = 0;
};

int Candidat::nr = 1;

class IF :  virtual public Candidat
{
public:
    void citire(){Candidat::citire();}
    void afisare(){Candidat::afisare();}
    float medie(){return proba * 0.8 + bac * 0.2;}
};

class ID : virtual public Candidat
{
protected:
    float matebac;
public:
    ID(){cod = "ID_"+ to_string(nr);}
    void citire(){Candidat::citire(); cout<<"Nota mate bac: "; cin>>matebac;}
    void afisare(){Candidat::afisare(); cout<<" si nota mate bac "<<matebac<<endl;}
    float medie(){return proba * 0.6 + matebac * 0.4;}
};

class Adoua : virtual public Candidat
{
protected:
    float licenta1;
public:
///    void citire();  /// OBS: Ciobanu Paul - A doua facultate poate fi abstracta, pentru ca nu avem nevoie de obiecte specifice ci doar IF2FAC si ID2FAC
///    void afisare();
    float medie(){return proba * 0.6 + licenta1 * 0.4;}
};

class IF2FAC : public IF, public Adoua
{
public:
    void citire();
    void afisare();
    float medie(){return Adoua::medie();}
};

class ID2FAC : public ID, public Adoua
{
public:
    void citire();
    void afisare();
    float medie(){return Adoua::medie();}
};

int main()
{
    vector<Candidat*> v;
    int n;
    cin>>n;
    for(int i = 0; i<n; i++)
    {
        int optiune;
        cin>>optiune;
        switch(optiune)
        {
            case 1 :{ v.push_back(new IF()); break;}
            case 2 :{ v.push_back(new ID()); break;}
            case 3 :{ v.push_back(new IF2FAC()); break;}
            case 4 :{ v.push_back(new ID2FAC()); break;}
        }
            (v.back())->citire();
    }

    /// inscrisi la prima facultate IF
    int total_if = 0;
    for(auto p = v.begin(); p != v.end(); p++)
    if (typeid(**p) == typeid(IF)) {total_if++; (**p).afisare();}
    cout<<"Numarul total de dosare de la IF este: "<<total_if<<endl;

///    ID ob1,ob2,ob;
///    ob.citire();
///    ob.afisare();

///    Adoua ob;
///    ob.citire();
///    cin>>ob; /// operator>>(cin,ob); /// upcasting
///    ob.afisare();
    return 0;
}

void Candidat::citire(){
    cout<<"Nume: "; cin>>nume;
    cout<<"Serie si numar CI; "; cin>>serie>>CI;
    cout<<"Medie bac: "; cin>>bac;
    cout<<"Nota proba examen: "; cin>>proba;}

void Candidat::afisare(){cout<<"Candidatul "<<cod<<" nume "<<nume<<" are CI-ul "<<serie<<" "<<CI<<" cu media la bac "<<bac<<" si nota la examen "<<proba<<" "; }

istream& operator>>(istream& in, Candidat& c) { c.citire(); return in;}

void IF2FAC::citire(){cout<<" A 2-a facultate IF: "; Candidat::citire(); cout<<"Medie prima licenta: "; cin>>licenta1;}
void IF2FAC::afisare(){cout<<" A 2-a facultate IF: "; Candidat::afisare(); cout<<"si nota la prima licenta "<<licenta1<<endl;}
void ID2FAC::citire(){cout<<" A 2-a facultate ID: ";  Candidat::citire(); cout<<"Medie prima licenta: "; cin>>licenta1;}
void ID2FAC::afisare(){cout<<" A 2-a facultate ID: ";  Candidat::afisare(); cout<<"si nota la prima licenta "<<licenta1<<endl;}
