#include <iostream>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001];



int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}