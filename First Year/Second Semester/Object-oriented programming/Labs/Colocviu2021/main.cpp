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
    virtual ~Jucarie();

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

class Clasice:public Jucarie {
protected:
    string material, culoare;
public:
    Clasice();
    ~Clasice();

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
    ~Educative();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Educative::Educative():Jucarie() {
    abilitate = "";
}

Educative::~Educative() {
    abilitate = "";
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
    ~Electronice();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Electronice::Electronice():Jucarie() {
    nrBat = 0;
}

Electronice::~Electronice() {
    nrBat = 0;
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
    ~Moderne();

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
    virtual ~Copil();
    Copil(const Copil& obj);
    Copil& operator=(const Copil& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Copil& obj);
    friend ostream & operator<<(ostream & out,const Copil& obj);

    Copil operator+(int nr);

    const string& getNume() const {return this->nume;}
    const int getVarsta() const {return this->varsta;}
    const int getFapte() const {return this->nrFapteBune;}

    const vector<Jucarie *> &getJucarii() const;
};

int Copil::contorID = 0;

Copil::Copil(const Copil& obj):ID(contorID++) {
    this->nume = obj.nume;
    this->prenume = obj.prenume;
    this->adresa = obj.adresa;
    this->varsta = obj.varsta;
    this->nrFapteBune = obj.nrFapteBune;
    this->jucarii = obj.jucarii;
}

Copil& Copil::operator=(const Copil &obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->prenume = obj.prenume;
        this->adresa = obj.adresa;
        this->varsta = obj.varsta;
        this->nrFapteBune = obj.nrFapteBune;
        if (!this->jucarii.empty()) this->jucarii.clear();
        this->jucarii = obj.jucarii;
    }
    return *this;
}

Copil Copil::operator+(int nr) {
    this->nrFapteBune += nr;
    for(int i=0;i<nr;i++) {
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
    return *this;
}

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
    if(!jucarii.empty()) {
        for(int i=0;i<jucarii.size();i++)
            if(jucarii[i]) delete jucarii[i];
        jucarii.clear();
    }
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
    ~Cuminte();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Cuminte::Cuminte():Copil() {
    nrDulciuri = 0;
}

Cuminte::~Cuminte() {
    nrDulciuri = 0;
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
    ~Neastamparat();

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

Neastamparat::Neastamparat():Copil() {
    nrCarbuni = 0;
}

Neastamparat::~Neastamparat() {
    nrCarbuni = 0;
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
                for(int i=0;i<copii.size();i++)
                    cout<<"Copil: "<<i<<"\n"<<*copii[i]<<endl;

                int index;
                cout<<"Index: \n";
                cin>>index;
                if(index >= 0 && index < copii.size()) {
                    int nr;
                    cout<<"Nr fapte bune: \n";
                    cin>>nr;
                    *copii[index] = *copii[index] + nr;
                }
                this->display();
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
                break;
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
