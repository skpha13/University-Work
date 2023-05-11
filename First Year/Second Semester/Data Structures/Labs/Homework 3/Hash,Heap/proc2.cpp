#include <iostream>
#include <unordered_map>
#include <fstream>

std::ifstream f("proc2.in");
std::ofstream g("proc2.out");

int main() {
    std::unordered_map<int,int> map;
    int n,m,in,out,timp_final,j;

    f>>n>>m;
    for(int i=0;i<m;i++) {
        f>>in>>out;
        timp_final = in + out;
        for(j=1;j<=n;j++) {
            if(map.find(j) != map.end() && i+1 >= map[j]) map.erase(j);

            if(map.find(j) == map.end()){
                map[j] = timp_final;
                g<<j<<"\n";
                break;
            }
        }
    }

    return 0;
}