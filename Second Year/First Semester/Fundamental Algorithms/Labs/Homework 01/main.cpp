#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
private:
    // n = number of nodes
    int n, numberOfEdges;
    vector<vector<int>> connections;
    vector<bool> vizited;
    vector<int> precedence;

    // private helper functions
    void DFSforCriticalConnections(int node, vector<int>& level, vector<int>& low, vector<vector<int>>& result);
    void DFSforShortestBridge(int i, int j,  vector<vector<int>>& grid, vector<vector<bool>>& vizited, queue<pair<int,int>>& waterNodes);

public:
    // constructors
    Graph(int n, vector<vector<int>> &connections, bool isOriented, bool needsPrecedence);

    // resolved functions
    bool isBipartit();
    vector<vector<int>> criticalConnections();
    vector<int> topologicalSort();

    // unresolved functions

        // a lot to change here, leave it for later
    int shortestBridge(vector<vector<int>>& grid);

        // same thing topological sort
    vector<int> eventualSafeNodes(vector<vector<int>>& graph);

        // this doesnt work
    bool equationsPossible(vector<string>& equations);
};

Graph::Graph(int n, vector<vector<int>> &connections, bool isOriented = false, bool needsPrecedence = false) {
    this->n = n;
    this->connections.resize(n+1);
    this->numberOfEdges = connections.size();

    if (isOriented == false) {
        for (int i = 0; i < connections.size(); i++) {
            this->connections[connections[i][0]].push_back(connections[i][1]);
            this->connections[connections[i][1]].push_back(connections[i][0]);
        }
        this->vizited.resize(n+1,false);
    }
    else {
        this->precedence.resize(n,0);
        for(int i=0;i<connections.size();i++) {
            if(needsPrecedence) this->precedence[connections[i][0]]++;

            this->connections[connections[i][1]].push_back(connections[i][0]);
        }
    }
}

bool Graph::isBipartit() {
    vector<int> team(n+1,0);
    queue<int> nodeQueue;

    for(int k=1;k<=n;k++) {
        if (!vizited[k]) {
            int node = k;
            vizited[node] = true;
            team[node] = 1;
            nodeQueue.push(node);

            while(!nodeQueue.empty()) {
                int temp = nodeQueue.front();
                nodeQueue.pop();

                for (int i = 0; i < connections[temp].size(); i++) {
                    if (!vizited[connections[temp][i]]) {
                        vizited[connections[temp][i]] = true;

                        if (team[temp] == team[connections[temp][i]]) return false;

                        if (team[temp] == 1) team[connections[temp][i]] = 2;
                        else team[connections[temp][i]] = 1;

                        nodeQueue.push(connections[temp][i]);
                    } else if (team[temp] == team[connections[temp][i]]) return false;
                }
            }
        }
    }

    return true;
}

void Graph::DFSforShortestBridge(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& vizited, queue<pair<int,int>>& waterNodes) {
    vizited[i][j] = true;

    if(i > 0 && grid[i-1][j] == 0) waterNodes.push(make_pair(i-1,j));
    if(i < grid.size()-1 && grid[i+1][j] == 0) waterNodes.push(make_pair(i+1,j));
    if(j > 0 && grid[i][j-1] == 0) waterNodes.push(make_pair(i,j-1));
    if(j < grid.size()-1 && grid[i][j+1] == 0) waterNodes.push(make_pair(i,j+1));

    if(i > 0 && grid[i-1][j] == 1 && !vizited[i-1][j]) DFSforShortestBridge(i-1,j,grid,vizited,waterNodes);
    if(i < grid.size()-1 && grid[i+1][j] == 1 && !vizited[i+1][j]) DFSforShortestBridge(i+1,j,grid,vizited,waterNodes);
    if(j > 0 && grid[i][j-1] == 1 && !vizited[i][j-1]) DFSforShortestBridge(i,j-1,grid,vizited,waterNodes);
    if(j < grid.size()-1 && grid[i][j+1] == 1 && !vizited[i][j+1]) DFSforShortestBridge(i,j+1,grid,vizited,waterNodes);
}

