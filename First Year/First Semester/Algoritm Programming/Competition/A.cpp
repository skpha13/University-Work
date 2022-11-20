#include <iostream>
#include <cstring>

using namespace std;

int k,p,res,n;
char s[1001],t[1001];

int main()
{
    cin>>k;
    cin.get();
    cin.getline(s,1001);
    cin.getline(t,1001);
    n=strlen(s);
    for(int i=0;i<n && k!=0;i++)
        if(s[i]==t[i])
        {
            p++;
            k--;
        }
    if(k==0)
    {
        for(int i=0;i<n;i++)
            if(s[i]!=t[i]) p++;
        res+=p;
    }
    else
        res+=p+(n-p-k);
    cout<<res;
    return 0;
}