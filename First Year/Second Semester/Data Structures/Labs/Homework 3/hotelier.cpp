#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin>>n;
    cin.get();
    getline(cin,s);
    vector<bool> v(10,0);

    for(int i=0;i<s.size();i++)
    {
        if(s[i] == 'L') {
            for(int i=0;i<10;i++)
                if(v[i] == 0) {
                    v[i] = 1;
                    break;
                }
        }

        if(s[i] == 'R') {
            for(int i=9;i>=0;i--)
                if(v[i] == 0){
                    v[i] = 1;
                    break;
                }
        }

        if(s[i] >= '0' && s[i] <='9') {
            v[(int)s[i] - '0'] = 0;
        }
    }
    for(int i=0;i<10;i++) cout<<v[i];

    return 0;
}