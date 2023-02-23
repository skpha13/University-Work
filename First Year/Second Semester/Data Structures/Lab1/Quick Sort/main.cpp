#include <iostream>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001];

void quicksort(int st,int dr)
{
    if(st>=dr) return;

    int pivot = v[dr],i=st-1;

    for (int j = st; j < dr; j++)
        if(v[j]<=pivot)
        {
            i++;
            swap(v[i],v[j]);
        }
    swap(v[i+1],v[dr]);
    i++;
    quicksort(st,i-1);
    quicksort(i+1,dr);
}

int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    quicksort(0,n-1);
    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}