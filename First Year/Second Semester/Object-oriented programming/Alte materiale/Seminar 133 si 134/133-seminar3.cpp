#include <iostream>
#include <string>
#include<typeinfo>
using namespace std;

/*** Baza de masini (marca): autobuze (nr locuri) si autoturisme (culoare).
Sa se citeasca n masini, sa se stocheze si sa se afiseze grupate dupa tip (autobuz/autoturism)
***/
class masina{
protected:

    string marca;
public:
    masina(string marca){this->marca = marca;}
    virtual void afisare(){cout<<marca<<" ";}
};
class autobuze : public masina{
    int nr_locuri;
public:

    autobuze(int locuri, string marca): masina(marca),nr_locuri(locuri){}
    void afisare(){
        masina::afisare();
        cout<<nr_locuri<<endl;}

};
class autoturism: public masina{
    string culoare;
public:
    autoturism(string cul, string marca): masina(marca), culoare(cul){};
    void afisare(){
        masina::afisare();
        cout<<culoare<<endl;}
    };
int main(){
    int n;
    cin>>n;
    masina **v = new masina*[n];
    int optiune;
    for(int i=0;i<n;i++){
        cin>>optiune;
        if(optiune==1){
            string aux;
            int locuri;
            cin>>aux>>locuri;
            v[i] = new autobuze(locuri,aux);
        }
        else{
            string aux, culoare;
            cin>>aux>>culoare;
            v[i] = new autoturism(culoare,aux);
        }
    }
    for(int i=0;i<n;i++){
        if(typeid(*v[i]) == typeid(autobuze))
            v[i]->afisare();
    }
    for(int i=0;i<n;i++){
        if(typeid(*v[i]) == typeid(autoturism))
            v[i]->afisare();
    }
}
/*************************************************************************/
/*
class Baza{
public:
    void b(){cout<<"B\n";}
    virtual ~Baza(){};
};

class Derivata1: public Baza
{
public:
    void d1(){cout<<"Derivata1\n";}
};

class Derivata2: public Derivata1
{
public:
    void d2(){cout<<"Derivata2\n";}
};

int main()
{
    Baza* p = new Derivata1();
    Derivata2 *q = dynamic_cast<Derivata2*>(p);
    q->d2();
}
*/

/********** downcasting problematic ****************/
/*

/// constructor explicit din derivata face trimitere automat catre constr init din baza
/// trebuie constr param explicit din derivata : Baza(constructor param)
/// trebuie constr copiere explicit din derivata : Baza(constructor copiere)

class Baza
{
    protected:
    int x; ///vptr* ----> VTABLE ---> LISTA CU ADRESELE FUNCTIILOR VIRTUALE
public:
    Baza(){cout<<"Baza init\n";}
    Baza(int a){x = a; cout<<"Baza param\n";}
    Baza(Baza& ob){x = ob.x; cout<<"Baza copiere\n";}
    virtual ~Baza(){cout<<"destr baza\n";}
///    virtual void f(){cout<<"f din Baza\n";}
};

class Derivata : public Baza
{
    int y;
public:
    Derivata(){cout<<"Derivata init\n";}
    Derivata(int b):Baza(b){y = b; cout<<"Derivata param\n";}
    Derivata(Derivata& ob):Baza(ob){y = ob.y; cout<<"Derivata copiere\n";}
    ~Derivata(){cout<<"destr derivata\n";}
    void f(){cout<<x<<"f din derivata\n";}
};

int main()
{
    ///Derivata ob;
    ///Derivata ob1(10);
    ///Derivata ob2(ob1);

    cout<<sizeof(Baza)<<"   "<<sizeof(Derivata)<<"\n";

    Baza* x = new Derivata();
    cout<<x<<"\n";
///    x->f();
///    Derivata* t = (Derivata*)(x); ///downcasting
    Derivata* t = dynamic_cast<Derivata*>(x);
    cout<<t<<"\n";
    t->f();
    delete x;

    Derivata* p = new Derivata(12);
    p->f();
    delete p; /// fara delete avem Memory Leak

    Baza *q = new Derivata(234); /// upcasting
    ((Derivata*)(q))->f(); /// downcasting

    Derivata* r;
///    r = (Derivata*)q;  /// downcasting
    r = dynamic_cast<Derivata*>(q);
    r->f();
    delete q;

    return 0;
}

*/
