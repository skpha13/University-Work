#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Interfata {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& print(ostream& out) const = 0;
};

class Produs:public Interfata {
protected:
    int pret,cantitate,ID;
    static int contorID;
public:
    Produs();
    Produs(int,int);
    Produs(const Produs& obj);
    virtual ~Produs();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
    friend istream& operator>>(istream& in, Produs& obj);
    friend ostream& operator<<(ostream& out, const Produs& obj);

    int getPret() const {return this->pret;}
    int getCantitate() const {return this->cantitate;}
};

int Produs::contorID = 0;

istream& Produs::read(istream &in) {
    cout<<"Introdu pret: \n";
    in>>pret;
    cout<<"Introdu cantitate: \n";
    in>>cantitate;

    return in;
}

ostream& Produs::print(std::ostream &out) const {
    out<<"Pret: "<<pret;
    out<<"\nCantitate: "<<cantitate;
    out<<"\n";

    return out;
}

istream& operator>>(istream& in, Produs& obj) {
    return obj.read(in);
}

ostream& operator<<(ostream& out,const Produs& obj) {
    return obj.print(out);
}

Produs::Produs(const Produs &obj):ID(contorID++) {
    this->pret = obj.pret;
    this->cantitate = obj.cantitate;
}

Produs::~Produs() {
    contorID--;
    pret = 0;
    cantitate = 0;
}

Produs::Produs():ID(contorID++) {
    pret = 0;
    cantitate = 0;
}

Produs::Produs(int pret, int cantitate):ID(contorID++) {
    this->pret = pret;
    this->cantitate = cantitate;
}

class Carte:virtual public Produs {
protected:
    string titlu;
    vector<string> autori;
public:
    const string &getTitlu() const {
        return titlu;
    }
    const vector<string> &getAutori() const {
        return autori;
    }

