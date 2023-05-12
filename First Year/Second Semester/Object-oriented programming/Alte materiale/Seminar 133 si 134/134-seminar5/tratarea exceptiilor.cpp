#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include <memory>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

class Elev{
    string grupa;
    string nume;
    //string nrMatricol;
public:
    string getGrupa()
    {
        return grupa;
    }
    string getNume()
    {
        return nume;
    }
    Elev(string grupa, string nume): grupa(grupa), nume(nume) {}

    friend ofstream& operator <<(ofstream &out, const Elev &elev){
        out<< elev.grupa << " " << elev.nume << endl;
        return out;
    }

};

class Cifra : public exception {
public:
    const char* what()
        {return "Nu e compozitia corecta pentru tipul de grupa\n";}
};

class litera : public exception {
public:
    const char* what()
        {return "Nu poate sa inceapa cu litera\n";}
};

class literaMica: public exception{
public:
    const char* what()
        {return "Numele nu poate sa inceapa cu litera mica\n";}
};

class caractere : public exception{
public:
    const char* what()
        {return "Numele poate avea doar litere\n";}
};

int main()
{
    int n;
    f >> n;  ///nr posibili studenti
    vector<shared_ptr<Elev>> Info, Mate, CTI;
    for (int i = 0; i < n; i++)
    {
        string x,y;
        f>>x>>y;
        try{
            if(x[0]!='1')
                throw Cifra();
            if(!(x[1]=='0' || x[1]=='3' || x[1]=='4' || x[1]=='5' || x[1]=='6'))
                throw Cifra();
            if(x.length()!=3)
                throw Cifra();
            if(!(x[0]<='9' && x[0]>='0'))
                throw litera();
            if(y[0]<='z' && y[0]>='a')
                throw literaMica();
            for (int k=1; k < y.length(); k++)
                if(!(y[k]<='z' && y[k]>='a'))
                    throw caractere();
        }
        catch(Cifra &obj){
            g << obj.what();
            continue;
        }
        catch(litera &obj){
            g << obj.what();
            continue;
        }
        catch(literaMica &obj){
            g << obj.what();
            continue;
        }
        catch(caractere &obj){
            g << obj.what();
            continue;
        }
        if(x[1] == '0')
            Mate.push_back(make_shared<Elev>(x,y));
        if(x[1] == '3' || x[1] == '4' || x[1] == '5')
            Info.push_back(make_shared<Elev>(x,y));
        if(x[1] == '6')
            CTI.push_back(make_shared<Elev>(x,y));

    }
    for (auto j: Mate) g<<*j<<'\n';
    for (auto j: Info) g<<*j<<'\n';
    for (auto j: CTI) g<<*j<<'\n';
    return 0;
}
