#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <fstream>

using namespace std;

class Persoana{
    const string CNP;
    string nume, tara;
public:
    Persoana(string cnp, string nume, string tara): CNP(cnp), nume(nume), tara(tara) {}

    friend ostream& operator<<(ostream& os, const Persoana& rsh){
         os <<"Nume: " << rsh.nume << " tara: " << rsh.tara << " cnp: " << rsh.CNP << endl;
         return os;
    }

    string  getCNP() const{
        return CNP;
    }
    string  getTara() const{
        return tara;
    }
    string  getNume() const{
        return nume;
    }
};

class Cifra : public exception{
public:
    const char* what() const throw(){
        return "nu sunt 13 cifre la cnp romanesc!";
    }
};

class PrimaCifra : public exception{
public:
    const char * what()const throw(){
        return "Prima cifra nu este 1,2,5,6!";
    }
};
class elev : public exception{
public:
    const char * what()const throw(){
        return "Nu este elev";
    }
};
class Februarie : public exception{
public:
    const char * what()const throw(){
        return "Februarie nu are zilele 30 si 31";
    }
};
class Litera : public exception{
public:
    const char * what()const throw(){
        return "Cnp-ul nu poate contine litere";
    }
};

int main()
{
    ifstream f("input.in");
    vector<shared_ptr<Persoana>> persoane, elevi;
    string cnp, nume, tara;
    int n = 6,i;
    for (i = 0; i < n; i++){
        f >> cnp >> nume >> tara;
        persoane.push_back(make_shared<Persoana>(cnp, nume, tara));
    }


    for(auto j = persoane.begin();j!= persoane.end();j++){
        auto p = *j;
        try{
            if(p->getTara() == "Romania")
            {
                if(p->getCNP().length() != 13)
                    throw Cifra();
                auto x = p->getCNP()[0];
                if(x!='1' && x!='2'&& x!='5' && x!='6')
                    throw PrimaCifra();

                int luna = int(p->getCNP()[3]-int('0'))*10+int(p->getCNP()[4]-int('0'));
                int zi = int(p->getCNP()[5]-int('0'))*10+int(p->getCNP()[6]-int('0'));
                if(luna == 2 && (zi == 30 || zi==31))throw Februarie();
                for(auto litera: p->getCNP()){
                    if(int(litera)<int('0') || int(litera) > int('9'))throw Litera();
                }
                int an = int(p->getCNP()[1]-int('0'))*10+int(p->getCNP()[2]-int('0'));
                if(23-an>18 || 23-an<6)
                    throw elev();
                else{
                    elevi.push_back(p);
                }


            }
        }/*catch(Cifra& obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }catch(PrimaCifra& obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }catch(elev& obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }
        catch(Februarie& obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }catch(Litera& obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }*/
        catch(exception &obj){
            cout << p->getNume()<<endl <<obj.what() << endl;
            persoane.erase(j);
            j--;
        }
    }
    for(auto elev: elevi)cout<<*elev<<'\n';
    return 0;
}
