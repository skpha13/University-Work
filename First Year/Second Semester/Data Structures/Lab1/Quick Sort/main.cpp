#include <iostream>
#include <fstream>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

int n,v[500001],temp[500001];

void quicksort(int st,int dr)
{
    if(st<dr)
    {
        int m = (st+dr)/2;
        int pivot = v[m];
        int poz_left=st,poz_right=dr;

        for(int i=st;i<=dr;i++)
            if(v[i]<pivot)
                temp[poz_left++] = v[i];
            else
                temp[poz_right--] = v[i];

        for(int i=st;i<=dr;i++) v[i]=temp[i];
        quicksort(st,poz_left-1);
        quicksort(poz_right+1,dr);
    }
}

int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    quicksort(0,n-1);
    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}