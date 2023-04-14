#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Ingredient{
    string nume;
    float pret;

public:
    Ingredient(string, float);
    Ingredient(const Ingredient&);

    Ingredient& operator =(const Ingredient&);
    friend istream& operator >>(istream&, Ingredient&);
    friend ostream& operator <<(ostream&, const Ingredient&);

    float getPret() const {return this->pret;}
};

Ingredient::Ingredient(string nume = "", float pret = 0){
    this->nume = nume;
    this->pret = pret;
}

Ingredient::Ingredient(const Ingredient& obj){
    this->nume = obj.nume;
    this->pret = obj.pret;
}

Ingredient& Ingredient::operator =(const Ingredient& obj){
    if(this != &obj){
        this->nume = obj.nume;
        this->pret = obj.pret;
    }
    return *this;
}

istream& operator >>(istream& in, Ingredient& obj){
    cout << "Introduceti numele\n";
    in >> obj.nume;
    cout << "Introduceti pretul\n";
    in >> obj.pret;
    return in;
}

ostream& operator <<(ostream& os, const Ingredient& obj){
    os << "Nume: " << obj.nume << endl;
    os << "Pret: " << obj.pret << endl;
    return os;
}

class IOinterface{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class Bautura: public IOinterface{
protected:
    string nume;
    vector<Ingredient> listaIng;
    float volum;

public:
    Bautura();
    Bautura(string nume, const vector<Ingredient>& listaIng, float volum);
    Bautura(const Bautura&);

    Bautura& operator=(const Bautura&);
    friend istream& operator >>(istream&, Bautura&);
    friend ostream& operator <<(ostream&, const Bautura&);

    istream& citire(istream& in){
        cout << "Introduceti numele\n";
        in >> this->nume;
        if(!this->listaIng.empty()){
                this->listaIng.clear();
        }
        cout << "1. Add ing\n";
        cout << "2. Inceteaza sa adaugi\n";
        int k;

        while(cin >> k && k != 2){
            ///Ingredient i;
            ///in >> i;
            ///obj.listaIng.push_back(i);
            this->listaIng.push_back(*(new Ingredient()));
            in >> this->listaIng.back();
            cout << "1. Add ing\n";
            cout << "2. Inceteaza sa adaugi\n";
        }

        cout << "Introduceti volumul\n";
        in >> this->volum;
        return in;
    }

    ostream& afisare(ostream& os) const{
        os << "Nume: " << this->nume << endl;
        os << "Lista de ingredient: \n";
        for(int i = 0; i < this->listaIng.size(); i++)
            os << this->listaIng[i] << endl;
        os << "Volum: " << this->volum << endl;
        os << "Pret: " << this->pret() << endl;
        return os;
    }

    string getNume() {return this->nume;}
    virtual float pret() const = 0;
    void test() {cout << "bautura\n";}
    virtual ~Bautura() {}
};

class BauturaAlcoolica: virtual public Bautura{
protected:
    int alcool;
public:
    BauturaAlcoolica();
    BauturaAlcoolica(string nume, const vector<Ingredient>& listaIng, float volum, int alcool);
    BauturaAlcoolica(const BauturaAlcoolica&);

    BauturaAlcoolica& operator =(const BauturaAlcoolica&);

    istream& citire(istream& in){
        this->Bautura::citire(in);
        cout << "Introduceti cantitatea de alcool\n";
        in >> this->alcool;
        return in;
    }

    ostream& afisare(ostream& os) const {
        this->Bautura::afisare(os);
        cout << "Cantitate alcool: " << this->alcool << endl;
        return os;
    }

    float pret() const {float pret = 0; for(int i = 0; i < this->listaIng.size(); i++) pret += this->listaIng[i].getPret(); return pret*1.1;}
    void test() {cout << "bautura alcoolica\n";}
    virtual ~BauturaAlcoolica() {}
};

class BauturaNonalcoolica: virtual public Bautura{
protected:
    int kcal;
    bool co2;
public:
    BauturaNonalcoolica();
    BauturaNonalcoolica(string nume, const vector<Ingredient>& listaIng, float volum, int kcal, bool co2);
    BauturaNonalcoolica(const BauturaNonalcoolica&);

