#include <iostream>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

ifstream f("queue.in");
ofstream g("queue.out");

int main()
{
    int n,nr;
    string s;
    f>>n;
    f.get();

    stack<int> s1;
    stack<int> s2;

    for(int i=0;i<n;i++) {
        getline(f,s);
        if(s.find("push_back") != string::npos ) {
            string number = "";
            int index = 10;
            while(isdigit(s[index])) number += s[index++];
            nr = stoi(number);

            s1.push(nr);
            g<<i+1<<": read("<<nr<<") push(1,"<<nr<<")\n";
        }
        if(s.find("pop_front") != string::npos) {
            if(s2.empty()) {
                while(s1.size() > 1) {
                    int temp = s1.top();
                    s1.pop();
                    s2.push(temp);
                    g<<i+1<<": pop(1) push(2,"<<temp<<") ";
                }
                int temp = s1.top();
                s1.pop();
                g<<"pop(1) write("<<temp<<")\n";
            }
            else {
                int temp = s2.top();
                s2.pop();
                g<<i+1<<": pop(2) write("<<temp<<")\n";
            }
        }
    }

    return 0;
}