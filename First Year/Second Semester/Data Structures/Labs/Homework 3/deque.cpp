#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");

int main()
{
    int n,k;
    long long int s=0;
    f>>n>>k;
    vector<int> v(n);
    deque<int> d;

    for(int i=0;i<n;i++) f>>v[i];

    for(int i=0;i<n;i++) {
        while(!d.empty() && v[i] <= v[d.back()]) d.pop_back();
        d.push_back(i);

        if(d.front() == i-k) d.pop_front();

        if(i>=k-1) s += v[d.front()];
    }

    g<<s;
    return 0;
}