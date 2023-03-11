#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

ifstream f("teste.in");
ofstream g("timp.out");

int *v = new int[1000000000];
int *vcopy = new int[1000000000];
int n,mx=0;

void generareFisierIn();

void mergesort(int v[],int st,int dr)
{
    int *temp = new int[1000000000];
    if(st<dr)
    {
        int m  = (st + dr) / 2;
        mergesort(v,st,m);
        mergesort(v,m+1,dr);

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

    if(temp != NULL)
    {
        delete[] temp;
        temp = NULL;
    }
}

void countsort(int v[])
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

void interschimbare(int v[])
{
    for(int i=0;i<n-1;i++)
        for(int j=i;j<n;j++)
            if(v[i]>v[j]) swap(v[i],v[j]);
}

int main()
{
    clock_t start,end;
    f>>n;
    for(int i=0;i<n;i++)
    {
        f>>v[i];
        if(v[i]>mx) mx = v[i];
    }

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    mergesort(vcopy,0,n-1);
    end = clock();
    g<<"Mergesort: "<<(double)(end-start);
    g<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    countsort(vcopy);
    end = clock();
    g<<"Countsort: "<<(double)(end-start);
    g<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    interschimbare(vcopy);
    end = clock();
    g<<"Interschimbare: "<<(double)(end-start);
    g<<endl;

    if (v!=NULL)
    {
        delete[] v;
        v = NULL;
    }

    if (vcopy!=NULL)
    {
        delete[] vcopy;
        vcopy = NULL;
    }

    return 0;
}

//putine numere
//crescator
//descrescator
//5 cu destule numere
//2 cu multe numere
void generareFisierIn()
{

}