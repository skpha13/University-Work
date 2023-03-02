#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001],temp[500001];

void quicksort(int st,int dr)
{
    if(st>=dr) return;
    int k,l,p,pivot,poz_left=st,poz_right=dr,aux=0,nr=0;
    
    k = v[rand()%(dr-st+1) + st];
    l = v[rand()%(dr-st+1) + st];
    p = v[rand()%(dr-st+1) + st];    

    if((k<l && l<p) || (p < l && l < k))
        pivot = l;
    else if ((l<k && k<p) || (p<k && k<l))
        pivot = k;
    else
        pivot = p;

    for(int i=st;i<=dr;i++)
    {
        if(v[i]<pivot)
            temp[poz_left++] = v[i];
        else 
            if(v[i]>pivot)
                temp[poz_right--] = v[i];
            else
                {
                    if(!nr)
                    {
                        aux = v[i];
                        nr++;
                    }
                    else
                        temp[poz_left++] = v[i];
                }
    }
    temp[poz_right] = aux;

    for(int i=st;i<=dr;i++)
        v[i] = temp[i];
    
    quicksort(st,poz_left-1);
    quicksort(poz_right+1,dr);
}

int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    quicksort(0,n-1);
    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}