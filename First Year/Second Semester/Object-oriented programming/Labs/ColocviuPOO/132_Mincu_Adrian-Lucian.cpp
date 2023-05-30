/*
 MINCU ADRIAN-LUCIAN 132
 CLion
 Eduard Gabriel Szmeteanca
*/
#include <iostream>
#include <vector>
#include <typeinfo>
#include <set>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class Drum: public IOInterface{
protected:
    string denumire;
    float lungime;
    int nrTronsoane;
public:
    Drum():nrTronsoane(1){}

    friend istream& operator>>(istream& in, Drum& obj);
    friend ostream& operator<<(ostream& out,const Drum& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    bool operator==(const Drum& obj);
    virtual float cost();

    int getNrTronsoane() {return this->nrTronsoane;}
    float getLungime(){return this->lungime;}
};

float Drum::cost() {
    return 3000*(lungime/nrTronsoane);
}

// TODO meniu asociare contract cu d

bool Drum::operator==(const Drum &obj) {
    return (this->denumire == obj.denumire);
}

istream& Drum::citire(std::istream &in) {
    cout<<"Introdu denumire: \n";
    in>>denumire;
    cout<<"Introdu lungime: \n";
    in>>lungime;
    bool ok = false;
    while(ok == false) {
        try {
            int tronson;
            cout<<"Introdu nr tronsoane: \n";
            cin>>tronson;
            if(tronson < 1) throw tronson;
            nrTronsoane = tronson;
            ok = true;
        }
        catch(int) {
            cout << "Nr Tronsoane invalid\n";
        }
    }

    return in;
}

ostream& Drum::afisare(ostream &out) const {
    out<<"Denumire: "<<denumire<<endl;
    out<<"Lungime: "<<lungime<<endl;
    out<<"Nr. Tronsoane: "<<nrTronsoane<<endl;

    return out;
}

istream& operator>>(istream& in, Drum& obj) {
    return obj.citire(in);
}

ostream & operator<<(ostream & out,const Drum& obj) {
    return obj.afisare(out);
}

class DrumNational:virtual public Drum {
protected:
    int nrJudete;
public:
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

istream& DrumNational::citire(std::istream &in) {
    this->Drum::citire(in);
    cout<<"Introdu nr Judete: \n";
    in>>nrJudete;
    return in;
}

ostream& DrumNational::afisare(ostream &out) const {
    this->Drum::afisare(out);
    out<<"Nr Judete: "<<nrJudete<<endl;

    return out;
}

class DrumEuropean:virtual public Drum {
protected:
    int nrTari;
public:
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    float cost();
};

float DrumEuropean::cost() {
    float temp = this->Drum::cost();
    temp += 500*nrTari;
    return temp;
}

istream& DrumEuropean::citire(std::istream &in) {
    this->Drum::citire(in);
    cout<<"Introdu nr tari: \n";
    in>>nrTari;
    return in;
}

ostream& DrumEuropean::afisare(ostream &out) const {
    this->Drum::afisare(out);
    out<<"Nr tari: "<<nrTari<<endl;

    return out;
}

class Autostrada: public DrumEuropean {
private:
    // TODO nrBenzi >=2
    int nrBenzi;
public:
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    float cost();
};

float Autostrada::cost() {
    return 2500*nrBenzi*(lungime/nrTronsoane);
}

istream& Autostrada::citire(std::istream &in) {
    this->DrumEuropean::citire(in);
    bool ok = false;
    while(!ok ) {
        try {
            int nr;
            cout<<"Introdu nr benzi: \n";
            cin>>nr;
            if(nr < 2) throw nr;
            nrBenzi = nr;
            ok = true;
        }
        catch(int) {
            cout<<"Nr benzi invalid\n";
        }

    }
    return in;
}

ostream& Autostrada::afisare(ostream &out) const {
    this->DrumEuropean::afisare(out);
    out<<"Nr benzi: "<<nrBenzi<<endl;
    return out;
}

class Contract {
private:
    static int contor;
    const int ID;
    string nume,CIF;
    Drum* d;
    int tronson;
public:
    Contract():ID(contor++){}
    Contract(const Contract& obj);
    Contract &operator=(const Contract& obj);
    friend istream& operator>>(istream& in, Contract& obj);
    friend ostream& operator<<(ostream& out, const Contract& obj);
    bool operator==(const Contract& obj);
    void setDrum(Drum* obj);
    void setTronson(int tronson);
    const string& getCIF() const {return this->CIF;}
    Drum* const getDrum() const {return this->d;}
};

int Contract::contor = 0;

void Contract::setTronson(int tronson) {
    this->tronson = tronson;
}

void Contract::setDrum(Drum* obj) {
    if(typeid(*obj) == typeid(DrumNational)) d = new DrumNational();
    if(typeid(*obj) == typeid(DrumEuropean)) d = new DrumEuropean();
    if(typeid(*obj) == typeid(Autostrada)) d = new Autostrada();
    this->d = obj;
    cout<<*d<<endl;
}

Contract::Contract(const Contract &obj):ID(contor++) {
    this->nume = obj.nume;
    this->CIF = obj.CIF;
    this->d = obj.d;
    this->tronson = obj.tronson;
}

Contract& Contract::operator=(const Contract& obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->CIF = obj.CIF;
        this->d = obj.d;
        this->tronson = obj.tronson;
    }
    return *this;
}

