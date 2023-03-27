#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

ifstream f("trompeta.in");
ofstream g("trompeta.out");

int main()
{
    int n,count;
    string s;
    long unsigned int m;
    f>>n>>m>>s;
    count = n-m;
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
        else if(temp.size() < m) temp.push(s[i]);
    }

    while(!temp.empty()) v.push_back(temp.top()), temp.pop();
    for(int i=v.size()-1;i>=0;i--)
        g<<v[i];
    g.close();
    return 0;
}

// 20 10
// 11999956498273841228

// 5 4
// 19990

// 5 3
// 54321

// 5 3
// 12345

// 9 3
// 987987987