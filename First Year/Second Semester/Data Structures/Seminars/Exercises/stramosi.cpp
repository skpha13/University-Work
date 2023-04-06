#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream f("stramosi.in");
ofstream g("stramosi.out");

int main()
{
    int n,m;
    vector<vector<int>> stramosi;
    f>>n>>m;
    vector<int> temp;
    stramosi.push_back(temp);
    for(int i=1;i<=n;i++)
    {
        vector<int> temp;
        stramosi.push_back(temp);
    }

    int parinte;
    for(int i=1;i<=n;i++)
    {
        f>>parinte;
        stramosi[i].push_back(parinte);
        stramosi[i].insert(stramosi[i].end(),stramosi[parinte].begin(),stramosi[parinte].end());
    }

    int x,y;
    for(int i=0;i<m;i++)
    {
        f>>x>>y;
        if(x <= stramosi.size() && y<stramosi[x].size())
            g<<stramosi[x][y-1]<<endl;
        else g<<0<<endl;
    }

    f.close();
    g.close();
    return 0;
}
