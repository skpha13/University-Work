#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream f("timbre.in");
std::ofstream g("timbre.out");

bool compare(std::pair<int,int> a, std::pair<int,int > b) {
    if(a.first > b.first) return true;
    return false;
}

int main() {
    int n,m,k,sup,c;
    std::priority_queue<int, std::vector<int>, std::greater<int>> cost;
    std::vector<std::pair<int,int>> lungimi_intervale;
    f>>n>>m>>k;

    for(int i=0;i<m;i++) {
        f>>sup>>c;
        lungimi_intervale.push_back(std::make_pair(sup,c));
    }

    std::sort(lungimi_intervale.begin(),lungimi_intervale.end(), compare);

    int index = 0, sum = 0;
    while(n) {
        while(index < m && lungimi_intervale[index].first >= n) {
            cost.push(lungimi_intervale[index].second);
            index++;
        }
        if(!cost.empty()) sum += cost.top();
        while(!cost.empty()) cost.pop();
        n -= k;
    }
    g<<sum;
    return 0;
}