    BauturaNonalcoolica& operator =(const BauturaNonalcoolica&);

    istream& citire(istream& in){
        this->Bautura::citire(in);
        cout << "Introduceti cantitatea de kcal\n";
        in >> this->kcal;
        cout << "Introduceti co2\n";
        in >> this->co2;
        return in;
    }

    ostream& afisare(ostream& os) const {
        this->Bautura::afisare(os);
        cout << "Cantitate kcal: " << this->kcal << endl;
        cout << "Co2: " << this->co2 << endl;
        return os;
    }

    float pret() const {
        float pret = 0; 
        for(int i = 0; i < this->listaIng.size(); i++) 
            pret += this->listaIng[i].getPret(); 
        return pret*1.2;
    }

    void test() {cout << "bautura nonalcoolica\n";}

    virtual ~BauturaNonalcoolica() {}
};

Bautura::Bautura(){
    this->nume = "anonim";
    this->listaIng = {};
    this->volum = 0;
    cout << "bautura\n";
}

Bautura::Bautura(string nume, const vector<Ingredient>& listaIng, float volum){
    this->nume = nume;
    this->listaIng = listaIng;
    this->volum = volum;
}

Bautura::Bautura(const Bautura& obj){
    this->nume = obj.nume;
    this->listaIng = obj.listaIng;
    this->volum = obj.volum;
}

Bautura& Bautura::operator=(const Bautura& obj){
    if(this != &obj){
        this->nume = obj.nume;
        this->listaIng = obj.listaIng;
        this->volum = obj.volum;
    }
    return *this;
}

istream& operator >>(istream& in, Bautura& obj){
    return obj.citire(in);
}

ostream& operator <<(ostream& os, const Bautura& obj){
    return obj.afisare(os);
}

BauturaAlcoolica::BauturaAlcoolica(): Bautura(){
    this->alcool = 0;
    cout << "bautura alcoolica\n";
}

BauturaAlcoolica::BauturaAlcoolica(string nume, const vector<Ingredient>& listaIng, float volum, int alcool):
    Bautura(nume, listaIng, volum){
    this->alcool = alcool;
}

BauturaAlcoolica::BauturaAlcoolica(const BauturaAlcoolica& obj): Bautura(obj){
    this->alcool = obj.alcool;
}

BauturaAlcoolica& BauturaAlcoolica::operator =(const BauturaAlcoolica& obj){
    if(this != &obj){
        Bautura::operator=(obj);
        this->alcool = obj.alcool;
    }
    return *this;
}

BauturaNonalcoolica::BauturaNonalcoolica(): Bautura(){
    this->kcal = 0;
    this->co2 = 0;
    cout << "bautura nonalcoolica\n";
}

BauturaNonalcoolica::BauturaNonalcoolica(string nume, const vector<Ingredient>& listaIng, float volum, int kcal, bool co2):
    Bautura(nume, listaIng, volum){
    this->kcal = kcal;
    this->co2 = co2;
}

BauturaNonalcoolica::BauturaNonalcoolica(const BauturaNonalcoolica& obj): Bautura(obj){
    this->kcal = obj.kcal;
    this->co2 = obj.co2;
}

BauturaNonalcoolica& BauturaNonalcoolica::operator =(const BauturaNonalcoolica& obj){
    if(this != &obj){
        Bautura::operator=(obj);
        this->kcal = obj.kcal;
        this->co2 = obj.co2;
    }
    return *this;
}

class Cocktail: public BauturaAlcoolica, public BauturaNonalcoolica {
    bool palariuta;
public:
    Cocktail(){
        this->palariuta = 0;
        cout << "cocktail\n";
    }

    Cocktail(string nume, const vector<Ingredient>& listaIng, float volum, 
            int alcool, int kcal, bool co2, bool palariuta): Bautura(nume, listaIng, volum), BauturaAlcoolica(nume, 
                listaIng, volum, alcool), BauturaNonalcoolica(nume, listaIng, volum, kcal, co2){
        this->palariuta = palariuta;
    }

    Cocktail(const Cocktail& obj): Bautura(obj), BauturaAlcoolica(obj), BauturaNonalcoolica(obj){
        this->palariuta = obj.palariuta;
    }

