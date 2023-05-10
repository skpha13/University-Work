#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

std::ifstream f("loto.in");
std::ofstream g("loto.out");

std::unordered_map<int, std::pair<int,std::vector<int>>> map;
std::vector<int> v;
int target = 0,n;
bool found = false;

void solution() {
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
            for(int k=j;k<n;k++) {
                std::vector<int> temp;
                temp.push_back(v[i]);
                temp.push_back(v[j]);
                temp.push_back(v[k]);
                map[v[i]+v[j]+v[k]] = std::make_pair(target - (v[i] + v[j] + v[k]),temp);
            }

    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
            for(int k=j;k<n;k++){
                int sum = v[i]+v[j]+v[k];
                if(map.find(target-sum)!=map.end() && sum == map[target - sum].first) {
                    std::vector<int> temp = map[target - sum].second;
                    g<<v[i]<<" "<<v[j]<<" "<<v[k]<<" "<<temp[0]<<" "<<temp[1]<<" "<<temp[2];
                    found = true;
                    return;
                }
            }
}

int main() 
{

    f>>n>>target;

    v.resize(n);

    for(int i=0;i<n;i++) f>>v[i];

    solution();

    if(!found) g<<-1;

    return 0;
}