int Graph::shortestBridge(vector<vector<int>> &grid) {
    queue<pair<int,int>> waterNodes;
    vector<vector<bool>> vizited(grid.size(),vector<bool>(grid[0].size(),false));
    bool breakFor = false;

    for(int i=0;i<grid.size();i++) {
        if(breakFor) break;
        for (int j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 1) {
                DFSforShortestBridge(i, j, grid, vizited, waterNodes);
                breakFor = true;
                break;
            }
    }

    // there are 100 nodes in the grid so max size for counter = 100 * 100
    int minCounter = 1001;
    while(!waterNodes.empty()) {
        int i = waterNodes.front().first;
        int j = waterNodes.front().second;
        queue<pair<int,int>> bfsQ;
        vector<vector<int>> depth(grid.size(),vector<int>(grid.size(),0));
        waterNodes.pop();
        vector<vector<bool>> vizitedCopy = vizited;
        if(!vizitedCopy[i][j]) {
            vizitedCopy[i][j] = true;
            bfsQ.push(make_pair(i,j));

            while(!bfsQ.empty()) {
                pair<int,int> temp = bfsQ.front();
                bfsQ.pop();

                if(temp.first > 0 && grid[temp.first-1][temp.second] == 1 && !vizitedCopy[temp.first-1][temp.second]) {
                    if(minCounter > depth[temp.first][temp.second]) minCounter = depth[temp.first][temp.second];
                    break;
                }
                if(temp.first < grid.size()-1 && grid[temp.first+1][temp.second] == 1 && !vizitedCopy[temp.first+1][temp.second]) {
                    if(minCounter > depth[temp.first][temp.second]) minCounter = depth[temp.first][temp.second];
                    break;
                }
                if(temp.second > 0 && grid[temp.first][temp.second-1] == 1 && !vizitedCopy[temp.first][temp.second-1]) {
                    if(minCounter > depth[temp.first][temp.second]) minCounter = depth[temp.first][temp.second];
                    break;
                }
                if(temp.second < grid.size()-1 && grid[temp.first][temp.second+1] == 1 && !vizitedCopy[temp.first][temp.second+1]) {
                    if(minCounter > depth[temp.first][temp.second]) minCounter = depth[temp.first][temp.second];
                    break;
                }

                if(temp.first > 0 && grid[temp.first-1][temp.second] == 0 && !vizitedCopy[temp.first-1][temp.second]) {
                    vizitedCopy[temp.first-1][temp.second] = true;
                    depth[temp.first-1][temp.second] = depth[temp.first][temp.second] + 1;
                    bfsQ.push(make_pair(temp.first-1,temp.second));
                }
                if(temp.first < grid.size()-1 && grid[temp.first+1][temp.second] == 0 && !vizitedCopy[temp.first+1][temp.second]) {
                    vizitedCopy[temp.first+1][temp.second] = true;
                    depth[temp.first+1][temp.second] = depth[temp.first][temp.second] + 1;
                    bfsQ.push(make_pair(temp.first+1,temp.second));
                }
                if(temp.second > 0 && grid[temp.first][temp.second-1] == 0 && !vizitedCopy[temp.first][temp.second-1]) {
                    vizitedCopy[temp.first][temp.second-1] = true;
                    depth[temp.first][temp.second-1] = depth[temp.first][temp.second] + 1;
                    bfsQ.push(make_pair(temp.first,temp.second-1));
                }
                if(temp.second < grid.size()-1 && grid[temp.first][temp.second+1] == 0 && !vizitedCopy[temp.first][temp.second+1]) {
                    vizitedCopy[temp.first][temp.second+1] = true;
                    depth[temp.first][temp.second+1] = depth[temp.first][temp.second] + 1;
                    bfsQ.push(make_pair(temp.first,temp.second+1));
                }
            }
        }
    }

    return minCounter+1;
}

vector<int> Graph::topologicalSort() {
    vector<int> sortedVector;
    queue<int> nodes;
    int countEdgeRemoval = 0;

    if(numberOfEdges == 0) {
        for(int i=0;i<n;i++)
            sortedVector.push_back(i);
        return sortedVector;
    }

    for(int i=0;i<n;i++)
        if(precedence[i] == 0)
            nodes.push(i);

    while(!nodes.empty()) {
        int temp = nodes.front();
        nodes.pop();

        sortedVector.push_back(temp);

        for(int i=0;i<connections[temp].size();i++) {
            precedence[connections[temp][i]]--;
            countEdgeRemoval++;
            if(precedence[connections[temp][i]] == 0) {
                nodes.push(connections[temp][i]);
            }
            // deleting v[2] places v[2] in position v[1] so we need to decrement i when deleting
            connections[temp].erase(connections[temp].begin() + i);
            i--;
        }
    }

    if(countEdgeRemoval != numberOfEdges) return {};

    return sortedVector;
}

