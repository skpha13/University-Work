#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Curs
{
    char* denumire;
public:
    Curs(){denumire = new char[100];}
    Curs(Curs& ob){
        denumire = new char[strlen(ob.denumire)+1];
        strcpy(denumire, ob.denumire);
        cin>>ob.denumire;
        strcpy(ob.denumire,"modificat");
        }
    ~Curs(){delete[] denumire;}
    void citire() {cin>>denumire;}
    void afisare(){cout<<denumire<<endl;}
};

int main()
{
    Curs a;
    a.citire();
    a.afisare();
    {
        Curs b(a);
    }
    a.afisare();
}

/*******************************************/
/*
class Curs
{
    int nr_ore;
public:
    Curs(int nr_ore = 20){this->nr_ore = nr_ore;}
    void citire(){cin>>nr_ore;}
    void afisare(){cout<<nr_ore;}
    operator int(){return nr_ore;} ///  operator de cast catre int
};

int main()
{
    Curs a0; /// default a0.nr_ore = 20;
    Curs a = 100;  /// cast prin intermediul constr cu 1 param
    Curs b = a; /// aici constructor de copiere
    Curs c(100);
    int X = a; /// merge doar daca am oepratorul de cast supraincarcat
    /*
    Curs a[20];
    int n;
    cin>>n;
    for(int i = 0; i<n; i++)
        a[i].citire();

    for(int i = 0; i<n; i++)
        a[i].afisare();

}
*/
/********************************************************/
/*
class Curs
{
    int nr_ore, grupa;
   /// string titular; char* titular;
public:
    void citire();
    virtual void afisare();
};

class Optional : public Curs{
public:
    void afisare(){cout<<"A\n";}
};

void Curs::citire()
{
    cin>>nr_ore>>grupa;
}

void Curs::afisare()
{
    cout<<nr_ore<<" "<<grupa<<endl;
}

int main()
{
        vector<Curs*> vv;
    vv.push_back(new Curs());
    (vv.back())->citire();
    vv.push_back(new Optional()); /// upcasting: pointer catre clasa de baza retine adresa de obiect derivat
    (vv.back())->citire();

    for(auto p = vv.begin(); p != vv.end(); p++)
        (**p).afisare();  /// (*p)->afisare();
    /*
    vector<Curs> v;
    int n;

    v.push_back(Curs());
    (v.back()).citire();
    (v.back()).afisare();
    for(int i = 0; i<v.size(); i++)
        v[i].afisare();

///    for(auto p = v.begin(); p != v.end(); p++)
vector<Curs>::iterator p;
    for( p = v.begin(); p != v.end(); p++)
        (*p).afisare();

vector<Curs>::reverse_iterator q;
    for(q = v.rbegin(); q != v.rend(); q++)
        (*q).afisare();




    return 0;
}
*/
