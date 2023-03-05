#include <cstdlib>
#include <iostream>
using namespace std;
//Diferente C C++
 //***Tipul referinta
/*
int i;
int *pi,j;  //pi este adresa a unui intreg   !! j este doar intreg
int & ri=i; //ri este alt nume pentru variabila i

int main()
{pi=&i;  // pi este adresa variabilei i
 *pi=3;   //in zona adresata de pi se pune valoarea 3
} */

//***Transmmiterea parametrilor
/*
void f(int ii, int *pii, int &rii)   //pentru  variabilele : int x,y,z;- vom apela:   f(x,&y,z)   ;
{ ii++;    //pentru i se rezerva zona de memorie (pe stiva) si valoarea parametrului actual x se copiaza  in i
             // modificarile facute asupra variabilei i nu modifica parametrul actual x
(*pii)++;  // se modifica variabila adresata de pi deci parametrul actual y
            // pentru pii se rezerva zona de memorie si valoarea (&y) e copiata in pii
 rii++;       // ri este alt nume pentru parametrul actual z -orice modificare a referintei modifica parametrul actual
                // pentru rii nu se rezerva zona noua de memorie
}

 int main()
 {int x,y,z;
  x=y=z=0;
  f(x,&y,z) ;
 } */

//***Alocare dinamica
/*
int main()
{ int *pi;
 pi=new int;// aloca zona pentru un int si intoarce  in pi adresa zonei de memorie sau NULL
 delete pi; // elibereaza  zona adresata de pi -o considera neocupata
   pi=new int(2);// aloca zona si initializeaza zona cu valoarea 2
   pi=new int[2]; // aloca un vector de 2 elemente  de tip intreg
   delete [] pi; //elibereaza intreg vectorul
     //-pentru new se foloseste delete
     //- pentru new [] se foloseste delete []
} */


//*** Intoarcerea valorilor din functie

/*
int  gv(int ii, int *pii,int &rii)    // functie care intoarce  un intreg
{int vl;
 return  vl; //intoarce o valoare -pe stiva
 return ii; //intoarce o valoare
 return *pii; // intoarce o valoare
 return rii;// intoarce o valoare
 int *pl=new int;
 return *pl; // intoarce o valoare
}
int main()
{int x,y,z;
 gv(x,&y,z)=2;   // eroare nu pot pune valori intr-o zona temporala constanta
}
*/
/*
int & gr(int ii, int *pii,int &rii)    // functie care intoarce un alt nume pentru un intreg
{int vl;
 //return  vl; //warning-intoarce un alt nume catre o zona care va fi eliberata -valida sintactic dar va genera erori ulterior
 //return ii; //warning-intoarce un alt nume spre o zona care va fi eliberata-valida sintactic dar va genera  erori ulterior
 return *pii; // intoarce un alt nume pt zona adresata de pointerul pii (adreseaza zona prin adresa data de parametrul actual)
 return rii;// intoarce alt nume pentru zona variabilei rii (variabila ri este un alt nume pentru paramtrul actual corespunzator)
  int *pl=new int;
 return *pl; // intoarce alt nume pentru zona nou creata -ramane alocata pana se apeleaza delete
}
//putem  avea apelul:
int main()
{ int x,y,z;
  // gr(x,&y,z)=2; //intorcand un alt nume catre o zona de memorie - in zona respectiva pot atribui valoarea 2
   int &rf=gr(x,&y,z);
   //rf=2; cout<<y; // y=2
}*/

/*
int * gp(int ii,int *pii, int & rii) // functie care intoarce adresa unui intreg
{int vl;
 return &vl; //warning-intorc adresa unei zone care va fi eliberata
 return &ii;  //warning-intorc adresa unei zone care va fi eliberata
   return pii;
   int *pl=new int;
   return pl; //intoarce o adresa  a unei zone care ramine alocata pina la stegerea cu delete
   return &rii;  //intoarce adresa zonei corespunzatoare referintei respectiv a parametrului actual
// nu exista tipul de date adresa a unei referinte adica : int & *p;
}
//pot avea apelul:
  int main()
 { int x,y,z;
   *gp(x,&y,z)=2;
 }// in zona adresata de adresa  intoarsa de functie se pune valoarea 2
*/