    Carte();
    Carte(int,int,string, vector<string>);
    Carte(const Carte& obj);
    ~Carte();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

istream& Carte::read(istream &in) {
    this->Produs::read(in);
    string titlu;
    cout<<"Titlu: \n";
    if(!this->titlu.empty()) this->titlu.clear();
    in>>titlu;
    this->titlu = titlu;
    cout<<"Introdu nr autori: \n";
    int k;
    in>>k;
    in.get();
    if(k < 1) throw string("Prea putini autori, minim unul");
    if(!autori.empty()) autori.clear();
    for(int i=0;i<k;i++)
    {
        cout<<"Introdu autor: \n";
        string temp;
        in>>temp;
        autori.push_back(temp);
    }


    return in;
}

ostream& Carte::print(std::ostream &out) const {
    this->Produs::print(out);
    out<<"Titlu: "<<titlu<<endl;
    out<<"nr autori: "<<autori.size()<<endl;
    for(auto const &it:autori)
        cout<<it<<"\n";

    return out;
}

Carte::Carte():Produs() {
    titlu = "Anonim";
    autori.push_back("Anonim");
}

Carte::Carte(int pret,int cantitate, std::string titlu, vector<std::string> autori):Produs(pret, cantitate) {
    this->titlu = titlu;
    this->autori = autori;
}

Carte::Carte(const Carte &obj):Produs(obj) {
    if(!this->titlu.empty()) this->titlu.clear();
    this->titlu = obj.titlu;
    if(!this->autori.empty())this->autori.clear();
    this->autori = obj.autori;
}

Carte::~Carte() {
    if(!this->titlu.empty()) this->titlu.clear();
    if(!this->autori.empty())this->autori.clear();
}

class DVD:virtual public Produs {
protected:
    int nrMin;
public:
    DVD();
    DVD(int,int,int);
    DVD(const DVD& obj);
    ~DVD();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

istream& DVD::read(istream &in) {
    this->Produs::read(in);
    cout<<"nr min: \n";
    in>>nrMin;

    return in;
}

ostream& DVD::print(std::ostream &out) const {
    this->Produs::print(out);
    out<<"nr min: "<<nrMin<<endl;

    return out;
}

DVD::DVD():Produs() {
    nrMin = 0;
}

DVD::DVD(int pret, int cantitate, int nrMin):Produs(pret, cantitate) {
    this->nrMin = nrMin;
}

DVD::DVD(const DVD &obj):Produs(obj) {
    this->nrMin = obj.nrMin;
}

DVD::~DVD() {
    nrMin = 0;
}

class Muzica:public DVD {
protected:
    string nume;
    vector<string> interpreti;
public:
    Muzica();
    Muzica(int,int,int,string,vector<string>);
    Muzica(const Muzica& obj);
    ~Muzica();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

Muzica::Muzica():DVD() {
    nume = "";
    interpreti.push_back("Anonim");
}

Muzica::Muzica(int pret, int cantitate, int nrMin, std::string nume, vector<std::string> interpreti):DVD(pret,cantitate,nrMin) {
    this->nume = nume;
    this->interpreti = interpreti;
}

Muzica::Muzica(const Muzica &obj):DVD(obj) {
    if(!this->nume.empty()) this->nume.clear();
    this->nume = obj.nume;
    if(!this->interpreti.empty())this->interpreti.clear();
    this->interpreti = obj.interpreti;
}

Muzica::~Muzica() {
    if(!this->nume.empty()) this->nume.clear();
    if(!this->interpreti.empty())this->interpreti.clear();
}

istream& Muzica::read(istream &in) {
    this->DVD::read(in);
    string nume;
    cout<<"Nume: \n";
    if(!this->nume.empty()) this->nume.clear();
    in>>nume;
    this->nume = nume;
    cout<<"Introdu nr autori: \n";
    int k;
    in>>k;
    in.get();
    if(k<1) throw string("Prea putini interpreti (cel putin 1)\n");
    if(!interpreti.empty()) interpreti.clear();
    for(int i=0;i<k;i++)
    {
        cout<<"Introdu autor: \n";
        string temp;
        in>>temp;
        interpreti.push_back(temp);
    }

    return in;
}

ostream& Muzica::print(std::ostream &out) const {
    this->DVD::print(out);

    out<<"Nume: "<<nume<<endl;
    out<<"nr autori: "<<interpreti.size()<<endl;
    for(auto const &it:interpreti)
        cout<<it<<"\n";

    return out;
}

class Film:public DVD {
protected:
    string nume,gen;
public:
    Film();
    Film(int,int,int,string,string);
    Film(const Film& obj);
    ~Film();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

Film::Film():DVD() {
    nume = "";
    gen = "";
}

Film::Film(int pret, int cantitate, int nrMin, std::string nume, string gen):DVD(pret,cantitate,nrMin) {
    this->nume = nume;
    this->gen = gen;
}

Film::Film(const Film &obj):DVD(obj) {
    if(!this->nume.empty()) this->nume.clear();
    this->nume = obj.nume;
    if(!this->gen.empty()) this->gen.clear();
    this->gen = obj.gen;
}

Film::~Film() {
    if(!this->nume.empty()) this->nume.clear();
    if(!this->gen.empty())this->gen.clear();
}

istream& Film::read(istream &in) {
    this->DVD::read(in);
    string nume;
    cout<<"Nume: \n";
    if(!this->nume.empty()) this->nume.clear();
    in>>nume;
    this->nume = nume;

    string gen;
    cout<<"Gen: \n";
    if(!this->gen.empty()) this->gen.clear();
    in>>gen;
    this->gen = gen;

    return in;
}

ostream& Film::print(std::ostream &out) const {
    this->DVD::print(out);

    out<<"Nume: "<<nume<<endl;
    out<<"Gen: "<<gen<<endl;

    return out;
}

class Obiecte:virtual public Produs {
protected:
    string denumire;
public:
    Obiecte();
    Obiecte(int,int,string);
    Obiecte(const Obiecte& obj);
    ~Obiecte();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

Obiecte::Obiecte():Produs() {
    denumire = "";
}

Obiecte::Obiecte(int pret, int cantitate, std::string denumire): Produs(pret, cantitate) {
    this->denumire = denumire;
}

Obiecte::Obiecte(const Obiecte &obj):Produs(obj) {
    if(!this->denumire.empty()) this->denumire.clear();
    this->denumire = obj.denumire;
}

Obiecte::~Obiecte() {
    denumire = "";
}

istream& Obiecte::read(istream &in) {
    this->Produs::read(in);
    string denumire;
    cout<<"Denumire: \n";
    if(!this->denumire.empty()) this->denumire.clear();
    in>>denumire;
    this->denumire = denumire;

    return in;
}

ostream& Obiecte::print(std::ostream &out) const {
    this->Produs::print(out);
    out<<"Denumire: "<<denumire<<endl;

    return out;
}

class Figurina:public Obiecte {
protected:
    string categorie, brand, material;
public:
    Figurina();
    Figurina(int,int,string,string,string,string);
    Figurina(const Figurina& obj);
    ~Figurina();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

Figurina::Figurina():Obiecte() {
    categorie = "";
    brand = "";
    material = "";
}

Figurina::Figurina(int pret, int cantitate, string denumire, std::string categorie, string brand, string material):Obiecte(pret,cantitate,denumire) {
    this->categorie = categorie;
    this->brand = brand;
    this->material = material;
}

Figurina::Figurina(const Figurina &obj):Obiecte(obj) {
    if(!this->categorie.empty()) this->categorie.clear();
    this->categorie = obj.categorie;
    if(!this->brand.empty()) this->brand.clear();
    this->brand = obj.brand;
    if(!this->material.empty()) this->material.clear();
    this->material = obj.material;
}

Figurina::~Figurina() {
    if(!this->categorie.empty()) this->categorie.clear();
    if(!this->brand.empty())this->brand.clear();
    if(!this->material.empty())this->material.clear();
}

istream& Figurina::read(istream &in) {
    this->Obiecte::read(in);
    string categorie;
    cout<<"categorie: \n";
    if(!this->categorie.empty()) this->categorie.clear();
    in>>categorie;
    this->categorie = categorie;

    cout<<"brand: \n";
    in>>brand;

    cout<<"material: \n";
    in>>material;

    return in;
}

ostream& Figurina::print(std::ostream &out) const {
    this->Obiecte::print(out);
    out<<"categorie: "<<categorie<<endl;
    out<<"brand: "<<brand<<endl;
    out<<"material: "<<material<<endl;

    return out;
}

class Poster:public Obiecte {
protected:
    string format;
public:
    Poster();
    Poster(int,int,string,string);
    Poster(const Poster& obj);
    ~Poster();

