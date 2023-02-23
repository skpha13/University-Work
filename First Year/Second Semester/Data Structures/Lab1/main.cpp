#include <iostream>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001],ok = 1;

int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    for(int i=0;i<n-1;i++)
        if(ok)
            for(int j=i;j<n;j++)
                if(v[i]>v[j])
                {
                    ok = 1;
                    swap(v[i],v[j]);
                }
    for(int i=0;i<n;i++) g<<v[i]<<" ";
    return 0;
}