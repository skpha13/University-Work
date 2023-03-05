#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{static  int s;
 int ns;
public:
C(){s=-1;}
void fns(){ns=2; (*this).ns=2; s=2; (*this).s=2;C::s=2;}
static void fs(){ // nu exista this
    //ns=1; // nu avem obiect pt ns -nu exista this
    // fns(); // nu am obiect care sa apeleze fns()-nu exista this
    //ns este (*this).ns ; fns() este (*this).f()
                    cout<<s<<C::s<<endl;
                    C oc; oc.ns=-1; // pot accesa datele nestatice ale unui Obiect al clasei
                }

 } o1;

//int C::s;// trebuie redeclarat pt a aloca zona de memorie
            //daca nu se initializeaza are val 0 (ca variabilele globale)
            // se aloca inainte de creerea obiectelor- chiar si inainte de o1
int C::s=1;// la declarare se poate si initializa desi nu este accesibil !!


int main()
{C::fs();
 C o2;
 o2.fs();
//C::s=2; eroare data privata -nu este accesibila
}
// datele stice =date comune tuturor obiectelor analog variabilelor globale
// datele statice sunt protejate si sunt incapsulate in clasa -preferabile variabilelor globale
// pot avea date statice si const initializate sau la declarare sau la redefinire- rol de constanta a clasei
// o singura zona de memorie pentru toate obiectele clasei si ale claselor derivate
