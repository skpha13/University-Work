#include <cstdlib>
#include <iostream>
using namespace std;
class prisma
{protected:double h;
public: prisma(int ph){h=ph;}
virtual double arie()=0;
double volum(){return h*arie();}
friend istream& operator >>(istream &i, prisma &p);
friend ostream& operator <<(ostream &o, const prisma &p);
virtual void citire(istream & i){i>>h;}
virtual void afisare(ostream &o)const {o<<h;}
};

class cilindru: public prisma
{double r;
public: cilindru(double ph,double pr):prisma(ph){r=pr;}
       double arie(){return 3.14*r*r;}
void citire(istream & i){prisma::citire(i); i>>r;}
virtual void afisare(ostream &o)const{prisma::afisare(o); o<<r;}
};

class ppd: public prisma /*paralelipiped dreptunghic*/
{double l,L;
public: ppd(double ph,double pl,double pL):prisma(ph){l=pl;L=pL;}
       double arie(){return l*L;}
void citire(istream & i){prisma::citire(i); i>>l>>L;}
virtual void afisare(ostream &o)const{prisma::afisare(o); o<<l<<L;}
};
class cub:public prisma
{public: cub(double ph):prisma(ph){};/* daca nu se apeleaza explicit constructorul bazei cu parametru, se va apela
                                        implicit constructorul bazei fara parametru*/
  double arie(){return h*h;}/* am nevoie de h deci necesar ca protected in prisma*/
/* nu e  nevoie sa redefinim metoda de citire(sau afisare)-exista cea din prisma care va fi apelata*/
};

istream& operator >>(istream &i, prisma &p)
{p.citire(i);
 return i;
}
ostream& operator <<(ostream &o,const prisma &p)
{p.afisare(o);
return o;
}
int main(int argc, char *argv[])
{
   prisma * vp[10]; /* colectie de adrese de prisme diferite*/
   vp[0]=new cilindru(5,5);
   vp[1]=new ppd(5,5,5);
   vp[2]=new cub(5);

   for (int i=0;i<3;i++) cout<<(vp[i]->arie())<<(vp[i]->volum());

   for(int i=0;i<3;i++) cin>>(*vp[i]);
   for(int i=0;i<3;i++) cout<<(*vp[i]);
    system("PAUSE");
    return 0;
}



