/***
candidatii au nume, serie buletin

300 locuri la Info IF, 100 locuri la CTI, 150 locuri la Mate si 75 locuri la Info ID
- La Mate - 2 subiecte de mate
- La Info - 1 subiect mate si 1 subiect info
- LA CTI - 1 subiect fizica si 1 subiect mate
- la Info ID - INTERVIU

Media = 80%examen + 20%bac (IF)
Media ID = 60% interviu + 40%bac

nr de inregistrare candidat, creste automat si exista un cod, de forma Mate_x, Info_IF_x, CTI_x sau ID_x trecut pentru fiecare dosar
un candidat poate depune dosar de inscriere la toate cele 4 forme de invatamant / sectiuni de admitere

se cere:
- exportul listelor de inscriere, in ordinea completarii dosarelor
- listele de inscrisi - pe fiecare sectiune in parte
- listele de admisi pe fiecare sectiune
- a afiaa toti candidatii care s-au inscris la ambele forme de invatamant (IF si ID) si au fost declarati admisi macar la una
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Domeniu{
protected:
    string cod;
    float bac;
    string nume, CI;
    static int dosar;
public:
    Domeniu(){dosar++;}
    virtual void citire() = 0;
    virtual void afisare() = 0;
    virtual float medie() = 0;
};
    int Domeniu::dosar = 1;

class IF : public Domeniu
{
protected:
    float mate;
public:
    void citire();
    void afisare();
};

class Mate: public IF{
protected:
    float mate2;
public:
    Mate(){cod = "Mate_" + to_string(dosar);}
    void citire();
    void afisare();
    float medie();
};

class Info: public IF{
protected:
    float info;
public:
    Info(){cod = "Info_IF_" + to_string(dosar);}
    void citire();
    void afisare();
    float medie();
};

class CTI: public IF{
protected:
    float fizica;
public:
    CTI(){cod = "CTI_" + to_string(dosar);}
    void citire();
    void afisare();
    float medie();
};

class ID: public Domeniu{
protected:
    float interviu;
public:
    ID(){cod = "ID_" + to_string(dosar);}
    void citire();
    void afisare();
    float medie();
};

void Domeniu::citire(){cout<<"Nume / CI/ nota bacalaureat "; cin>>nume>>CI>>bac;}
void IF::citire(){Domeniu::citire(); cout<<"nota subiect mate1: "; cin>>mate;}
void ID::citire(){Domeniu::citire(); cout<<"nota interviu: "; cin>>interviu;}
void Mate::citire(){IF::citire(); cout<<"nota subiect mate2: "; cin>>mate2;}
void Info::citire(){IF::citire(); cout<<"nota subiect info: "; cin>>info;}
void CTI::citire(){IF::citire(); cout<<"nota subiect fizica: "; cin>>fizica;}

void Domeniu::afisare(){cout<<"Numar dosar "<<cod<<" Nume "<<nume <<" CI "<<CI<<" nota bacalaureat "<<bac<<" "<<" media de admitere: "<<medie()<<" ";}
void IF::afisare(){Domeniu::afisare();cout<<"nota mate1 "<<mate<<endl;}
void ID::afisare(){Domeniu::afisare();cout<<"nota interviu "<<interviu<<endl;}
void Mate::afisare(){IF::afisare();cout<<"nota mate2 "<<mate2<<endl;}
void Info::afisare(){IF::afisare();cout<<"nota info "<<info<<endl;}
void CTI::afisare(){IF::afisare();cout<<"nota fizica "<<fizica<<endl;}

float Mate::medie(){return 0.8 * ((mate + mate2)/2) + 0.2 * bac;}
float Info::medie(){return 0.8 * ((mate + info)/2) + 0.2 * bac;}
float CTI::medie(){return 0.8 * ((mate + fizica)/2) + 0.2 * bac;}
float ID::medie(){return 0.6 * interviu + 0.4 * bac;}


int comp(Mate& a, Mate& b)
{
    return a.medie() >= b.medie();
}

int main()
{
    vector<Domeniu*> v;
    int inscriere = 1;
    while (inscriere)
    {
        int optiune;
        cin>>optiune;

        switch(optiune)
        {
            case 1:{v.push_back(new Mate()); break;}
            case 2:{v.push_back(new Info()); break;}
            case 3:{v.push_back(new CTI()); break;}
            case 4:{v.push_back(new ID()); break;}
        }

        v.back()->citire();

        cout<<"alta inscriere? da = 1, nu = 0 "; cin>>inscriere;
    }

    for(auto p = v.begin(); p != v.end(); p++)
        (*p)->afisare();

cout<<endl;
/*******************************************/
    vector<Mate> v1;
    vector<Info> v2;
    vector<CTI> v3;
    vector<ID> v4;

        for(auto p = v.begin(); p != v.end(); p++)
        if (typeid(**p) == typeid(Mate)) v1.push_back(*dynamic_cast<Mate*>(*p));   /// avem doar candidati la Mate
    else if (typeid(**p) == typeid(Info)) v2.push_back(*dynamic_cast<Info*>(*p)); /// doar la Info IF
    else if (typeid(**p) == typeid(CTI)) v3.push_back(*dynamic_cast<CTI*>(*p)); /// doar la CTI
    else if (typeid(**p) == typeid(ID)) v4.push_back(*dynamic_cast<ID*>(*p)); /// doar la ID

    cout<<"Numar inscrisi la mate: "<<v1.size()<<endl;
    for(auto p = v1.begin(); p != v1.end(); p++)
        (*p).afisare();

    cout<<"Numar inscrisi la info IF: "<<v2.size()<<endl;
    for(auto p = v2.begin(); p != v2.end(); p++)
        (*p).afisare();

    cout<<"Numar inscrisi la cti: "<<v3.size()<<endl;
    for(auto p = v3.begin(); p != v3.end(); p++)
        (*p).afisare();

    cout<<"Numar inscrisi la ID: "<<v4.size()<<endl;
    for(auto p = v4.begin(); p != v4.end(); p++)
        (*p).afisare();


        sort(v1.begin(), v1.end(),comp);

    cout<<"Numar inscrisi la mate: "<<v1.size()<<endl;
    for(auto p = v1.begin(); p != v1.end(); p++)
        (*p).afisare();


    /*
    vector<int> v;
    v.push_back(1234);
    auto p = v.begin();
    ///cout<<typeid(p).name();
    cout<<*p;
    */

    return 0;
}
