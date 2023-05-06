#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream f("paranteze.in");
ofstream g("paranteze.out");

struct info {
    int poz;
    char paranteza;
};  

int main()
{
    int n;
    int contor = 0,mx = 0;
    stack<info> st;
    char c;
    info inf;
    inf.poz = -1;
    inf.paranteza = ')';
    st.push(inf);

    f>>n;
    for(int i=1;i<=n;i++)
    {
        f>>c;
        if(c=='(' || c=='[' || c=='{')
        {
            inf.poz = i;
            inf.paranteza = c;
            st.push(inf);
        }
        else 
        {   
            if((c==')' && st.top().paranteza == '(') || (c==']' && st.top().paranteza == '[') || (c=='}' && st.top().paranteza == '{'))
            {
                if(!st.empty()) st.pop();
                if(!st.empty())
                    mx = max(mx,i-st.top().poz);
                else
                {
                    inf.poz = i;
                    inf.paranteza = c;
                    st.push(inf);
                }
            }
            else
                {
                    inf.poz = i;
                    inf.paranteza = c;
                    st.push(inf);
                }
        }
    }
    g<<mx;
    g.close();
    return 0;
}

// 16
// ([{)]}[]{}()[{]}

// 13
// {)([({})]([{}

