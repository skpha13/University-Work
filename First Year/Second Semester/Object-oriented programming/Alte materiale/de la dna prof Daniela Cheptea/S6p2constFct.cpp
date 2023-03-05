#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

void f(const int i){/*i=1;*/} // nu pot modifica parametrul formal - copia parametrului actual -

void f1(int i){i=1;} // modifica copia parametrului actual

void f2(int *pi){*pi=1;}// modifica variabila adresata de parametrul actual
void f3(const int *pi){}// pi protejeaza zona (zona adrsata de param actual nemodificata)
void f4(int &ri){ri=1;} // modific zona parametrului actual prin parametrul formal (alt nume pentru zona parametrului actual)
void f5(const int &ri){}// ri protejeaza zona (parametrul actual nu se modifica)

int f6(){return 2;}
int & f7(){int *p=new int (2); return *p;
//const int & rlc=*p;return rlc; /* nu- prin referinta care nu protejeaza zona, pot modifica zona protejata*/
}
const int & f8(){int *p=new int (2); return *p;} /* corect -nu pot modifica zona intoarsa*/

void f(int *pi){cout<<"pointer"<<endl;}
void f(const int *pi){cout<<"pointer spre const"<<endl;}
/* NU e ambiguitate !! daca lipseste f(int*)  se face conversie de la int * la const int *
  (invers nu) */
int main()
{
const int c=1;
int i;
int *p;
//p=&c;//nu e corect -poate modifica constanta
const int * pc;

//f4(c); //nu - initializez referinta cu o constanta -o pot modifica
f5(c);// da -initializez referinta constanta cu o constanta -nu pot modifica
//f6()=2;//nu se poate modifica temporarul
f7()=2;
//f8()=2;// nu se poate modifica prin referinta zona constanta
f(p);
f(pc);

}

