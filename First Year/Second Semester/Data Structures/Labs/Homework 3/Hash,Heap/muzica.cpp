#include <iostream>
#include <fstream>
#include <unordered_map>

std::ifstream f("muzica.in");
std::ofstream g("muzica.out");

int main() {
    int n,m,count=0;
    long long A,B,C,D,E,temp;
    f>>n>>m>>A>>B>>C>>D>>E;
    std::unordered_map<int, bool> map;

    for(int i=0;i<n;i++) f>>temp, map[temp] = 1;

    if(map.find(A)!=map.end()) count++,map[A] = 0;
    if(map.find(B)!=map.end() && map[B] == 1) count++, map[B] = 0 ;

    for(int i=3;i<=m;i++) {
        temp = (C*B + D*A) % E;
        if(map.find(temp)!=map.end() && map[temp] == 1) count++, map[temp] = 0;
        A = B;
        B = temp;
    }
    g<<count;

    return  0;
}