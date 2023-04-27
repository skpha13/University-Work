#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream f("arbint.in");
ofstream g("arbint.out");

int arbore[100001 * 4];
int maxim = 0;

void update(int n, int left, int right, int p, int val);
void query(int n, int left, int right, int a, int b);

int main() 
{
    int n,m;
    f>>n>>m;

    for(int i=1;i<=n;i++)
    {
        int temp;
        f>>temp;
        update(1,1,n,i,temp);
    }

    for(int i=0;i<m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        if(x==0) {
            maxim = 0;
            query(1,1,n,y,z);
            g<<maxim<<endl;
        }
        if(x==1) {
            update(1,1,n,y,z);
        }
    }

    return 0;
}

void update(int n, int left, int right, int p, int val) {
    if(left==right) 
    {
        arbore[n] = val;   
        return ;
    }
    int m = (left + right)/2;
    if(p <= m)
        update(2*n,left,m,p,val);
    else
        update(2*n+1,m+1,right,p,val);
    
    arbore[n] = max(arbore[2*n],arbore[2*n+1]);
}   

void query(int n, int left, int right, int a, int b) {
    if(a<=left && right<=b) {
        if(maxim < arbore[n]) maxim = arbore[n];
        return ;
    }

    int m = (left + right)/2;
    if(a<=m) query(2*n,left,m,a,b);
    if(b>m) query(2*n+1,m+1,right,a,b);
}