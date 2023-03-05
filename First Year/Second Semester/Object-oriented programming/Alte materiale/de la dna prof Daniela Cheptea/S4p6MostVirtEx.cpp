#include <iostream>
#include <cstring>
/* La mostenire virtuala in clasa  ce mosteneste o singura data clasa de baza , tranmite ea contructorului bazei parametru,
celelalte apeluri ale bazei sunt ignorate
La fel operatorul de citire-afisare -trebuie sa apeleze o singura data operatorul din baza , celelalte date
fiind necesare sa fie  protected pt a fi accesate*/
// Da nastere la diverse probleme!!!
using namespace std;
class persoana
{char nume[10];
    public:
      persoana(char * pn=""){strcpy(nume,pn);}
    friend ostream & operator <<(ostream & o, const persoana & p) ;
    /* pentru a putea afisa si temporare sau constante*/
    virtual void afisare(ostream &o) const{o<<nume;}
};
ostream & operator <<(ostream & o, const persoana & p){p.afisare(o);return o;}

class student: virtual public persoana
{ protected: int an;
    public:
 student(char * pn="", int pa=0): persoana(pn),an(pa){}
  void afisare(ostream &o) const{persoana::afisare(o); o<<an;}
};

class angajat: virtual public persoana
{protected: int salariu;
    public: angajat(char *pn="", int ps=0):persoana(pn),salariu(ps){}
   void afisare(ostream &o) const{persoana::afisare(o); o<<salariu;}
};
class student_angajat: public student, public angajat
{public : student_angajat(char * pn="", int pa=0, int ps=0): persoana(pn),student(pn,pa),angajat(pn,ps){}
/* nu e corect sa se apeleze de doua ori constructorul pt persoana,
 se apeleaza o sg data cu parametrul transmis din student_angajat -ignora celelalte apeluri*/
  void afisare(ostream &o) const{persoana::afisare(o); o<<an<<salariu;}
};


int main()
{ student_angajat sa("ion",2, 1000);
  cout<<sa;
    return 0;

}
