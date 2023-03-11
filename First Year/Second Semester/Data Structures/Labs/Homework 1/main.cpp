#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

ifstream f("teste.in");
ofstream g("timp.out");

int *v = new int[1000000000];
int *vcopy = new int[1000000000];
int n,mx=0;

void generareFisierIn();
bool verificaSortare(int v[],int n);
void verificaTimpi();

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

void countsort(int v[],int n)
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

void interschimbare(int v[],int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=i;j<n;j++)
            if(v[i]>v[j]) swap(v[i],v[j]);
}

int nrcifre(int n)
{
    int cifre = 0;
    if(n<10) return 1;
    while(n!=0)
    {
        n/=10;
        cifre++;
    }
    return cifre;
}

void radixsort10(int v[],int n)
{
    vector<vector <int>> count;
    int nrCifre = nrcifre(mx),exp=1;

    vector<int> temp(0);
    for(int i=0;i<10;i++)
        count.push_back(temp);

    for(int l=0;l<nrCifre;l++)
    {
        for(int i=0;i<10;i++) count[i].clear();

        for(int i=0;i<n;i++)
            count[(v[i]/exp)%10].push_back(v[i]);

        int k = 0;
        for(int i=0;i<10;i++)
            if(count[i].size())
                for(int j=0;j<count[i].size();j++)
                    v[k++] = count[i][j];

        exp *= 10;
    }
}

void radixsort16(int v[],int n)
{
    vector<vector <int>> count;
    int exp=0;

    vector<int> temp(0);
    for(int i=0;i<=16;i++)
        count.push_back(temp);

    while(mx>>exp > 0)
    {
        for(int i=0;i<=16;i++) count[i].clear();

        for(int i=0;i<n;i++)
            count[(v[i]>>exp) & 0xf].push_back(v[i]);

        int k = 0;
        for(int i=0;i<16;i++)
            if(count[i].size())
                for(int j=0;j<count[i].size();j++)
                    v[k++] = count[i][j];

        exp += 4;
    }
}

void radixsort64(int v[],int n)
{
    vector<vector <int>> count;
    int exp=0;

    vector<int> temp(0);
    for(int i=0;i<=64;i++)
        count.push_back(temp);

    while(mx>>exp > 0)
    {
        for(int i=0;i<=64;i++) count[i].clear();

        for(int i=0;i<n;i++)
            count[(v[i]>>exp) & 0x11f].push_back(v[i]);

        int k = 0;
        for(int i=0;i<64;i++)
            if(count[i].size())
                for(int j=0;j<count[i].size();j++)
                    v[k++] = count[i][j];

        exp += 6;
    }
}

void radixsort216(int v[],int n)
{
    //2^16 = 65536
    vector<vector <int>> count;
    int exp=0;

    vector<int> temp(0);
    for(int i=0;i<=65536;i++)
        count.push_back(temp);

    while(mx>>exp > 0 && exp < 32)
    {
        for(int i=0;i<=65536;i++) count[i].clear();

        for(int i=0;i<n;i++)
            count[(v[i]>>exp) & 0xffff].push_back(v[i]);

        int k = 0;
        for(int i=0;i<65536;i++)
            if(count[i].size())
                for(int j=0;j<count[i].size();j++)
                    v[k++] = count[i][j];

        exp += 16;
    }
}

void insertionsort(int v[],int n,int pos,int gap)
{
    int temp,j;
    for(int i=pos + gap;i<n;i+=gap)
    {
        temp = v[i];
        j = i-gap;
        while(j>=0 && v[j] > temp)
            v[j+gap] = v[j], j-=gap;
        v[j+gap] = temp;
    }
}

void shellsort(int v[],int n)
{
    int gap = n/2;
    while(gap > 0)
    {
        for(int i=0;i<gap;i++)
            insertionsort(v,n,i,gap);
        gap /= 2;
    }
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

int main()
{
    verificaTimpi();
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

bool verificaSortare(int v[],int n)
{
    if(n==0 || n==1) return true;
    for(int i=1;i<n;i++)
        if(v[i] < v[i-1]) return false;
    return true;
}

void verificaTimpi()
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
    if(verificaSortare(vcopy,n))
    {
        g<<"Mergesort: "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Mergesort: Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    countsort(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Countsort: "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Countsort: Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    interschimbare(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Interschimbare: "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Interschimbare: Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    shellsort(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Shellsort: "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Shellsort: Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    radixsort10(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Radixsort(10): "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Radix(10): Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    radixsort16(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Radixsort(16): "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Radixsort(16): Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    radixsort64(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Radixsort(64): "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Radixsort(64): Nu a sortat corect"<<endl;

    for(int i=0;i<n;i++) vcopy[i] = v[i];
    start = clock();
    radixsort216(vcopy,n);
    end = clock();
    if(verificaSortare(vcopy,n))
    {
        g<<"Radixsort(2^16): "<<(double)(end-start);
        g<<endl;
    }
    else g<<"Radixsort(2^16): Nu a sortat corect"<<endl;

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
}
