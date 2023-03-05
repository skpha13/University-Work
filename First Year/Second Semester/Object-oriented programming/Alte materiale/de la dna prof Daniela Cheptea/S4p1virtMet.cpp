#include <cstdlib>
#include <iostream>
using namespace std;
class B
{
public:
       void fnv(){cout<<"B nevirttuala\n";} /* evaluare la compilare*/
       virtual void fv(){cout<<"B virtuala\n";}/*evaluare la executie-obiectul are un pointer suplimentar
                                                catre tabela cu metode virtuale*/
       void fB(){fnv();fv();} /* evaluare la compilare a fnv din B,  evaluare la executie a fv din D prin ponterul
                                suplimentar*/
};
class D: public B
{
public:
        void fnv(){cout<<"D nevirtuala\n";}
        void fv(){cout<<"D virtuala\n";}    //ramane virtuala daca are acelasi tip intors si aceiasi parametrii
        void fs(){cout<<"f suplimentara\n";}

};
void fGeneralaRef(B &rb) /* va putea fi apelata cu obiecte din B sau D*/
{rb.fnv();/* alege la compilare fnv din B*/
  rb.fv();/* alege la executie corespunzator clasei obiectului*/
}
void fGeneralaPtr(B *pb) /* va putea fi apelata cu adrese de obiecte din B sau D*/
{pb->fnv();/* alege la compilare fnv din B*/
  pb->fv();/* alege la executie corespunzator clasei obiectului*/
}
int main(int argc, char *argv[])
{B b1;
D d1;
d1.fnv();// evaluare la compilare alege fnv din D
d1.fv();// evaluare la executie alege fv din D

/* Apel prin pointer la baza */
B *pb=&d1; // in pointer la BAZA pot pune adresa unui obiect din DERIVATA
/* pb->fs();  pb nu vede decat membrii din clasa B -fs nu e vizibil prin  pointerul pb*/
pb->fnv(); /*alege la compilare fnv din B*/
pb->fv(); /* alege la executie fv din D*/

/* apel prin referinta la baza*/
B &rb=d1; /* referinta la BAZA poate referi un obiect din DERIVATA*/
/* rb.fs();  rb nu vede decat membrii din clasa B -fs nu e vizibil prin  referinta rb */
rb.fnv(); /*alege la compilare fnv din  B*/
rb.fv(); /* alege la executie fv din D*/


B *v[2];
v[0]=new B;
v[1]=new D ; /*pot avea  vector de pointeri la obiecte de tipuri diferite */
for(int i=0;i<2;i++)
{v[i]->fnv();  /*alege la compilare fnv din B */
 v[i]->fv();   /* alege la executie fv() din clasa corespunzatoare  obiectului (B sau D)*/
}

fGeneralaRef(b1); /* alege fv din B */
fGeneralaRef(d1);  /* alege fv din D */

fGeneralaPtr(&b1); /* alege fv din B */
fGeneralaPtr(&d1); /* alege fv din D */

/*Metoda din B are pointerul this = pointer la B */
d1.fB() ; // apeleaza fnv din B -evaluare la compilare dar fv din D -evaluare la executie
pb->fB(); /* alege la compilare fnv(din B), alege la  executie   fv (din D)*/
rb.fB(); /* alege la compilare fnv (din B), alege la  executie   fv (din D)*/

    return 0;
}
