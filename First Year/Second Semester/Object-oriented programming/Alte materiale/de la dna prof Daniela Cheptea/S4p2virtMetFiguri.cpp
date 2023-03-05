#include <cstdlib>
#include <iostream>
using namespace std;
class prisma
{protected:double h;
public: prisma(int ph){h=ph;}
virtual double arie()=0;
double volum(){return h*arie();}
};

class cilindru: public prisma
{double r;
public: cilindru(double ph,double pr):prisma(ph){r=pr;}
       double arie(){return 3.14*r*r;}
};

class ppd: public prisma /*paralelipiped dreptunghic*/
{double l,L;
public: ppd(double ph,double pl,double pL):prisma(ph){l=pl;L=pL;}
       double arie(){return l*L;}
};
class cub:public prisma
{public: cub(double ph):prisma(ph){};/* daca nu se apeleaza explicit constructorul bazei cu parametru, se va apela
                                        implicit constructorul bazei fara parametru*/
  double arie(){return h*h;}/* am nevoie de h deci necesar ca protected in prisma*/
};


int main(int argc, char *argv[])
{  cilindru c1(5,5);
 /* c1.arie(); functioneaza corect*/
 /* c1.volum(); nu va functiona corect*/

   prisma * vp[10]; /* colectie de adrese de prisme diferite*/
   vp[0]=new cilindru(5,5);
   vp[1]=new ppd(5,5,5);
   vp[2]=new cub(5);

   for (int i=0;i<3;i++) cout<<(vp[i]->arie())<<(vp[i]->volum());


    system("PAUSE");
    return 0;
}



