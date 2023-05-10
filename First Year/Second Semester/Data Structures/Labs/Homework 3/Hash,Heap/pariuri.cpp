#include <iostream>
#include <fstream>
#include <unordered_map>

std::ifstream f("pariuri.in");
std::ofstream g("pariuri.out");

int main() {
    int n;
    f>>n;
    std::unordered_map<int, int> map;

    for(int i=0;i<n;i++) {
        int nrPerechi;
        f>>nrPerechi;
        for(int j=0;j<nrPerechi;j++) {
            int timp,bani;
            f>>timp>>bani;
            if(map.find(timp) == map.end()) map[timp] = bani;
            else map[timp] = map[timp]+bani;
        }
    }
    g<<map.size()<<"\n";
    for(auto it:map) {
        g<<it.first<<" "<<it.second<<" ";
    }
    return  0;
}