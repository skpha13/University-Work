#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class pers
{
 const int cnp;
 char nume[10];
 char *  prenume;
static int nrp;
public:
pers(int c, char *p, char *n):cnp(c) //, nume(n) //nu este corect !!!!
  {prenume=new char[strlen(p)+1];
   strcpy(prenume,p);

   strcpy(nume,n);
   nrp++;
  }
~pers(){nrp--;}

int get_cnp() const {return cnp;} // nu pot modifica datele obiectului apelat
void set_nume(char *n){strcpy(nume,n);}
const char * get_nume()const {return nume;} // as putea modifica nume[0],nume[1],...
char * get_prenume()const {return prenume;} // pot modifica zona adresata de prenumele, nu pot adresa alta zona
};
int pers::nrp=0; // se poate da si alta valoare
int main()
{
 int nr,c;
 char n[10],p[10];
/* cin>>c>>n>>p;
  pers vp[2]={pers(c,p,n),pers(c,p,n)};
ar trebui apelat constructorul pentru toate obiectele la declarare
-se creaza toate odata nu doar cate sunt necesare*/
pers *vp[100];//pot avea mai multi pointeri din care folosesc doar cati sunt necesari
for(int i=0;i<nr;i++)
{cin>>c>>p>>n;
vp[i]=new pers(c,p,n);
}
return 0;
}




