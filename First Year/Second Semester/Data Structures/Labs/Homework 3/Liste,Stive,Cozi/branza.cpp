#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

ifstream f("branza.in");
ofstream g("branza.out");

void print(deque<int> d, vector<pair<int,int>>v) {
    while(!d.empty()) {
        cout<<"("<<d.front()<<",{"<<v[d.front()].first<<","<<v[d.front()].second<<"}) ";
        d.pop_front();
    }
    cout<<endl;
}

int main()
{
    int n,s,t;
    long long pret = 0;
    f>>n>>s>>t;
    
    vector<pair<long long,long long>>v(n);
    deque<int> d;
    
    for(int i=0;i<n;i++) f>>v[i].first>>v[i].second;

    for(int i=0;i<n;i++) {
        if(!d.empty() && d.front() + t < i) d.pop_front();

        while(!d.empty() && (s*(i-d.back()) + v[d.back()].first) >= v[i].first) d.pop_back();
        d.push_back(i);

        // print(d,v);
        // cout<<s*v[d.back()].second*(i-d.front())<<" "<<v[d.front()].first*v[d.back()].second<<" ";
        pret += (s*v[d.back()].second*(i-d.front()) + v[d.front()].first*v[d.back()].second);
        // cout<<pret<<endl;
    }

    g<<pret;
    return 0;
}