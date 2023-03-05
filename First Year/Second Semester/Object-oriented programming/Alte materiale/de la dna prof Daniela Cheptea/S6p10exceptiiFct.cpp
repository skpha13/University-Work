#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class Test{} ob;
void f()
{int i;
 cin>>i;
 if (i) throw ob;
  cout<<"dupa if"; // nu se mai executa daca se arunca exceptia
 return;
}

int main()
{
try{
    f();
    cout<<"dupa f"; // nu se mai executa daca se arunca exceptia
   }
catch(double a){cout<<"D catch "<<a;} // nu face conversie
catch(int a){cout<<"I catch "<<a;}
catch(...){cout<<" toate tipurile";}
 cout<<"dupa catch" ; // dupa tratare sau daca nu s-a aruncat exceptia

}
