// prezentari in sapt: 4,8,12
// 10-15 minute
// 1000-2000 linii de cod/proiect
#include <iostream>

using namespace std;

int main()
{
//    int *a;
    int b = 10;
    int *a = new int();
//    *a = b;
    *a = 100;
    cout<<*a;
    a = &b;

    cout<<*a<<endl<<a<<endl<<&a<<endl<<&b;
    return 0;
}