bool Graph::equationsPossible(vector<std::string> &equations) {
    vector<int> team('z' - 'a' + 1,0);
    vector<vector<pair<int,bool>>> connections('z'-'a'+1);
    vector<bool> vizited('z'-'a'+1,false);
    queue<int> nodeQueue;
    int teamCounter = 1;

    for(int i=0;i<equations.size();i++) {
        if(equations[i][1] == '!') {
            if(equations[i][0] != equations[i][3]) {
                connections[equations[i][0]-'a'].push_back(make_pair(equations[i][3] - 'a', false));
                connections[equations[i][3]-'a'].push_back(make_pair(equations[i][0] - 'a',false));
            } else return false;
        }
        else
            if(equations[i][0] != equations[i][3]) {
                connections[equations[i][0]-'a'].push_back(make_pair(equations[i][3] - 'a', true));
                connections[equations[i][3]-'a'].push_back(make_pair(equations[i][0] - 'a', true));
            }
    }

    for(int i=0;i<26;i++) {
        if(!vizited[i] && connections[i].size() > 0) {
            vizited[i] = true;
            if(team[i] == 0) team[i] = teamCounter++;
            nodeQueue.push(i);

            while(!nodeQueue.empty()) {
                int temp = nodeQueue.front();
                nodeQueue.pop();

                for(int i=0;i<connections[temp].size();i++) {
                    if(!vizited[connections[temp][i].first]) {
                        vizited[connections[temp][i].first] = true;

                        if(connections[temp][i].second == false && team[connections[temp][i].first] == 0)
                            team[connections[temp][i].first] = teamCounter++;
                        else if(connections[temp][i].second == true && team[connections[temp][i].first] == 0)
                            team[connections[temp][i].first] = team[temp];

                        if(connections[temp][i].second == true && team[connections[temp][i].first] != team[temp])
                            return false;

                        if(connections[temp][i].second == false && team[connections[temp][i].first] == team[temp])
                            return false;

                        nodeQueue.push(connections[temp][i].first);
                    } else {
                        if(connections[temp][i].second == true && team[connections[temp][i].first] != team[temp])
                            return false;

                        if(connections[temp][i].second == false && team[connections[temp][i].first] == team[temp])
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

vector<int> Graph::eventualSafeNodes(vector<vector<int>> &graph) {
    vector<int> sortedVector;
    vector<int> subsequent(graph.size(), 0);
    vector<vector<int>> reverseGraph(graph.size());
    queue<int> nodes;

    for(int i=0;i<graph.size();i++) {
        if(graph[i].size() > 0) subsequent[i] += graph[i].size();
        for(int j=0;j<graph[i].size();j++) {
            reverseGraph[graph[i][j]].push_back(i);
        }
    }

    for(int i=0;i<subsequent.size();i++)
        if(subsequent[i] == 0)
            nodes.push(i);

    while(!nodes.empty()) {
        int temp = nodes.front();
        nodes.pop();

        sortedVector.push_back(temp);

        for(int i=0;i<reverseGraph[temp].size();i++) {
            subsequent[reverseGraph[temp][i]]--;
            if(subsequent[reverseGraph[temp][i]] == 0) {
                nodes.push(reverseGraph[temp][i]);
            }
            // deleting v[2] places v[2] in position v[1] so we need to decrement i when deleting
            reverseGraph[temp].erase(reverseGraph[temp].begin() + i);
            i--;
        }
    }

    sort(sortedVector.begin(),sortedVector.end());
    return sortedVector;
}

void Graph::DFSforCriticalConnections(int node, vector<int> &level, vector<int> &low, vector<vector<int>>& result) {
    vizited[node] = true;
    for(int i=0;i<connections[node].size();i++) {
        if(!vizited[connections[node][i]]) {
            level[connections[node][i]] = level[node] + 1;
            low[connections[node][i]] = level[node] + 1;

            DFSforCriticalConnections(connections[node][i],level,low,result);

            if(low[node] >= low[connections[node][i]])
                low[node] = low[connections[node][i]];

            if(low[connections[node][i]] > level[node])
                result.push_back({node,connections[node][i]});
        }
        else {
            if(level[node]-1 > level[connections[node][i]] && low[node] >= level[connections[node][i]])
                low[node] = level[connections[node][i]];
        }
    }
}

vector<vector<int>> Graph::criticalConnections() {
    vector<int> level(n,0),low(n,0);
    vector<vector<int>> result;

    DFSforCriticalConnections(0,level,low,result);

    return result;
}

int main() {
    // Possible Bipartition Tests
    /*vector<vector<int>> d = {{1,2},{3,4},{5,6},
                            {6,7},{8,9},{7,8}};

    vector<vector<int>> d2 = {{1,2},{1,3},{2,4}};
    vector<vector<int>> d3 = {{1,2},{1,3},{2,3}};
    vector<vector<int>> d4 = {{1,2},{3,4},{4,5},{3,5}};
    vector<vector<int>> d5 = {{39,46},{4,41},{3,35},{8,44},{22,44},{7,49},{28,41},{7,25},{6,35},{2,22},{34,35},{3,7},{1,11},{11,48},{8,24},{6,7},{38,40},{37,48},{3,45},{44,45},{4,46},{23,35},{28,46},{7,28},{35,36},{18,20},{8,15},{17,41},{13,35},{6,22},{22,48},{22,39},{4,35},{8,38},{23,41},{10,41},{6,41},{18,48},{16,41},{37,44},{8,12},{18,36},{16,18},{7,44},{3,18},{10,46},{20,37},{2,37},{11,49},{30,45},{28,37},{23,37},{22,23},{5,37},{29,40},{16,35},{22,26},{46,49},{18,26},{8,9},{24,46},{8,28},{11,29},{22,24},{7,15},{4,37},{9,40},{8,32},{23,40},{40,42},{33,40},{17,45},{40,48},{12,41},{43,45},{38,41},{45,47},{12,18},{7,31},{34,37},{8,48},{4,11},{46,48},{2,7},{17,40},{12,46},{22,49},{46,50},{37,50},{22,36},{22,43},{41,44},{13,22},{11,16},{7,47},{14,37},{37,43},{13,37},{26,40},{19,41},{46,47},{16,22},{19,22},{22,33},{11,19},{35,44},{7,33},{41,49},{38,45},{25,35},{3,37},{15,22},{6,18},{11,30},{5,41},{8,33},{1,46},{31,46},{41,42},{18,28},{15,41},{35,49},{25,41},{20,45},{26,46},{8,43},{5,45},{28,40},{1,18},{23,46},{13,18},{35,38},{8,49},{11,44},{18,33},{4,7},{5,7},{10,11},{37,49},{9,22},{4,45},{32,45},{32,37},{29,35},{26,35},{7,29},{1,37},{8,14},{5,11},{18,29},{18,49},{21,41},{17,35},{7,10},{22,38},{40,43},{5,35},{33,35},{6,40},{34,40},{22,34},{16,40},{19,46},{18,39},{24,35},{19,35},{18,50},{8,17},{11,12},{27,35},{8,47},{7,9},{7,36},{8,34},{7,26},{31,41},{29,41},{10,45},{9,35},{33,46},{11,32},{34,45},{42,46},{15,40},{40,50},{30,40},{25,40},{15,37}};

    Graph g(50,d);
    cout << g.isBipartit();*/

    // Shortest Bridge Tests
    /*vector<vector<int>> t1 = {{0,1},{1,0}};
    vector<vector<int>> t2 = {{0,1,0},{0,0,0},{0,0,1}};
    vector<vector<int>> t3 = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    vector<vector<int>> t4 = {{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};

    Graph g;
    cout << g.shortestBridge(t4);*/

    // Course Schedule 2 Tests
    /*vector<vector<int>> prerequisites1 = {{1,0}};
    vector<vector<int>> prerequisites2 = {{1,0},{2,0},{3,1},{3,2}};
    vector<vector<int>> prerequisites3 = {};

    Graph g(2,prerequisites1,true,true);

    vector<int> result = g.topologicalSort();
    for(auto i:result) cout<<i<<" ";*/

    // Satifiability of Equality Equations - this approach doesnt work
    /*Graph g;
    vector<vector<string>> inputs = {{"a==b","b!=a"},{"b==a","a==b"},{"a==b","b==c","a!=c"},{"c==c","b==d","x!=z"},{"a!=b","b!=c","c!=a"},{"b==b","b==e","e==c","d!=e"},{"a!=a"}};
    vector<bool> solutions = {false,true,false,true,true,true,false};

    for(int i=0;i<solutions.size();i++) {
        cout<<"TEST "<<i<<": ";
        if(solutions[i] != g.equationsPossible(inputs[i])) cout<<"FAILED\n";
        else cout<<"PASSED\n";
    }*/

    // Find Eventual Safe Nodes
    /*Graph g;
    vector<vector<int>> graph1 = {{1,2},{2,3},{5},{0},{5},{},{}};
    vector<vector<int>> graph2 = {{1,2,3,4},{1,2},{3,4},{0,4},{}};
    vector<vector<int>> graph3 = {{1},{2},{0,3},{}};
    vector<int> result = g.eventualSafeNodes(graph3);
    cout<<"\n\tRESULT: "<<endl;
    for(auto it:result) cout<<it<<" ";
    cout<<endl;*/

    /*vector<vector<int>> connections1 = {{0,1},{1,2},{2,0},{1,3}};
    vector<vector<int>> connections2 = {{0,1}};
    Graph g(2,connections2);
    for(auto it:g.criticalConnections())
        cout<<"("<<it[0]<<", "<<it[1]<<") ";*/
    return 0;
}
