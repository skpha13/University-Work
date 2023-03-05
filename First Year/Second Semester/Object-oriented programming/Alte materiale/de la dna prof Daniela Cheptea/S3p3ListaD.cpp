#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
class lista
{protected:
    int *v;
    int max;
    int n;
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
   stiva(int d=10): lista(d){}
   bool push(int val){return inserare(val,n);}
};
class coadaI: protected lista
{public:
    coadaI(int d=10):lista(d){}
   bool inserare(int val){return lista::inserare(val,n);}
};
class coadaE: protected lista
{   int f,r;
 public:
    coadaE(int d=10):lista(d){f=r=-1; cout<<"ciP ";}
    bool inserare(int val){}
};
class coadaEP: protected lista
{   int *pf,*pr;
 public:
    coadaEP(int d=10):lista(d){pf=pr=NULL; cout<<"ciP ";}
    coadaEP(const coadaEP & c):lista(c){pf=v+(c.pf-c.v); pr=v+(c.pr-c.v);cout<<"cc ";}
    coadaEP operator =(coadaEP  c)
    {this->lista::operator =(c);
    pf=v+(c.pf-c.v); pr=v+(c.pr-c.v);cout<<"o= ";
    }
    bool inserare(int val){}
};

int main()
{/*lista l1;
    coadaI c1,c2(20);
    coadaE  c3(3),c4(c3); */
    coadaEP c5(20),c6(c5); c6=c5;
}

