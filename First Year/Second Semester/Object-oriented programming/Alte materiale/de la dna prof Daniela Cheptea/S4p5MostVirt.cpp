#include <iostream>
#include <cstring>
/* La mostenire virtuala in clasa D nu se mai transmit parametrii din clasele B si C
 constructorului clasei A ci doar explicit din D */
using namespace std;
class A
{public: A(int i=0){cout<<"A"<<i<<" "<<endl;}   };

class B: virtual public A
{public: B():A(1){};   };

class C: virtual public A
{public: C():A(2){}  };

class E{public: E(){cout<<"E"<<endl;}};

class D:public E,public B,public C
{/*public : D():A(3){} */ };  // ar fi contradictie intre apelul prin B si cel prin C
/* Se poate transmite explicit parametrul pentru constructorul lui A ; Daca nu - se va apela cel implicit
Constructorul clasei mostenite virtual se va apela primul , chiar si inaintea celui din E */
int main()
{ D d;
    return 0;

}
