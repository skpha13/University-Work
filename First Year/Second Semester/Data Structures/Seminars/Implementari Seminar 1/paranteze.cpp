#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream f("paranteze.in");
ofstream g("paranteze.out");

int main()
{
    int n;
    int contor = 0,mx = 0;
    stack<char> st;
    char c;

    f>>n;
    for(int i=1;i<=n;i++)
    {
        f>>c;
        if(c=='(' || c=='[' || c=='{') st.push(c);
        else if (c==')' || c==']' || c=='}')
            {
                if(!st.empty() && ((c==')' && st.top() == '(') || (c==']' && st.top() == '[') || (c=='}' && st.top() == '{')))
                    {
                        st.pop();
                        contor+=2;
                        if(mx < contor) mx = contor;
                    }
                else
                {
                    contor = 0;
                    while(!st.empty()) st.pop();
                }
            }
    }
    g<<mx;
    return 0;
}