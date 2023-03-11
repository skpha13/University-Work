#include <iostream>
#include <fstream>

using namespace std;

ifstream f("numere.in");
ofstream g("numere.out");

int n,v[500001],temp[500001],i,j,mx=0;

void mergesort(int st,int dr)
{
    if(st<dr)
    {
        int m  = (st + dr) / 2;
        mergesort(st,m);
        mergesort(m+1,dr);

        int i=st,j=m+1,k=0;
        while(i<=m && j<=dr)
        {
            if(v[i]<v[j])
                temp[k++]=v[i++];
            else
                temp[k++]=v[j++];
        }
        while(i<=m) temp[k++] = v[i++];
        while(j<=dr) temp[k++] = v[j++];

        i=st; j=0;
        while(i<=dr) v[i++]=temp[j++];
    }
}

void countsort()
{
    int *vf = new int[1000000000],k=0;

    for(int i=0;i<=mx;i++)
        vf[i] = 0;

    for(int i=0;i<n;i++)
        vf[v[i]]++;

    for(int i=0;i<=mx;i++)
        if(vf[i] != 0)
            for(int j=0;j<vf[i];j++)
                v[k++] = i;

    if (vf!=NULL)
    {
        delete[] vf;
        vf = NULL;
    }
}

int main()
{
    f>>n;
    for(int i=0;i<n;i++)
    {
        f>>v[i];
        if(v[i]>mx) mx = v[i];
    }

//    mergesort(0,n-1);
    countsort();
    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}