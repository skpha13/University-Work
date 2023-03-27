#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int n;

    cin>>n;
    while(n!=0)
    {
        int x,temp;
        stack<int> output;
        stack<int> aux;
        bool ok = true;

        output.push(0);
        aux.push(0);
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(x == output.top() + 1)
                output.push(x);
            else if(aux.top() - 1 == output.top())
            {
                while(aux.top() - 1 == output.top())
                {
                    output.push(aux.top());
                    aux.pop();
                }
                aux.push(x);
            }
                else
                    aux.push(x);
        }
        while(aux.top() != 0) 
            output.push(aux.top()),aux.pop();

        if(output.size() != n + 1) ok = 0;        
        if(output.size() <= 2) ok = 1;
        else
        {
            temp = output.top();
            output.pop();
            while(output.top() != 0)
            {
                if(temp - 1 != output.top()) 
                {
                    ok = 0; 
                    break;
                }
                temp = output.top();
                output.pop();
            }
        }

        ok ? cout<<"yes\n" : cout<<"no\n";
        cin>>n;
    }
    return 0;
}