    istream& read(istream& in);
    ostream& print(ostream& out) const;
};

Poster::Poster():Obiecte() {
    format = "A4";
}

Poster::Poster(int pret, int cantitate, string denumire, std::string format):Obiecte(pret,cantitate,denumire) {
    this->format = format;
}

Poster::Poster(const Poster &obj):Obiecte(obj) {
    if(!this->format.empty()) this->format.clear();
    this->format = obj.format;
}

Poster::~Poster() {
    if(!this->format.empty()) this->format.clear();
}

istream& Poster::read(istream &in) {
    this->Obiecte::read(in);
    string categorie;
    cout<<"categorie: \n";
    if(!this->format.empty()) this->format.clear();
    in>>format;
    this->format = format;

    return in;
}

ostream& Poster::print(std::ostream &out) const {
    this->Obiecte::print(out);
    out<<"format: "<<format<<endl;

    return out;
}

class Menu {
private:
    static Menu* singleton;
    static int nrInstance;

    vector<Produs*> items;

    Menu() = default;
    Menu(const Menu& obj) = delete;
public:
    static Menu* getInstance() {
        nrInstance++;
        if(!singleton) singleton = new Menu();
        return singleton;
    }

    ~Menu() {
        nrInstance--;
        if(nrInstance == 0 && singleton) delete singleton;
    }

    void displayOptions();
    void engine();
};

int Menu::nrInstance = 0;
Menu* Menu::singleton = NULL;

void Menu::displayOptions() {
    cout<<"Optiuni:\n";
    cout<<"1. Citeeste produs\n";
    cout<<"2. Afiseaza produse\n";
    cout<<"3. Editeaza produs\n";
    cout<<"4. Ordoneaza produse dupa pret\n";
    cout<<"5. Cauta carte dupa titlu\n";
    cout<<"6. Afisare produs cea mai mare cantitate\n";
}

bool cmp(const Produs* ob1, const Produs* ob2) {
    return (ob1->getPret() < ob2->getPret());
}

void Menu::engine() {
    this->displayOptions();
    int option;
    while(true) {
        cout<<"introdu optiune: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 1: {
                Produs* p;
                cout<<"1. Carte\n";
                cout<<"2. Dvd film\n";
                cout<<"3. Dvd muzica\n";
                cout<<"4. Figurina\n";
                cout<<"5. Poster\n";

                int temp;
                cin>>temp;
                cin.get();
                if(temp == 1) p = new Carte();
                if(temp == 2) p = new Film();
                if(temp == 3) p = new Muzica();
                if(temp == 4) p = new Figurina();
                if(temp == 5) p = new Poster();

                try {
                    cin>>*p;
                }
                catch(const string& err) {
                    cout<<err;
                }
                this->items.push_back(p);

                this->displayOptions();
                break;
            }
            case 2: {
                for(int i=0;i<items.size();i++)
                {
                    cout<<"Item: "<<i<<endl;
                    cout<<*items[i]<<endl;
                }
                this->displayOptions();
                break;
            }
            case 3: {
                for(int i=0;i<items.size();i++)
                {
                    cout<<"Item: "<<i<<endl;
                    cout<<*items[i]<<endl;
                }
                cout<<"Alege item: \n";
                int temp;
                cin>>temp;
                cin.get();
                try {
                    if(temp < 0 || temp >= items.size()) throw temp;
                    cin>>*items[temp];
                }
                catch (const int& e) {
                    cout<<e<<" nu e index bun\n";
                }
                this->displayOptions();
                break;
            }
            case 4: {
                std::sort(items.begin(),items.end(),cmp);
                for(int i=0;i<items.size();i++)
                {
                    cout<<"Item: "<<i<<endl;
                    cout<<*items[i]<<endl;
                }
                this->displayOptions();
                break;
            }
            case 5: {
                cout<<"Introdu titlu: \n";
                string temp;
                cin>>temp;
                for(int i=0;i<items.size();i++)
                {
                    if(typeid(*items[i]) == typeid(Carte)) {
                        if(dynamic_cast<Carte*>(items[i])->getTitlu() == temp)
                            cout<<"Carte gasita:\n"<<*items[i]<<endl;
                    }
                }
                this->displayOptions();
                break;
            }
            case 6: {
                int mx = 0;
                Produs* temp = NULL;
                for(int i=0;i<items.size();i++)
                {
                    if(items[i]->getCantitate() > mx) {
                        mx = items[i]->getCantitate();
                        temp = items[i];
                    }
                }
                cout<<*temp<<endl;
                this->displayOptions();
                break;
            }
            default: cout<<"~ INVALID OPTION\n";
        }
    }
}

int main() {
    Menu* m = m->getInstance();
    m->engine();
    return 0;
}