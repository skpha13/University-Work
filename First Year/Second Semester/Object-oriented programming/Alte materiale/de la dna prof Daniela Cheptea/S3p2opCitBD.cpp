
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

class B
{int a;
public: friend istream & operator >>(istream & i,B & ob);


};
class D: public B
{int c;
public: friend istream & operator >>(istream & i,D & d);

};

istream & operator >>(istream & i,B & ob)
{i>>ob.a; cout<<"B";return i;}

istream & operator >>(istream & i,D & d)
{ // i>>d.a; //este inaccesibil
    B &rb=d; i>>rb; // apelez operatorul pentru baza
    i>>((B&) d); // apelez operatorul pentru baza
    i>>d.c;
    cout<<"D"; return i;}

int main()
{
    D d;B b;
    cin>>b;cin>>d;
return 0;
}
