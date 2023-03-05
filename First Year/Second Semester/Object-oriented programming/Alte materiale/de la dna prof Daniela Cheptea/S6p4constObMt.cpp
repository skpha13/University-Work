#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{ int n;
  public:

    /* -metoda e constanta cand const apare DUPA lista param
       -nu va putea modifica datele obiectului implicit
        -this e transmis ca pointer care protejeaza zona
    */
    C(int i){n=i;}
    C(){n=1;}
    int & fc1()const{/*return n;*/} /* prin referinta pot modifica zona protejata de this*/
    const int & fc2()const{/*n=1;*/ /*nu se pot modifica datele obiectului implicit-
									transmis prin this pointer care nu modifica zona*/
							C c1; c1.n=1;// poate modifica datele altui obiect
	                        return n;} // da- intoarce referinta care protejeaza zona
    void fnc(){static int s=0;s++; cout<<s<<endl;}// metoda neconstanta- nu poate fi apelata de obiecte const
    // variabila locala statica   -o singura zona de memorie  -in  segmentul de date -pt toate apelurile
    // initializare doar la primul apel  si pastreaza modificarile  variabilei

   // void fnc()const{}// pot avea ambele variante -nu e ambiguitate -obiectele neconst vor alege prioritar metode neconst
};


int main()
{
const C oc;
//oc.fnc(); //nu poate apela decat met const
oc.fc2();

C on,on1; // poate apela met const si neconst
on.fc2();
on.fnc();
on1.fnc();

const C *p; // prin pointer nu se poate modifica zona
 p=&on;
 p->fc2();
// p->fnc(); //prin pointer care nu modifica zona nu pot apela decat functii const

}

