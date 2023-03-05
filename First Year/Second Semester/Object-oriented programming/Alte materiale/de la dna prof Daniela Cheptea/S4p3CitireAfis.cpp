
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
// Citire si scriere pentru ierarhie de clase cu metode virtuale
/* Se poate declara  doar operatorul >> pt baza*/
/* !!friendul apeleaza baza pe care o vede desi se executa derivata la care nu ar avea  acces!! */
class B
{
friend istream & operator >>(istream & i,B& ob);
protected:
virtual void citire(istream & i){cout<<"citeste B"<<endl;}
virtual void afisare(ostream &o){}

};
class D: public B
{
void citire(istream &i)
{ cout<<"incep citire D ";
    B::citire(i);  
  cout<<"sfarsit citire D"<<endl;
}
};

istream & operator >>(istream & i,B& ob)
{ob.citire(i);return i;}

int main()
{
    D d;B b;
    ifstream f("t.txt");
	cin>>b;
	cin>>d;
	f>>d; /* pentru ca ifstream deriva din istream*/
return 0;
}
