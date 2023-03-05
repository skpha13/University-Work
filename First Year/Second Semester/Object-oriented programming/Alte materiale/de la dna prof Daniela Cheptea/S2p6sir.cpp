#include <iostream>
#include <string.h>
using namespace std;
class sir
{char *p;
public:
 sir(const char * c=""); /* sau 1 constructor fara parametru  si 1 constructor cu parametru */
 sir(const sir& s);    /* fara & -se apeleaza infinit constructorul de copiere !!*/
 sir operator +(sir s);  /* 2 operanzi -obiectul implicit si parametrul*/
 sir operator=(sir s);
 ~sir();
 friend istream& operator>>(istream &i, sir& s);
 friend ostream& operator <<(ostream &o, const sir& s);

};
sir::sir(const char* c)
{ p=new char[strlen(c)+1];
  strcpy(p,c);
}
sir::sir(const sir& s)
{p=new char[strlen(s.p)+1];
 strcpy(p,s.p);
}
sir sir::operator+(sir s)
{sir l;
 delete[]p;
 l.p=new char[strlen(p)+strlen(s.p)+1];
 strcpy(l.p, p);
 strcpy(l.p, s.p);
 return l;
}
sir sir::operator=(sir s)
{delete[]p;/* daca s e transmis prin referinta -doar daca strcmp(s.p,p)!=0 sau this!=&s */
p=new char[strlen(s.p)+1];
strcpy(p,s.p);
return *this;
}
/*
sir& sir::operator+(sir &s) //mai eficient
{ sir *pl=new sir;
 pl->p=new char[strlen(p)+strlen(s.p)+1];
 strcpy(pl->p,p);
 strcat(pl->p,s.p);
 return *pl
}
*/
sir::~sir()
{ delete[]p;
}
istream& operator>>(istream& i, sir& s)
{ char v[100];
 i>>v;
 delete[]s.p;
 s.p=new char[strlen(v)+1];
 strcpy(s.p,v);
 return i;
}
ostream& operator<<(ostream& o, const sir& s)
{o<<s.p;
 return o;
}
int main()
{ sir s1,s2("ab"),s3(s2),s4=s2;
   s1=s2;
   s1=s2+s3;
   cin>>s1;
   cout<<s1;

    return 0;
}
