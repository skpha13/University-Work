#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

ifstream f("alibaba.in");
ofstream g("alibaba.out");

int main()
{
    int n,m,count,size;
    string s;
    f>>n>>m>>s;
    size = n-m;
    count = m;
    stack<char> temp;
    vector<char> v;

    temp.push(s[0]);

    for(int i=1;i<s.size();i++)
    {
        if(!temp.empty() && temp.top() < s[i])
        {
            while(!temp.empty() && temp.top() < s[i] && count != 0)
                temp.pop(), count--;
            temp.push(s[i]);
        }
        else if(temp.size() < size) temp.push(s[i]);
    }

    while(!temp.empty()) v.push_back(temp.top()), temp.pop();
    for(int i=v.size()-1;i>=0;i--)
        g<<v[i];
    g.close();
    return 0;
}