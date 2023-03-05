#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
class lista
{   int *v;
    int max;
 protected: int n;
 public:
    lista(){int d=10; max=d; n=0; v=new int[max]; cout<<"li ";}
    lista(int d){max=d; n=0; v=new int[max]; cout<<"liP ";}
    lista(const lista & l){max= l.max; n=l.n; v= new int[max];
                           for(int i; i<n;i++) v[i]=l.v[i]; cout<<"lc ";
                           }
    lista operator =(lista l){delete []v;
                              max= l.max; n=l.n; v= new int[max];
                              for(int i; i<n;i++) v[i]=l.v[i];
                           }
   bool inserare(int val, int pos)
    {if (pos<0|| pos>n) return 0;
     if(n+1>max) return 0;
     for(int i=n-1;i>pos;i--){ v[i]=v[i-1];}
     v[pos]=val;
     return 1;
    }
};
class stiva: lista
{public:
   bool push(int val){return inserare(val,n);}
};
class coadaI: protected lista
{public:
   bool inserare(int val){return lista::inserare(val,n);}
};
class coadaE: protected lista
{   int f,r;
 public:
    coadaE(){f=r=-1; cout<<"ci ";}
    coadaE(int d):lista(d){f=r=-1; cout<<"ciP ";}
    coadaE(const coadaE & c):lista(c){f=c.f; r=c.r;cout<<"cc ";}
    bool inserare(int val){}
};
int main()
{lista l1;
coadaI c1;
coadaE c2, c3(3),c4(c2);
}

