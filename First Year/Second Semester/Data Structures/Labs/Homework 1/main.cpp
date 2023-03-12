#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

ifstream f("D:\\UNI CODE\\test.txt");
ofstream g("timp.out");

int *v = new int[1000000000];
int *vcopy = new int[1000000000];
int n,mx=0,nrteste;

void generareFisierIn();
bool verificaSortare(int v[],int n);
void verificaTimpi();

void mergesort(int v[],int st,int dr)
{
    if(st<dr)
    {
        int *temp = new int[n];
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

        if(temp != NULL)
        {
            delete[] temp;
            temp = NULL;
        }
    }
}

void countsort(int v[],int n)
{
    int *vf = new int[mx],k=0;

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

void radixsort2(int v[],int n,int baza)
{
    vector<vector <int>> count;
    int exp=0,nrShift = 1,putere = 2;

    while(putere < baza)
    {
        nrShift++;
        putere = putere<<1;
    }

    vector<int> temp(0);
    for(int i=0;i<=baza;i++)
        count.push_back(temp);

    while(mx>>exp > 0 && exp < 32)
    {
        for(int i=0;i<=baza;i++) count[i].clear();

        for(int i=0;i<n;i++)
            count[(v[i]>>exp) & (baza-1)].push_back(v[i]);

        int k = 0;
        for(int i=0;i<baza;i++)
            if(count[i].size())
                for(int j=0;j<count[i].size();j++)
                    v[k++] = count[i][j];

        exp += nrShift;
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
}

int main()
{
//    generareFisierIn();
    verificaTimpi();
    return 0;
}

void generareFisierIn()
{
    ofstream a("test.txt");
    a<<20<<endl;
    // test cu un numar mic de elemente, hardcoded
    a<<10<<endl<<"248206 585825 652412 335040 72031 179768 282309 975160 609689 473890"<<endl;

    // numere in ordine crescatoare
    a<<100000<<endl;
    for(int i=0;i<100000;i++)
        a<<i<<" ";
    a<<endl;

    // numere in ordine descrecatoare
    a<<100000<<endl;
    for(int i=100000;i>0;i--)
        a<<i<<" ";
    a<<endl;

    // numere mici
    a<<100000<<endl;
    for(int i=0;i<100000;i++)
        a<<rand()%100<<" ";
    a<<endl;

    // numere mari
    a<<100000<<endl;
    for(int i=0;i<100000;i++)
        a<<rand()%100000000 + 10000000<<" ";
    a<<endl;

    // 1.000 de numere
    a<<1000<<endl;
    for(int i=0;i<1000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 10.000 de numere
    a<<10000<<endl;
    for(int i=0;i<10000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 100.000 de numere
    a<<100000<<endl;
    for(int i=0;i<100000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 200.000 de numere
    a<<200000<<endl;
    for(int i=0;i<200000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 300.000 de numere
    a<<300000<<endl;
    for(int i=0;i<300000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 400.000 de numere
    a<<400000<<endl;
    for(int i=0;i<400000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 500.000 de numere
    a<<500000<<endl;
    for(int i=0;i<500000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 600.000 de numere
    a<<600000<<endl;
    for(int i=0;i<600000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 700.000 de numere
    a<<700000<<endl;
    for(int i=0;i<700000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 800.000 de numere
    a<<800000<<endl;
    for(int i=0;i<800000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 900.000 de numere
    a<<900000<<endl;
    for(int i=0;i<900000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 1.000.000 de numere
    a<<1000000<<endl;
    for(int i=0;i<1000000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 10.000.000 de numere
    a<<10000000<<endl;
    for(int i=0;i<10000000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 100.000.000 de numere
    a<<100000000<<endl;
    for(int i=0;i<100000000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;

    // 1.000.000.000 de numere
    a<<1000000000<<endl;
    for(int i=0;i<1000000000;i++)
        a<<rand()%100000000<<" ";
    a<<endl;
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
    ofstream b("plot.txt");
    n = 10;
//    clock_t start,end;
    f>>nrteste;
    for(int t=0;t<nrteste;t++)
    {
        g<<"Testul: "<<t+1<<endl;
        for(int i=0;i<n;i++) v[i] = 0;
        f>>n;
        b<<n<<" ";
        for(int i=0;i<n;i++)
        {
            f>>v[i];
            if(v[i]>mx) mx = v[i];
        }

        for(int i=0;i<n;i++) vcopy[i] = v[i];
        auto start = chrono::steady_clock::now();
        mergesort(vcopy,0,n-1);
        auto end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tMergesort: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tMergesort: Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        countsort(vcopy,n);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tCountsort: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tCountsort: Nu a sortat corect"<<endl;

        if(t < 10)
        {
            for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
            start = chrono::steady_clock::now();
            interschimbare(vcopy,n);
//        end = clock();
            end = chrono::steady_clock::now();
            if(verificaSortare(vcopy,n))
            {
                g<<"\tInterschimbare: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
                g<<endl;
                b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
            }
            else g<<"\tInterschimbare: Nu a sortat corect"<<endl;
        }

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        shellsort(vcopy,n);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tShellsort: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tShellsort: Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort10(vcopy,n);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(10): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(10): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort2(vcopy,n,16);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(2^4): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(2^4): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort2(vcopy,n,32);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(2^5): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(2^5): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort2(vcopy,n,64);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(2^6): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(2^6): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort2(vcopy,n,256);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(2^8): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(2^8): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        radixsort2(vcopy,n,65536); //65536 = 2^16
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tRadixsort(2^16): "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tRadixsort(2^16): Nu a sortat corect"<<endl;

        for(int i=0;i<n;i++) vcopy[i] = v[i];
//        start = clock();
        start = chrono::steady_clock::now();
        sort(vcopy,vcopy+n);
//        end = clock();
        end = chrono::steady_clock::now();
        if(verificaSortare(vcopy,n))
        {
            g<<"\tSortare nativa: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count();
            g<<endl;
            b<<(chrono::duration_cast<chrono::milliseconds>(end-start).count())<<" ";
        }
        else g<<"\tSortare nativa: Nu a sortat corect"<<endl;

        b<<endl;
        g<<endl;
    }
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
