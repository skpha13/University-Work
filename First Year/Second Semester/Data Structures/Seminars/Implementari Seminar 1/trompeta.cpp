#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream f("trompeta.in");
ofstream g("trompeta.out");

int word[1000000];

int main()
{
    int n,m,nr,count;
    f>>n>>m>>nr;
    count = n-m;
    stack<int> st;
    while(nr)
    {
        st.push(nr%10);
        nr/=10;
    }
    stack<int> temp;
    temp.push(st.top());
    st.pop();
    while(!st.empty() && count!=0)
    {
        if(!temp.empty() && temp.top() <= st.top())
        {
            temp.pop();
            temp.push(st.top());
            st.pop();
            count--;
        }
        else
        {
            temp.push(st.top());
            st.pop();
        }
    }
    while(!st.empty())
    {
        temp.push(st.top());
        st.pop();
    }
    int k=0;
    while(!temp.empty())
    {
        word[k++] = temp.top();
        temp.pop();
    }
    for(int i=k-1;i>=0;i--)
        g<<word[i];
    g.close();
    return 0;
}