#include <cstdlib>
#include <iostream>
using namespace std;
struct complex
{float re,im;
 } a,b;
complex c;

// complex este tip de date
// a,b,c sunt variabile de tipul complex
// accesul la cimpuri -implicit este public-din orice punct al programului ex: a.re=2;a.im=2;

class Complex
{
  float re,im;
public: void afisare();
} A,B;
Complex C;

/*Complex este un tip de date
  A,B,C sunt variabile de tipul Complex -se numesc obiecte sau instante ale clasei Complex
  cimpurile: re,im  se numesc date
  functiile:  afisare() se numesc metode
  datele si metodele sunt membrii ai clasei
  implicit specificatorul de acces la membrii este private
  private= am acces la membrii privati (ai tuturor obiectelor clasei) doar intr-o metoda a clasei
  public = am acces la membrii publici ai clasei din orice punct al programului.



 metoda afisare() poate fi apelata doar de catre un obiect =obiectul implicit
 exemplu:  A.afisare();-obiectul implicit este A
 exemplu:  B.afisare();-obiectul implicit este B

 this este adresa obiectului  care apeleaza metoda-existent in orice metoda nestatica
 * this este chiar obiectul care apeleaza metoda
 exemplu pt A.afisare() ; this este adresa lui A ; * this  este chiar A
            B.afisare() ; this este &B ; * this  este chiar B

 pot accesa datele si metodele obiectului care apeleaza metoda
 (*this).im=0;    sau
  this->im=0 ;    sau
  im=0;

 poate exista o alta clasa cu acelasi nume de metoda : class Clasa1{void afisare();};

 diferentiem  cele doua metode la definire specificand numele clasei:
  void Clasa1::afisare(){} */
  void Complex :: afisare()
{ cout<<im;  // data im a obiectului care apeleaza metoda -echivalent cu :
cout<<(*this).im;//echivalent cu
cout<< this->im;
 Complex D;
 D.im=0; // din  metoda clasei  pot accesa datele private ale TUTUROR obiectelor
}

int main()
{ A.afisare();
  B.afisare();
}


