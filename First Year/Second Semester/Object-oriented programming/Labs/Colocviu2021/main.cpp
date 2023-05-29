#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class Jucarie: public IOInterface{
protected:
    string denumire;
    int dimensiune;
public:
    Jucarie();
    Jucarie(string,int);
    Jucarie(const Jucarie& obj);
    virtual ~Jucarie();

    Jucarie& operator=(const Jucarie& obj);
    friend istream& operator>>(istream& in, Jucarie& obj);
    friend ostream& operator<<(ostream& out,const Jucarie& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

istream& operator>>(istream& in, Jucarie& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream & out,const Jucarie& obj) {
    return obj.afisare(out);
}

istream& Jucarie::citire(istream &in) {
    cout<<"Denumire: \n";
    in>>denumire;
    cout<<"Dimensiune: \n";
    in>>dimensiune;
    in.get();
    return in;
}

ostream& Jucarie::afisare(ostream &out) const {
    out<<"Denumire: "<<denumire<<endl;
    out<<"Dimensiune: "<<dimensiune<<endl;
    return out;
}

Jucarie::Jucarie() {
    denumire = "";
    dimensiune = 0;
}

Jucarie::~Jucarie() {
    denumire = "";
    dimensiune = 0;
}

Jucarie::Jucarie(std::string denumire, int dimensiune) {
    this->denumire = denumire;
    this->dimensiune = dimensiune;
}

Jucarie::Jucarie(const Jucarie &obj) {
    this->denumire = obj.denumire;
    this->dimensiune = obj.dimensiune;
}

Jucarie &Jucarie::operator=(const Jucarie &obj) {
    if(this != & obj){
        this->denumire = obj.denumire;
        this->dimensiune = obj.dimensiune;
    }
    return *this;
}

class Clasice:public Jucarie {
protected:
    string material, culoare;
public:
    Clasice();
    Clasice(string,int ,string,string);
    Clasice(const Clasice& obj);
    virtual ~Clasice();

    Clasice& operator=(const Clasice& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Clasice::Clasice():Jucarie() {
    material = "";
    culoare = "";
}

Clasice::~Clasice() {
    material = "";
    culoare = "";
}

Clasice::Clasice(string denumire, int dimensiune, std::string material, string culoare):Jucarie(denumire, dimensiune) {
    this->material = material;
    this->culoare = culoare;
}

Clasice::Clasice(const Clasice &obj):Jucarie(obj) {
    this->material = obj.material;
    this->culoare = obj.culoare;
}

Clasice &Clasice::operator=(const Clasice &obj) {
    if(this != & obj){
        Jucarie::operator=(obj);
        this->material = obj.material;
        this->culoare = obj.culoare;
    }
    return *this;
}

istream& Clasice::citire(std::istream &in) {
    this->Jucarie::citire(in);
    cout<<"Material: \n";
    in>>material;
    cout<<"Culoare: \n";
    in>>culoare;
    return in;
}

ostream& Clasice::afisare(std::ostream &out) const {
    this->Jucarie::afisare(out);
    out<<"Material: "<<material<<endl;
    out<<"Culoare: "<<culoare<<endl;
    return out;
}

class Educative:virtual public Jucarie {
protected:
    string abilitate;
public:
    Educative();
    Educative(string, int, string);
    Educative(const Educative& obj);
    virtual ~Educative();

    Educative& operator=(const Educative& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Educative::Educative():Jucarie() {
    abilitate = "";
}

Educative::~Educative() {
    abilitate = "";
}

Educative::Educative(string denumire, int dimensiune, std::string abilitate):Jucarie(denumire, dimensiune) {
    this->abilitate = abilitate;
}

Educative::Educative(const Educative &obj):Jucarie(obj) {
    this->abilitate = obj.abilitate;
}

Educative &Educative::operator=(const Educative &obj) {
    if(this != & obj){
        Jucarie::operator=(obj);
        this->abilitate = obj.abilitate;
    }
    return *this;
}

istream& Educative::citire(istream &in) {
    this->Jucarie::citire(in);
    cout<<"Abilitate: \n";
    in>>abilitate;
    return in;
}

ostream& Educative::afisare(ostream &out) const {
    this->Jucarie::afisare(out);
    out<<"Abilitate: "<<abilitate<<endl;
    return out;
}

class Electronice:virtual public Jucarie {
protected:
    int nrBat;
public:
    Electronice();
    Electronice(string, int, int);
    Electronice(const Electronice& obj);
    virtual ~Electronice();

    Electronice& operator=(const Electronice& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Electronice::Electronice():Jucarie() {
    nrBat = 0;
}

Electronice::~Electronice() {
    nrBat = 0;
}

Electronice::Electronice(string denumire, int dimensiune, int nrBat):Jucarie(denumire,dimensiune) {
    this->nrBat = nrBat;
}

Electronice::Electronice(const Electronice &obj):Jucarie(obj) {
    this->nrBat = obj.nrBat;
}

Electronice &Electronice::operator=(const Electronice &obj) {
    if(this != & obj){
        Jucarie::operator=(obj);
        this->nrBat = obj.nrBat;
    }
    return *this;
}

istream& Electronice::citire(std::istream &in) {
    this->Jucarie::citire(in);
    cout<<"Nr bat: \n";
    in>>nrBat;
    return in;
}

ostream& Electronice::afisare(std::ostream &out) const {
    this->Jucarie::afisare(out);
    out<<"Nr bat: "<<nrBat<<endl;
    return out;
}

class Moderne:public Educative, public Electronice {
private:
    string brand, model;
public:
    Moderne();
    Moderne(string,int,string,string);
    Moderne(const Moderne& obj);
    virtual ~Moderne();

    Moderne& operator=(const Moderne& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Moderne::Moderne():Jucarie(),Educative(),Electronice() {
    brand = "";
    model = "";
    nrBat = 1;
    abilitate = "generala";
}

Moderne::~Moderne() {
    brand = "";
    model = "";
}

Moderne::Moderne(string denumire, int dimensiune, string brand, string model):Jucarie(denumire, dimensiune),
                                                                                Educative(denumire,dimensiune,"generala"),
                                                                                Electronice(denumire,dimensiune,1)
{
    this->brand = brand;
    this->model = model;
}

Moderne::Moderne(const Moderne &obj):Jucarie(obj),Educative(obj),Electronice(obj) {
    this->brand = obj.brand;
    this->model = obj.model;
}

Moderne &Moderne::operator=(const Moderne &obj) {
    if(this != & obj){
        Educative::operator=(obj);
        Electronice::operator=(obj);
        this->brand = obj.brand;
        this->model = obj.model;
    }
    return *this;
}

istream& Moderne::citire(std::istream &in) {
    this->Jucarie::citire(in);
    cout<<"Brand: \n";
    in>>brand;
    cout<<"Model: \n";
    in>>model;
    return in;
}

ostream& Moderne::afisare(std::ostream &out) const {
    this->Educative::afisare(out);
    out<<"Nr bat: "<<nrBat<<endl;
    out<<"Brand: "<<brand<<endl;
    out<<"Model: "<<model<<endl;
    return out;
}

class Copil: public IOInterface{
protected:
    static int contorID;
    const int ID;
    string nume,prenume,adresa;
    int varsta,nrFapteBune;
    vector<Jucarie*> jucarii;
public:
    Copil();
    Copil(string,string,string,int,int,vector<Jucarie*>);
    Copil(const Copil& obj);
    virtual ~Copil();

    Copil& operator=(const Copil& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Copil& obj);
    friend ostream & operator<<(ostream & out,const Copil& obj);

    const string& getNume() const {return this->nume;}
    const int getVarsta() const {return this->varsta;}
    const int getFapte() const {return this->nrFapteBune;}

    const vector<Jucarie *> &getJucarii() const;
};

int Copil::contorID = 0;

Copil::Copil():ID(contorID++) {
    nume = "";
    prenume = "";
    adresa = "";
    varsta = 0;
    nrFapteBune = 0;
}

Copil::~Copil() {
    contorID--;
    nume = "";
    prenume = "";
    adresa = "";
    varsta = 0;
    nrFapteBune = 0;
    if(!jucarii.empty()) jucarii.clear();
}

Copil::Copil(std::string nume, std::string prenume, std::string adresa, int varsta, int nrFapteBune, vector<Jucarie*> jucarii):ID(contorID++) {
    this->nume = nume;
    this->prenume = prenume;
    this->adresa = adresa;
    this->varsta = varsta;
    this->nrFapteBune = nrFapteBune;
    if(!jucarii.empty()) jucarii.clear();
    this->jucarii = jucarii;
}

Copil::Copil(const Copil &obj):ID(contorID++) {
    this->nume = obj.nume;
    this->prenume = obj.prenume;
    this->adresa = obj.adresa;
    this->varsta = obj.varsta;
    this->nrFapteBune = obj.nrFapteBune;
    if(!this->jucarii.empty()) this->jucarii.clear();
    this->jucarii = obj.jucarii;
}

Copil& Copil::operator=(const Copil &obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->prenume = obj.prenume;
        this->adresa = obj.adresa;
        this->varsta = obj.varsta;
        this->nrFapteBune = obj.nrFapteBune;
        if(!this->jucarii.empty()) this->jucarii.clear();
        this->jucarii = obj.jucarii;
    }
    return *this;
}

istream& operator>>(istream& in, Copil& obj) {
    return obj.citire(in);
}

ostream & operator<<(ostream & out,const Copil& obj) {
    return obj.afisare(out);
}

istream& Copil::citire(std::istream &in) {
    cout<<"Nume: \n";
    in>>nume;
    cout<<"Prenume: \n";
    in>>prenume;
    cout<<"Adresa: \n";
    in>>adresa;
    cout<<"Varsta: \n";
    in>>varsta;
    cout<<"Fapte bune: \n";
    in>>nrFapteBune;
    for(int i=0;i<nrFapteBune;i++) {
        cout<<"1. Clasica\n";
        cout<<"2. Educativa\n";
        cout<<"3. Electronica\n";
        cout<<"4. Moderna\n";

        Jucarie* j;
        int temp;
        cout<<"Introdu optiune\n";
        cin>>temp;
        cin.get();
        if(temp == 1) j = new Clasice();
        if(temp == 2) j = new Educative();
        if(temp == 3) j = new Electronice();
        if(temp == 4) j = new Moderne();

        in>>*j;
        jucarii.push_back(j);
    }

    return in;
}

ostream& Copil::afisare(std::ostream &out) const {
    out<<"Nume: "<<nume<<endl;
    out<<"Prenume: "<<prenume<<endl;
    out<<"Adresa: "<<adresa<<endl;
    out<<"Varsta: "<<varsta<<endl;
    out<<"Fapte bune: "<<nrFapteBune<<endl;
    for(int i=0;i<nrFapteBune;i++){
        cout<<"\tJucarie "<<i<<":\n";
        cout<<*jucarii[i]<<endl;
    }
    return out;
}

const vector<Jucarie *> &Copil::getJucarii() const {
    return jucarii;
}

class Cuminte:public Copil {
private:
    int nrDulciuri;
public:
    Cuminte();
    Cuminte(string,string,string,int,vector<Jucarie*>,int);
    Cuminte(const Cuminte& obj);
    virtual ~Cuminte();

    Cuminte& operator=(const Cuminte& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Cuminte::Cuminte():Copil() {
    nrDulciuri = 0;
}

Cuminte::~Cuminte() {
    nrDulciuri = 0;
}

Cuminte::Cuminte(std::string nume, std::string prenume, std::string adresa, int varsta, vector<Jucarie*> jucarii, int nrDulciuri):Copil(nume,prenume,adresa,varsta,10,jucarii) {
    this->nrDulciuri = nrDulciuri;
}

Cuminte::Cuminte(const Cuminte &obj):Copil(obj) {
    this->nrDulciuri = nrDulciuri;
}

Cuminte& Cuminte::operator=(const Cuminte &obj) {
    if(this != &obj) {
        Copil::operator=(obj);
        this->nrDulciuri = nrDulciuri;
    }
    return *this;
}

istream& Cuminte::citire(std::istream &in) {
    try {
        cout << "Nume: \n";
        in >> nume;
        cout << "Prenume: \n";
        in >> prenume;
        cout << "Adresa: \n";
        in >> adresa;
        cout << "Varsta: \n";
        in >> varsta;
        cout << "Fapte bune: \n";
        in >> nrFapteBune;
        if (nrFapteBune < 10) throw nrFapteBune;
        for(int i=0;i<nrFapteBune;i++) {
            cout<<"1. Clasica\n";
            cout<<"2. Educativa\n";
            cout<<"3. Electronica\n";
            cout<<"4. Moderna\n";

            Jucarie* j;
            int temp;
            cout<<"Introdu optiune\n";
            cin>>temp;
            cin.get();
            if(temp == 1) j = new Clasice();
            if(temp == 2) j = new Educative();
            if(temp == 3) j = new Electronice();
            if(temp == 4) j = new Moderne();

            cin>>*j;
            jucarii.push_back(j);
        }
        cout << "Nr dulciuri:\n";
        in >> nrDulciuri;
    }
    catch (const int& e) {
        cout<<e<<" fapte bune nu e destul pentru copil cuminte\n";
    }
    return in;
}

ostream& Cuminte::afisare(std::ostream &out) const {
    this->Copil::afisare(out);
    out<<"Nr dulciuri: "<<nrDulciuri<<endl;
    return out;
}

class Neastamparat:public Copil {
private:
    int nrCarbuni;
public:
    Neastamparat();
    Neastamparat(string,string,string,int,int,vector<Jucarie*>,int);
    Neastamparat(const Neastamparat& obj);
    virtual ~Neastamparat();

    Neastamparat& operator=(const Neastamparat& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Neastamparat::Neastamparat():Copil() {
    nrCarbuni = 0;
}

Neastamparat::~Neastamparat() {
    nrCarbuni = 0;
}

Neastamparat::Neastamparat(std::string nume, std::string prenume, std::string adresa, int varsta, int nrFapteBune,vector<Jucarie*> jucarii, int nrCarbuni):Copil(nume,prenume,adresa,varsta,nrFapteBune,jucarii) {
    this->nrCarbuni = nrCarbuni;
}

Neastamparat::Neastamparat(const Neastamparat &obj):Copil(obj) {
    this->nrCarbuni = nrCarbuni;
}

Neastamparat& Neastamparat::operator=(const Neastamparat &obj) {
    if(this != &obj) {
        Copil::operator=(obj);
        this->nrCarbuni = nrCarbuni;
    }
    return *this;
}

istream& Neastamparat::citire(std::istream &in) {
    this->Copil::citire(in);
    cout<<"Nr carbuni:\n";
    in>>nrCarbuni;

    return in;
}

ostream& Neastamparat::afisare(std::ostream &out) const {
    this->Copil::afisare(out);
    out<<"Nr carbuni: "<<nrCarbuni<<endl;
    return out;
}

class Menu {
private:
    static Menu* singleton;
    static int nrInstance;
    Menu() = default;
    Menu(const Menu&) = delete;
    vector<Copil*> copii;
public:
    static Menu* getInstance() {
        nrInstance++;
        if(singleton == NULL) singleton = new Menu();
        return singleton;
    }
    ~Menu() {
        nrInstance--;
        if(nrInstance == 0 && singleton) delete singleton;
    }
    void display();
    void engine();
};

Menu* Menu::singleton = NULL;
int Menu::nrInstance = 0;

void Menu::display() {
    cout<<"---Optiuni---\n";
    cout<<"1 Adaugare copil\n";
    cout<<"2 Gasire copil\n";
    cout<<"3 Ordonare varsta\n";
    cout<<"4 Ordonare fapte bune\n";
    cout<<"5 Creste fapte bune\n";
    cout<<"6 Contorizare\n";
}

bool cmp1(const Copil* ob1, const Copil* ob2) {
    return ob1->getVarsta() < ob2->getVarsta();
}

bool cmp2(const Copil* ob1, const Copil* ob2) {
    return ob1->getFapte() < ob2->getFapte();
}

void Menu::engine() {
    this->display();
    while(true) {
        int option;
        cin>>option;
        cin.get();
        switch (option) {
            case 1: {
                cout<<"1. Citire\n";
                cout<<"2. Afisare\n";
                int op;
                cin>>op;
                cin.get();
                if(op == 1) {
                    Copil *temp = new Copil;
                    cin >> *temp;
                    copii.push_back(temp);
                }
                else if(op == 2) {
                    for(int i=0;i<copii.size();i++)
                        cout<<*copii[i]<<endl;
                }
                this->display();
                break;
            }
            case 2: {
                string nume;
                cout<<"nume: \n";
                cin>>nume;
                for(int i=0;i<copii.size();i++)
                {
                    if(copii[i]->getNume() == nume)
                        cout<<*copii[i]<<endl;
                }
                this->display();
                break;
            }
            case 3: {
                sort(copii.begin(),copii.end(),cmp1);
                for(int i=0;i<copii.size();i++)
                        cout<<*copii[i]<<endl;
                this->display();
                break;
            }
            case 4: {
                sort(copii.begin(),copii.end(),cmp2);
                for(int i=0;i<copii.size();i++)
                    cout<<*copii[i]<<endl;
                this->display();
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                int c = 0,ed = 0,el = 0,m = 0;
                for(int i=0;i<copii.size();i++) {
                    for(int j=0;j<copii[i]->getJucarii().size();j++) {
                        if(typeid(*copii[i]->getJucarii()[j]) == typeid(Clasice))
                            c++;
                        if(typeid(*copii[i]->getJucarii()[j]) == typeid(Educative))
                            ed++;
                        if(typeid(*copii[i]->getJucarii()[j]) == typeid(Electronice))
                            el++;
                        if(typeid(*copii[i]->getJucarii()[j]) == typeid(Moderne))
                            m++;
                    }
                }
                cout<<c<<" clasice\n";
                cout<<ed<<" educative\n";
                cout<<el<<" electronice\n";
                cout<<m<<" moderne\n";

            }
            default: cout<<"Nu e valida optinea\n";
        }
    }
}

int main() {
    Menu* m = m->getInstance();
    m->engine();
    return 0;
}
