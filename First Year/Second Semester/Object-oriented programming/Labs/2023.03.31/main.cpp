#include <iostream>
#include <vector>

using namespace std;

class Ingredient {
private:
    string nume;
    float pret;

public:
    Ingredient(string nume ,float pret);
    Ingredient(const Ingredient &obj);
    Ingredient &operator=(const Ingredient &obj);
    friend istream& operator>>(istream &in, Ingredient &obj);
    friend ostream& operator<<(ostream &out,const Ingredient &obj);
};


Ingredient::Ingredient(string nume = " ", float pret = 0.0)
{
    this->nume = nume;
    this->pret = pret;
}

Ingredient::Ingredient(const Ingredient &obj)
{
    this->nume = obj.nume;
    this->pret = obj.pret;
}

Ingredient& Ingredient::operator=(const Ingredient &obj)
{
    if(this != &obj)
    {
        this->nume = obj.nume;
        this->pret = obj.pret;
    }
    return *this;
}

istream& operator>>(istream &in,Ingredient &obj)
{
    cout<<"Nume:\n";
    in>>obj.nume;
    cout<<"Pret:\n";
    in>>obj.pret;
    return in;
}

ostream& operator<<(ostream &out,const Ingredient &obj)
{
    out<<"Nume: "<<obj.nume<<endl;
    out<<"Pret: "<<obj.pret<<endl;
    return out;
}

class Bautura {
    protected:
    string nume;
    vector<Ingredient> listaIngredient;
    float volum;

public:
    Bautura();
    Bautura(string nume, vector<Ingredient> listaIngredient,float volum);
    Bautura(const Bautura &obj);
    Bautura& operator=(const Bautura &obj);
    friend ostream& operator<<(ostream &out,const Bautura &obj);
    friend istream& operator>>(istream &in,Bautura &obj);
};

Bautura::Bautura()
{
    this->nume = "Anonim";
    this->listaIngredient = {};
    this->volum = 0;
}

Bautura::Bautura(string nume, vector<Ingredient> listaIngredient,float volum)
{
    this->nume = nume;
    this->listaIngredient = listaIngredient;
    this->volum = volum;
}

Bautura::Bautura(const Bautura &obj)
{
    this->nume = obj.nume;
    this->listaIngredient = obj.listaIngredient;
    this->volum = obj.volum;
}

Bautura& Bautura::operator=(const Bautura &obj)
{
    if(this != &obj)
    {
        this->nume = obj.nume;
        this->listaIngredient = obj.listaIngredient;
        this->volum = obj.volum;
    }
    return *this;
}

ostream& operator<<(ostream &out,const Bautura &obj)
{
    out<<"Nume: "<<obj.nume<<endl;
    out<<"Ingredientele sunt: "<<endl;
    for(int i=0;i<obj.listaIngredient.size();i++)
        out<<obj.listaIngredient[i]<<endl; //avem deja supraincarcat operator de afisare la ingredient
    out<<"Volum: "<<obj.volum<<endl;
    return out;
}

istream& operator>>(istream &in,Bautura &obj)
{
    cout<<"Introdu nume: \n";
    in>>obj.nume;
    if(!obj.listaIngredient.empty())
        obj.listaIngredient.clear();
    while(true)
    {
        cout<<"\nIntrodu 1 pentru a adauga un ingredient\n2 pentru a te opri\n";
        int k;
        cin>>k;
        if(k==1) {
            Ingredient i;
            cin>>i;
            obj.listaIngredient.push_back(i);
        }
        else break;
    }
    cout<<"Introdu volum:\n";
    in>>obj.volum;
    return in;
}

class BauturaAlcoolica:public Bautura {
private:
    float alcoolemie;
public:
    BauturaAlcoolica():Bautura()
    {

        this->alcoolemie = 0;
    }
    BauturaAlcoolica(string nume, vector<Ingredient> listaIngredient,float volum,float alcoolemie):
        Bautura(nume,listaIngredient,volum)
    {
        this->alcoolemie = alcoolemie;
    }
    BauturaAlcoolica(const BauturaAlcoolica &obj):
        Bautura(obj)
    {
        this->alcoolemie = obj.alcoolemie;
    }
    BauturaAlcoolica& operator=(const BauturaAlcoolica &obj)
    {
        if(this != &obj)
        {
            // apelam noi separat operatorul egal pentru partea
            // de Bautura din BauturiAlcoolice
            Bautura::operator=(obj);
            this->alcoolemie = obj.alcoolemie;
        }
        return *this;
    }
    friend istream& operator>>(istream &in,BauturaAlcoolica &obj)
    {
        // daca incercam (fara cast) se va duce in bautura
        // va vedea ca nu e alcoolemie se va duce in BauturaAlcoolica
        // si se va cicla asa infinit
        in>>(Bautura&)obj;
        cout<<"Alcoolemie: \n";
        in>>obj.alcoolemie;
        return in;
    }
    friend ostream& operator<<(ostream &out,const BauturaAlcoolica &obj)
    {
        // daca incercam (fara cast) se va duce in bautura
        // va vedea ca nu e alcoolemie se va duce in BauturaAlcoolica
        // si se va cicla asa infinit
        out<<(Bautura&)obj;
        out<<"Alcoolemie: "<<obj.alcoolemie<<endl;
        return out;
    }
};

int main()
{
    BauturaAlcoolica b;
    cin>>b;
    cout<<b<<endl;
    return 0;
}
