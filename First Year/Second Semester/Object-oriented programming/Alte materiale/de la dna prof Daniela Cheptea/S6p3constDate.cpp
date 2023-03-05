#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{public:
    int nc;
    const int ct; /* se initializeaza doar in lista de initializare a construct si nu se mai modifica ulterior
                 pt fiecare obiect poate avea o alta valoare primita la initializare prin param constructorului*/
    C(int p=0):ct(p),nc(p){nc=p;
	                    /*ct=p;*/ // nu se mai poate modifica -se apeleaza operatorul= nu pseudoconstructorul
	                     };
	C():ct(1){} // c nu se mai modifica
	C(C &o):ct(o.ct),nc(o.nc){nc=o.nc;}
    int f1(){return ct;} // da - intorc o copie
    int & f2(){return nc; /* return c;*/}//nu -pot modifica campul const prin ref
    const int & f3(){return ct;} // referinta care protejeaza zona
    int * f4(){return &nc; /* return &c; */}// nu -pot modifica const prin adresa
    const int * f5(){ return &ct; }// pointer care protejeaza zona
};

int main()
{

}