    Cocktail& operator =(const Cocktail& obj){
        if(this != &obj){
            BauturaAlcoolica::operator=(obj);
            BauturaNonalcoolica::operator=(obj);
            this->palariuta = obj.palariuta;
        }
        return *this;
    }

    istream& citire(istream& in) {
        Bautura::citire(in);
        cout << "Introduceti cantitatea de alcool\n";
        in >> this->alcool;
        cout << "Introduceti cantitatea de kcal\n";
        in >> this->kcal;
        cout << "Introduceti co2\n";
        in >> this->co2;
        cout << "Introduceti palariuta\n";
        in >> this->palariuta;
        return in;
    }
    ostream& afisare(ostream& os) const {
        Bautura::afisare(os);
        os << "Cantitate alcool: " << this->alcool << endl;
        os << "Cantitate kcal: " << this->kcal << endl;
        os << "Co2: " << this->co2 << endl;
        os << "Palariuta: " << this->palariuta << endl;
        return os;
    }
    float pret() const {
        return BauturaAlcoolica::pret() + 10 * this->palariuta;
    }

    void fCocktail() {cout << "metoda\n" << this->palariuta << endl;}
    
    virtual ~Cocktail() {}
};

class ItemInventar{
    Bautura* bautura;
    bool stoc;
public:
    friend istream& operator >>(istream& in, ItemInventar& obj){
        cout << "1. Bautura alcoolica\n";
        cout << "2. Bautura nonalcoolica\n";
        cout << "3. Cocktail\n";
        int k;
        cin >> k;
        if(k == 1){
            obj.bautura = new BauturaAlcoolica();
        }
        if(k == 2){
            obj.bautura = new BauturaNonalcoolica();
        }
        if(k == 3)
            obj.bautura = new Cocktail();
        in >> *obj.bautura;
        cout << "Introduceti stoc\n";
        in >> obj.stoc;
        return in;
    }

    friend ostream& operator<<(ostream& os, const ItemInventar& obj){
        os << "Bautura:\n" << *obj.bautura << endl;
        os << "Stoc: " << obj.stoc << endl;
        return os;
    }

    Bautura* getBautura() {return this->bautura;}
};

class Bar{
    list<ItemInventar> inventar;
    vector<Bautura*> meniu;
public:
    void addInventar();
    void addMeniu(string numeBautura);
    void showInventar();
    void showMeniu();
};

void Bar::addInventar(){
    ItemInventar i;
    cin >> i;
    inventar.push_back(i);
}

void Bar::showInventar(){
    for(auto it = inventar.begin(); it != inventar.end(); it++)
        cout << *it << endl;
}

void Bar::addMeniu(string numeBautura){
    for(auto it = inventar.begin(); it != inventar.end(); it++){
        if(it->getBautura()->getNume() == numeBautura){
            meniu.push_back(it->getBautura());
        }
    }
}

void Bar::showMeniu(){
    for(int i = 0; i < meniu.size(); i++)
        cout << *meniu[i] << endl;
}


int main()
{
    ///Bautura a;  clasa abstracta => eroare

    Bar b;
    //Cocktail c;
    //c.BauturaAlcoolica::test();
    /*
    Bautura* p = new BauturaAlcoolica();
    dynamic_cast<Cocktail&>(*p).fCocktail();    bad cast
    */

   Bautura* p = new Cocktail();
   dynamic_cast<Cocktail*>(p)->fCocktail();

/*
    int k = 1;
    while(k == 1){
        cout << "1. Add inventar\n";
        cout << "2. Show inventar\n";
        cout << "3. Add meniu\n";
        cout << "4. Show meniu\n";
        cout << "5. Stop\n";
        int comanda;
        cin >> comanda;
        switch(comanda){
            case 1:{
                b.addInventar();
                break;
            }

            case 2:{
                b.showInventar();
                break;
            }

            case 3:{
                cout << "Nume: ";
                string nume;
                cin >> nume;
                b.addMeniu(nume);
                break;
            }

            case 4:{
                b.showMeniu();
                break;
            }

            case 5:{
                k = 0;
                break;
            }
        }
    }
    */
    return 0;
}
