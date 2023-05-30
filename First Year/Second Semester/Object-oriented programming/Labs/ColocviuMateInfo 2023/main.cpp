#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class IOInterface {
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class Programator {
private:
    string nume,tip;
    int experienta;
public:
    Programator():nume("Noname"),tip("Clasic"),experienta(0){}
    Programator(const Programator& obj);
    Programator& operator=(const Programator& obj);

    friend istream& operator>>(istream& in, Programator& obj);
    friend ostream& operator<<(ostream& out, const Programator& obj);

    int getExperienta(){return this->experienta;}
    const string getName() const {return this->nume;}
};

Programator::Programator(const Programator &obj) {
    this->nume = obj.nume;
    this->tip = obj.tip;
    this->experienta = obj.experienta;
}

Programator& Programator::operator=(const Programator &obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->tip = obj.tip;
        this->experienta = obj.experienta;
    }
    return *this;
}

istream& operator>>(istream& in, Programator& obj) {
    cout<<"Nume: \n";
    in>>obj.nume;
    cout<<"Tip: \n";
    in>>obj.tip;
    cout<<"Ani exp: \n";
    in>>obj.experienta;

    return in;
}

ostream& operator<<(ostream& out, const Programator& obj) {
    cout<<"Nume: "<<obj.nume<<endl;
    cout<<"Tip: "<<obj.tip<<endl;
    cout<<"Ani exp: "<<obj.experienta<<endl;

    return out;
}

class WorkItems: public IOInterface{
protected:
    const int ID;
    static int contor;
    string data,area,status;
    int timp;
    Programator p;
public:
    WorkItems():ID(contor++),status("open") {}

    friend istream& operator>>(istream& in, WorkItems& obj);
    friend ostream& operator<<(ostream& out, const WorkItems& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    virtual float cost() = 0;
    int getID() const {return this->ID;}
    const string getStatus() const {return this->status;}
    void setStatus(const string& status) {this->status = status;}
    void setTimp(int timp) {this->timp = timp;}
    void assign(const Programator& p) {
        this->p = p;
        this->status = "InProgress";
    }
};

int WorkItems::contor = 0;

istream& operator>>(istream& in, WorkItems& obj) {
    return(obj.citire(in));
}

ostream & operator<<(ostream & out,const WorkItems& obj) {
    return(obj.afisare(out));
}

istream& WorkItems::citire(std::istream &in) {
    cout<<"Data: \n";
    in>>data;
    cout<<"Area: \n";
    in>>area;
    return in;
}

ostream & WorkItems::afisare(std::ostream &out) const {
    cout<<"Data: "<<data<<endl;
    cout<<"Area: "<<area<<endl;
    cout<<"Status: "<<status<<endl;
    cout<<"Timp: "<<timp<<endl;
    cout<<"Programator: \n";
    cout<<p;
    return out;
}

class Bug:public WorkItems {
private:
    int impactBug;
    string startWork;
public:
    Bug():WorkItems() {};

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    float cost();
    int getImpactBug() {return impactBug;}
};

float Bug::cost() {
    return impactBug * 10 + timp*5;
}

istream& Bug::citire(std::istream &in) {
    this->WorkItems::citire(in);
    cout<<"Impact bug:\n";
    in>>impactBug;
    return in;
}

ostream & Bug::afisare(std::ostream &out) const {
    this->WorkItems::afisare(out);
    cout<<"Impact bug: "<<impactBug<<endl;
    cout<<"Start work: "<<startWork<<endl;
    return out;
}

class Change:public WorkItems {
private:
    string descriere,dataLansare;
public:
    Change():WorkItems() {};

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    float cost();
};

float Change::cost() {
    return timp * 18.4;
}

istream& Change::citire(std::istream &in) {
    this->WorkItems::citire(in);
    cout<<"Descriere:\n";
    in>>descriere;
    cout<<"Data lansare:\n";
    in>>dataLansare;
    return in;
}

ostream & Change::afisare(std::ostream &out) const {
    this->WorkItems::afisare(out);
    cout<<"Descriere: "<<descriere<<endl;
    cout<<"Data lansare: "<<dataLansare<<endl;
    return out;
}

class Menu {
private:
    Menu() = default;
    Menu(const Menu& obj) = delete;
    ~Menu();

    vector<Programator> p;
    vector<WorkItems*> w;
public:
    static Menu& getInstance();
    void display();
    void engine();
};

Menu::~Menu() {
    if(!p.empty()) p.clear();
    if(!w.empty()) {
        for(int i=0;i<w.size();i++) {
            delete w[i];
        }
        w.clear();
    }
}

Menu& Menu::getInstance() {
    static Menu instance;
    return instance;
}

void Menu::display() {
    cout<<"---OPTIUNI---\n";
    cout<<"1. WorkItems\n";
    cout<<"2. Programator\n";
    cout<<"3. Asignare\n";
    cout<<"4. Afisare WorkItems\n";
    cout<<"5. Afisare programatori\n";
    cout<<"6. Afisare venit prog\n";
}

void Menu::engine() {
    this->display();
    while(true) {
        int option;
        cin>>option;
        switch (option) {
            case 1: {
                WorkItems* temp;
                cout<<"1. Bug\n";
                cout<<"2. Change\n";
                int opt;
                cin>>opt;
                if(opt == 1) temp = new Bug();
                if(opt == 2) temp = new Change();

                cin>>*temp;
                w.push_back(temp);
                this->display();
                break;
            }
            case 2: {
                Programator temp;
                cin>>temp;
                p.push_back(temp);
                this->display();
                break;
            }
            case 3: {
                for(int i=0;i<w.size();i++) {
                    cout<<*w[i]<<endl;
                }
                int id;
                cout<<"Workitem id: \n";
                cin>>id;

                for(int i=0;i<p.size();i++) {
                    cout<<p[i]<<endl;
                }

                string nume;
                cout<<"Programmers name: \n";
                cin>>nume;
                Programator copiat;
                for(int i=0;i<p.size();i++)
                    if(p[i].getName() == nume)
                        copiat = p[i];

                WorkItems* toChange;
                for(int i=0;i<w.size();i++) {
                    if(w[i]->getID() == id && w[i]->getStatus()!="Closed")
                    {
                        if(typeid(*w[i]) == typeid(Bug) && dynamic_cast<Bug&>(*w[i]).getImpactBug() > 5 && copiat.getExperienta() > 2) {
                            w[i]->assign(copiat);
                        }
                        else if(copiat.getExperienta() < 2) {
                            w[i]->assign(copiat);
                        }
                        int timprez;
                        cout<<"timp rez: \n";
                        cin>>timprez;
                        w[i]->setTimp(timprez);
                    }
                }
                this->display();
                break;
            }
            case 4: {
                for(int i=0;i<w.size();i++) {
                    cout<<*w[i]<<endl;
                }
                this->display();
                break;
            }
            case 5: {
                for(int i=0;i<p.size();i++) {
                    cout<<p[i]<<endl;
                }
                this->display();
                break;
            }
            case 6: {
                string nume;
                cout<<"Nume:\n";
                cin>>nume;
                for(int i=0;i<p.size();i++) {
                    if (p[i].getName() == nume) {
                        int venit = 0;
                        for (int j = 0; j < w.size(); j++)
                            venit += w[j]->cost();
                        cout<<venit<<endl;
                        break;
                    }
                }
                this->display();
                break;
            }
            default: cout<<"not an option\n";
        }
    }
}

int main() {
    Menu& m = Menu::getInstance();
    m.engine();
    return 0;
}
