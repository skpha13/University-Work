#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001];

void quicksort(int st,int dr)
{
    if(st>=dr) return;
    int k,l,p,pivot;

    k = v[rand()%(dr-st+1) + st];
    l = v[rand()%(dr-st+1) + st];
    p = v[rand()%(dr-st+1) + st];

    if((k<l && l<p) || (p < l && l < k))
        pivot = l;
    else if ((l<k && k<p) || (p<k && k<l))
        pivot = k;
    else
        pivot = p;

    int i = st - 1;
    for(int j=st;j<=dr;j++)
        if(v[j]<pivot)
            swap(v[++i],v[j]);

    for(int j=st;j<=dr;j++)
        if(v[j]==pivot)
            swap(v[++i],v[j]);

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