//***Putem avea functii cu parametru implicit
/*
void f1(int i, int j=0){}
int main()
{ f1(1,2);   //avem j = 2
  f1(1);      //  avem j=0 (valoarea implicita)
} */

//Parametrii impliciti pot apare dupa specificarea celor ne-impliciti :
// void f2(int i=0,int j){} //gresit
// Putem avea mai multi parametrii cu valori implicite
/*void f3(int i,int j=0,int k=1){}
int main()
{ f3(2,3);// considera j=3  si k=1 valoarea implicita
}*/

//*** Polimorfism de compilare
// Pot exista mai multe functii cu acelasi nume dar numar  sau tip diferit de parametrii
//-trebuie ca la apel sa se poata alege o singura functie
//-se incearca intai potrivirea exacta,
//-daca nu se poate -se incearca prin conversie pas1.predefinite fara pierderi,
                                             // pas2. apoi predefinite cu pierderi,
                                              //pas3. apoi definite de utilizator
/*
void f3(int i,int j=0){}
void f3(int i){}
int main(){ f3(1);}// gresit- ambiguu -poate alege ambele variante
*/
/*
void f4(double d){cout<<"double";}
void f4(float f){cout <<"float";}
int main()
{f4 (3.5);//alege double -pt constante in virgula  mobila
 f4(3);   //gresit - ambigua -alege ambele variante
}
*/
/*
void f5(double d){cout<<"double";}
void f5(int d){cout<<"int";}
int main()
{float f;
 f5 ((float) 3.5);//face conversie intai fara pierderi spre double -nu e ambiguitate
 f5(f);
 char c;
 f5(c); // ar trebui sa dea ambiguitate dar este o conversie automata
}
*/
/*
void f6(int a){}
void f6(int& a){}
int main()
{ int b;
 f6(2);// nu da ambiguitate
 f6(b); //da ambiguitate
}
*/
//*** citire si scriere
/*
// operator este o functie care are ca nume un simbol (sau mai multe simboluri)
int main()
{int x,y,z;
   cin >>x; // citire(extragere) din fluxul cin in variabila x -sensul sagetii
            // este de fapt operatorul  >>(cin,x) care  intoarce fluxul (prin referinta ) cin din care s-a extras data x
   cin>>y>>z; //este de fapt  >>(>>(cin,y), z) -citeste y si z

cout<<x; // x este afisata(inserata) in fluxul cout     -sensul sagetii
	    //este de fapt operatorul  <<(cout, x ) -intoarce fluxul cout (prin referinta) in care s-a inserat x
cout<<y<<z; // este de fapt <<(<<(cout,y),z) -afiseaza y si z

} */

/* pointeri si referinte care nu modifica */
/*int f(){}
void fRef(int &r){}  // Nu poate apela constante si temporare (ex: rezultate intoarse de functii)
void fConstRef(const int & cr){} // Poate apela constante si temporare

int main(){
int i,j;
const int * cp;
cp=&i;
i=1;
// *cp=2;  se poate modifica i dar nu prin pointerul cp

const int & cr=i;
i=1;
//  rc=2; se poate modifica i dar nu prin cr

//pointer constant
int * const pc=&i;// necesar initializarea la declarare
*pc=1;
//  pc=&j; nu poate sa adreeze alta zona
int v[10]; // v este pointer constant
*v=1; // echivalent cu v[0]=1;
//  v=&j; nu poate sa adreseze alta zona

//  fRef(f()); referinta poate modifica zona -temporarul nu se poate modifica
 //   fRef(2); referinta poate modifica zona -constanta nu se poate modifica
 fConstRef(f());
 fConstRef(2);
}
*/
