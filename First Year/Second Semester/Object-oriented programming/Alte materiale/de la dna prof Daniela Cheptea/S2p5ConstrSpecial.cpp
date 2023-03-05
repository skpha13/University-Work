#include <iostream>
using namespace std;
//cazuri speciale pt apel constructori
class C{
public: C(int i=0){cout<<"initializare ";}
C(const C& c){cout<<"copiere ";}
	};
	
	void f1(C o){cout<<"parametru ";}
	C f2(){cout<<"rezultat ";return 1;}
	void f3(const C & o){cout<<"parametru-referinta ";}
	const C& f4(){cout<<"rezultat-referinta ";return 1;}
int main() {
	f1(1);// nu se apeleaza cel de copiere ci cel de initializare
	f2();
	f3(1);// desi e tranmitere prin ref -se apeleaza cel de initializare
	f4();
	// your code goes here
	return 0;
}
