#include <iostream>
#include <cmath>

using namespace std;

int n,s,t[101],mx,sum;
float res;

int main()
{
    cin>>n>>s;
    for(int i=1;i<=n;i++)
    {
        cin>>t[i];
        if(t[i]>mx) mx=t[i];
    }
    res=mx*s;
    res/=1000;
    cout<<ceil(res);
    return 0;
}