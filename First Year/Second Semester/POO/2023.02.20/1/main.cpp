// prezentari in sapt: 4,8,12
// 10-15 minute
// 1000-2000 linii de cod/proiect
#include <iostream>

using namespace std;

int main()
{
/*
//    int *a;
    int b = 10;
    int *a = new int();
    int *c;

    c = a;
    *c = 10;

    *a = b;
    *a = 100;
//    cout<<*a;
//    a = &b;
    cout<<*a<<endl<<a<<endl<<&a<<endl<<&b<<endl<<b;
*/

    int *v = new int[3];
    for(int i=0;i<3;i++)
    {
        *(v+i) = i;
        cout<<v[i]<<endl;
    }

    if (v != NULL)
    {
        delete []v;
        v = NULL;
    }
    v = new int[4];
    // tema : citim string.h
    return 0;
}
