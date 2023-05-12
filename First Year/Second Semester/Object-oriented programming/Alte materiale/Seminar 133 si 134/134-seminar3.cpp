#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

/*** citire, stocare, afisare n auto, cu toate datele necesare. Afisarea doar a
motocicletelor cu capacitate pana in 100cp ***/

class Auto
{
protected:
    string color;
    int nr_roti;
public:
    Auto(string color, int nr_roti):nr_roti(nr_roti)
    {
        this->color = color;
    }
    virtual void Afis()
    {
        cout << color << " " << nr_roti << " ";
    }

};

class masina : public Auto
{
    string marca;
public:
    masina(string marca, string color, int nr_roti):Auto(color, nr_roti), marca(marca){}
    void Afis()
    {
        Auto::Afis();
        cout << marca <<endl;
    }

};

class moto : public Auto
{
    int cp;
public:
    int get_cp()  ///getter cp
    {
        return cp;
    }
    moto(string color, int nr_roti, int cp): Auto(color, nr_roti), cp(cp){}
    void Afis()
    {
        Auto::Afis();
        cout << cp <<endl;
    }
};

class bicicleta_mo : public moto
{
public:
    bicicleta_mo(string color, int nr_roti): moto(color, nr_roti, 0){}
};

int main()
{
    ///Auto ob("rosu", 0);
    /*masina ob_2("dacia", "rosu", 4);
    ob_2.Afis();
    moto ob_3("negru", 2, 100);
    ob_3.Afis();
    bicicleta_mo ob_4("bej", 2);
    ob_4.Afis();*/
    int n;
    vector <Auto*> v;   ///putem stoca acum obiecte din clase diferite la un loc
    cin >> n;
    for(int i = 0 ; i < n; i++)
        {
            int optiune;
            cin >> optiune;
            if (optiune == 1)
                {int a;
                 string b,c;
                 cin >> a >> b >> c;
                 v.push_back(new masina(b,c,a));
                }
            else if (optiune == 2)
            {
                int a , b;
                string c;
                cin >> a >> b >> c;
                v.push_back(new moto(c,a,b));
            }
            else
            {
                int a;
                string b;
                cin >> a >> b;
                v.push_back(new bicicleta_mo(b , a));
            }

        }
    for(int i = 0 ; i < n; i++)
    {
        v[i]->Afis();
    }
    for(int i = 0 ; i < n; i++)
    {    ///am verificat daca suntem in clasa moto   ///downcast adica transformam pointer de la clasa Auto, la moto
        ///if (typeid(*v[i]) == typeid(moto) && ((moto*)(v[i]))->get_cp() <= 100)
            ///v[i]->Afis();
        if (typeid(*v[i]) == typeid(moto))
            {
                moto* temp;
                temp = (moto*)(v[i]);
                temp->Afis();
            }
        ///liniile 106+107 sunt echivalente cu 108-113
    }
}

/****************************************************************/
/*
class Baza
{ protected:
    int x;
public:
    Baza(int a = 0) : x(a){}
    Baza(Baza& ob) : x(ob.x) {}
};

class Derivata : public Baza
{
    int y;
public:
    Derivata(int a = 0, int b = 0): Baza(a) ,y(b){}
///    Derivata(Derivata& ob) : Baza(ob), y(ob.y){}
///    Derivata(Derivata& ob) : Baza(ob){ y = ob.y;}
    void afis(){cout<<x<<"  "<<y<<"\n";}
};

int main()
{
    Derivata ob(2,3);
    ob.afis();
    Derivata ob2(ob);
    ob2.afis();
}
*/