bool Contract::operator==(const Contract &obj) {
    return (this->d == obj.d && this->tronson == obj.tronson);
}

istream& operator>>(istream& in, Contract& obj) {
    cout<<"Introdu nume: \n";
    in>>obj.nume;
    cout<<"Introdu CIF: \n";
    in>>obj.CIF;

    return in;
}

ostream& operator<<(ostream& out, const Contract& obj) {
    out<<"ID: "<<obj.ID<<endl;
    out<<"Nume: "<<obj.nume<<endl;
    out<<"CIF: "<<obj.CIF<<endl;
    out<<"Drum: "<<*obj.d<<endl;
    out<<"Tronson: "<<obj.tronson<<endl;

    return out;
}

class Menu {
private:
    Menu() = default;
    Menu(const Menu& obj)  = delete;
    Menu& operator=(const Menu& obj) = delete;
    static int nrInstance;
    static Menu* singleton;
    vector<Drum*> d;
    vector<Contract> c;
public:
    Menu* getInstance();
    ~Menu();
    void display();
    void engine();
};

Menu* Menu::singleton = NULL;
int Menu::nrInstance = 0;

void Menu::display() {
    cout<<"---MENU---\n";
    cout<<"1. Citeste drum\n";
    cout<<"2. Citeste contract\n";
    cout<<"3. Afiseaza drumuri\n";
    cout<<"4. Afiseaza contracte\n";
    cout<<"5. Calculeaza lungimea totala\n";
    cout<<"6. Reziliaza contracte\n";
    cout<<"7. Calculeaza cost total\n";
}

void Menu::engine() {
    this->display();
    while(true) {
        int option;
        cin>>option;
        switch (option) {
            case 1: {
                Drum* temp;
                cout<<"1. Drum national\n";
                cout<<"2. Drum european\n";
                cout<<"3. Autostrada\n";
                int opt;
                cin>>opt;
                if(opt == 1) temp = new DrumNational();
                if(opt == 2) temp = new DrumEuropean();
                if(opt == 3) temp = new Autostrada();
                cin>>*temp;
                d.push_back(temp);
                this->display();
                break;
            }
            case 2: {
                Contract temp;
                cin>>temp;
                for(int i=0;i<d.size();i++)
                    cout<<"\tDRUM: "<<i<<endl<<*d[i]<<endl;
                int index;
                cout<<"Alege index drum\n";
                cin>>index;

                if(index >= 0 && index<d.size()) {
                    temp.setDrum(d[index]);
                }

                bool ok = false;
                while(!ok ) {
                    try {
                        int tronson;
                        cout<<"Introdu tronson: \n";
                        cin>>tronson;
                        if(tronson < 1 || tronson > d[index]->getNrTronsoane()) throw tronson;
                        temp.setTronson(tronson);
                        ok = true;
                    }
                    catch(int) {
                        cout<<"Tronson invalid\n";
                    }

                }

                c.push_back(temp);
                this->display();
                break;
            }
            case 3: {
                for(int i=0;i<d.size();i++)
                    cout<<"\tDRUM: "<<i<<endl<<*d[i]<<endl;
                this->display();
                break;
            }
            case 4: {
                for(int i=0;i<c.size();i++)
                    cout<<"\tCONTRACT: "<<i<<endl<<c[i]<<endl;
                this->display();
                break;
            }
            case 5: {
                float ldrum=0;
                float lauto=0;
                for(int i=0;i<d.size();i++) {
                    ldrum += d[i]->getLungime();
                    if(typeid(*d[i]) == typeid(Autostrada)) lauto += d[i]->getNrTronsoane();
                }
                cout<<"Lungime toate drumurile: "<<ldrum<<endl;
                cout<<"Lungime autosrazi: "<<lauto<<endl;
                this->display();
                break;
            }
            case 6: {
                cout<<"Introdu cif: \n";
                string cif;
                cin>>cif;
                for(int i=0;i<c.size();i++) {
                    if(c[i].getCIF() == cif) {
                        swap(c[c.size()-1],c[i]);
                        c.pop_back();
                    }
                }
                this->display();
                break;
            }
            case 7: {
                for(int i=0;i<c.size();i++)
                    cout<<"\tCONTRACT: "<<i<<endl<<c[i]<<endl;
                cout<<"Alege index contract: \n";
                int index;
                cin>>index;
                if(index >= 0 && index <c.size() )
                    cout<<c[index].getDrum()->cost()<<endl;
                this->display();
                break;
            }
            default: cout<<"Optiune invalida\n";
        }
    }
}

Menu* Menu::getInstance() {
    nrInstance++;
    if(!singleton) singleton = new Menu();
    return singleton;
}

Menu::~Menu() {
    nrInstance--;
    if(nrInstance == 0){
        for(int i=0;i<d.size();i++) if(d[i]) delete d[i];
        if(!c.empty()) c.clear();
        if(!d.empty()) d.clear();
        delete singleton;
    }
}

int main() {
    Menu* m = m->getInstance();
    m->engine();
    return 0;
}
