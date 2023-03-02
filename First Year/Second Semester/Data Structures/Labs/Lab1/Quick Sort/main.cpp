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
    // the length of the current array
    srand(time(NULL));
    k = rand()%(dr-st+1) + st;
    l = rand()%(dr-st+1) + st;
    p = rand()%(dr-st+1) + st;    

    if((v[k]<v[l] && v[l]<v[p]) || (v[p] < v[l] && v[l] < v[k]))
        pivot = v[l];
    else if ((v[l]<v[k] && v[k]<v[p]) || (v[p]<v[k] && v[k]<v[l]))
        pivot = v[k];
    else
        pivot = v[p];

    cout<<"Pivot = "<<pivot<<" | ";
    cout<<"V = ";
    for(int i=st;i<=dr;i++)
        cout<<v[i]<<" ";

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

    cout<<" | temp = ";
    for(int i=st;i<=dr;i++) 
        cout<<temp[i]<<" ";
    cout<<" | "<<st<<" "<<dr<<" "<<poz_left<<" "<<poz_right<<endl;

    for(int i=st;i<=dr;i++)
        v[i] = temp[i];
    
    // daca merg mai intai in stanga merge perfect, dar in dreapta e loop infinit
    quicksort(poz_right+1,dr);
    quicksort(st,poz_left-1);
}

int main()
{
    f>>n;
    for(int i=0;i<n;i++) f>>v[i];

    quicksort(0,n-1);
    for(int i=0;i<n;i++) g<<v[i]<<" ";

    return 0;
}