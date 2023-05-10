#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

ifstream f("vila2.in");
ofstream g("vila2.out");

void update1(deque<int>& temp,const vector<int>& v,int i) {
    while(!temp.empty() && v[i] >= v[temp.back()]) temp.pop_back();
    temp.push_back(i);
}

void update2(deque<int>& temp,const vector<int>& v,int i) {
    while(!temp.empty() && v[i] <= v[temp.back()]) temp.pop_back();
    temp.push_back(i);
}

int main() 
{
    int n,k,mx=0;
    deque<int> q,p;
    f>>n>>k;
    vector<int> v(n,0);
    k++;
    
    for(int i=0;i<n;i++) f>>v[i];

    for (int i=0;i<k;i++) update1(q,v,i),update2(p,v,i);

    if(mx < v[q.front()]-v[p.front()])
        mx = v[q.front()]-v[p.front()];
    for(int i=k;i<n;i++)
    {
        if(q.front() == i-k) q.pop_front();
        if(p.front() == i-k) p.pop_front();

        update1(q,v,i);
        update2(p,v,i);

        if(mx < v[q.front()]-v[p.front()])
            mx = v[q.front()]-v[p.front()];
    }

    g<<mx;
    return 0;
}