#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

// this is used for matrix traversal, to get neighbours of current element
class Neighbours {
private:
    // i = row j = column
    // rowLength = depends if matrix is square or not
    int i,j,indexedBy,rowLength;
    // the matrix to get the values, passed by reference
    const vector<vector<int>> &grid;
public:
    // returns -1 if next element is out of bounds
    // otherwise returns the indices as a pair
    int getValue(pair<int,int> indices) {
        if(i + indices.first >= indexedBy && i + indices.first < grid.size()
           && j + indices.second >= indexedBy && j + indices.second < rowLength)
            return grid[i + indices.first][j + indices.second];

        return -1;
    }

    // returns new calculated indices
    pair<int, int> getIndices(pair<int, int> indices) const {
        return make_pair(i + indices.first, j + indices.second);
    }

    // constructor indexedBy if matrix starts with row/col 1
    Neighbours(pair<int,int> indices ,const vector<vector<int>> &grid, int indexedBy = 0, bool isSquare = true):grid(grid) {
        this->i = indices.first;
        this->j = indices.second;
        this->indexedBy = indexedBy;
        if(isSquare == false) {
            this->rowLength = grid[0].size();
        }
        else this->rowLength = grid.size();
    }
};

class Graph {
private:
    // n = number of nodes
    int n, numberOfEdges;
    vector<vector<int>> connections;
    vector<bool> vizited;
    vector<int> precedence;
    vector<bool> markedNodes;
    // a bool to distinguish between the 2 topological sort problems
    bool findCompleteTopologicalSort;
    // for problem Padure
    pair<int,int> startNode, destinationNode;
    // for matrix traversal to get all directions: N S W E
    vector<pair<int,int>> directions = {{1,0}, {-1,0}, {0,-1}, {0,1}};

    // for union find, size for the rank of trees
    vector<int> parent, size;

    // private helper functions
    void DFSforCriticalConnections(int node, vector<int>& level, vector<int>& low, vector<vector<int>>& result);
    void DFSforShortestBridge(pair<int, int> indices, vector<vector<int>>& grid, vector<vector<bool>>& vizited, queue<pair<int,int>>& waterNodes);

    int find(int node);
    void Union(int firstNode, int secondNode);

public:
    // constructors
    Graph();
    // any value is good, as it is the constructor for the union problem
    Graph(bool needsUnion);
    Graph(int n, int numberOfEdges, vector<pair<int,int>> &edges);
    Graph(int n, vector<vector<int>> &connections, vector<bool> &markedNodes);
    Graph(int n, vector<vector<int>> &connections, bool isOriented = false, bool needsPrecedence = false);
    Graph(pair<int,int> startNode, pair<int,int> destinationNode);

    // resolved functions
    vector<int> getBipartition();
    bool isBipartit();
    vector<vector<int>> criticalConnections();
    void transposeGraph(vector<vector<int>> &graph);
    vector<int> topologicalSort();
    vector<int> findSafeNodes(vector<vector<int>> &graph);
    bool equationsPossible(vector<string> &equations);

    // optimize this to be faster
    int shortestBridge(vector<vector<int>>& grid);

    // codeforces methods
    string directedGraphPathRestriction(vector<pair<int,int>> &edges);
    pair<int,int> BFSFromOneNodeToAnother(int startNode);
    int getMinimumMaximumDistanceBetweenTwoMarkedNodes(int startNode = 0);

    // infoarena problems
    int shortestCostInWeightedGraph(vector<vector<int>> &grid);
};

Graph::Graph() {
    this->findCompleteTopologicalSort = true;
}

Graph::Graph(bool needsUnion) {
    this->parent.resize(27);
    this->size.resize(27,0);
    for (int i=0;i<parent.size();i++) parent[i] = i;
}

Graph::Graph(int n, vector<vector<int>> &connections, vector<bool> &markedNodes): connections(connections), markedNodes(markedNodes) {
    this->n = n;
    this->vizited.resize(n+1,false);
}

Graph::Graph(int n, int numberOfEdges, vector<pair<int,int>> &edges) {
    this->n = n;
    this->numberOfEdges = numberOfEdges;
    this->connections.resize(n+1);

    for (int i=0;i<edges.size();i++) {
        this->connections[edges[i].first].push_back(edges[i].second);
        this->connections[edges[i].second].push_back(edges[i].first);
    }

    this->vizited.resize(n+1, false);
}

Graph::Graph(int n, vector<vector<int>> &connections, bool isOriented, bool needsPrecedence) {
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

Graph::Graph(pair<int, int> startNode, pair<int, int> destinationNode) {
    this->startNode = startNode;
    this->destinationNode = destinationNode;
}

vector<int> Graph::getBipartition() {
    // team = represents colors
    vector<int> team(n+1,0);
    queue<int> nodeQueue;

    // if the graph is not connected we go trough all the nodes
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

                        // if theres a connection between 2 nodes and they are on the same team
                        // return an empty array denoting that it is not a Bipartit graph
                        if (team[temp] == team[connections[temp][i]]) return {};

                        // assign new teams
                        if (team[temp] == 1) team[connections[temp][i]] = 2;
                        else team[connections[temp][i]] = 1;

                        nodeQueue.push(connections[temp][i]);
                    } else if (team[temp] == team[connections[temp][i]]) return {}; // to check even if we have visited (for cycles)
                }
            }
        }
    }

    return team;
}

bool Graph::isBipartit() {
    // it getBipartiton returns empty array -> its not bipartit
    if (this->getBipartition().empty()) return false;
    return true;
}

string Graph::directedGraphPathRestriction(vector<pair<int,int>> &edges) {
    vector<int> teams = this->getBipartition();
    string result = "";

    if(!teams.empty()) result += "YES\n";
    else return "NO\n";

    // a bipartit problem, for each edge the orientation depends in which team the node is
    for(auto it:edges) {
        if (teams[it.first] == 1) result += "1";
        else if(teams[it.first] == 2) result += "0";
    }

    return result;
}

void Graph::DFSforShortestBridge(pair<int, int> indices, vector<vector<int>>& grid, vector<vector<bool>>& vizited, queue<pair<int,int>>& waterNodes) {
    vizited[indices.first][indices.second] = true;
    Neighbours d(indices, grid);

    for(auto it:directions) {
        if (d.getValue(it) == 0) waterNodes.push(d.getIndices(it));
    }

    for(auto it:directions) {
        if (d.getValue(it) == 1 && !vizited[d.getIndices(it).first][d.getIndices(it).second])
            DFSforShortestBridge(
                    d.getIndices(it),
                    grid, vizited, waterNodes
            );
    }
}

int Graph::shortestBridge(vector<vector<int>> &grid) {
    queue<pair<int,int>> waterNodes;
    vector<vector<bool>> vizited(grid.size(),vector<bool>(grid[0].size(),false));
    bool breakFor = false;

    // find first value of 1 and then use DFS to go trough the whole island
    for(int i=0;i<grid.size();i++) {
        if(breakFor) break;
        for (int j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 1) {
                DFSforShortestBridge(make_pair(i,j), grid, vizited, waterNodes);
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
        vector<vector<bool>> vizitedCopy = vizited;

        waterNodes.pop();

        if(!vizitedCopy[i][j]) {
            vizitedCopy[i][j] = true;
            bfsQ.push(make_pair(i,j));

            while(!bfsQ.empty()) {
                pair<int,int> current = bfsQ.front();
                Neighbours d(current, grid);
                bfsQ.pop();

                bool breakLoop = false;
                for (auto it:directions) {
                    bool breakFor = false;
                    if (d.getValue(it) == 1 && !vizitedCopy[d.getIndices(it).first][d.getIndices(it).second]) {
                        if (minCounter > depth[current.first][current.second])
                            minCounter = depth[current.first][current.second];

                        breakLoop = true;
                        break;
                    }
                }

                if(breakLoop) break;

                for (auto it:directions) {
                    if (d.getValue(it) == 0 && !vizitedCopy[d.getIndices(it).first][d.getIndices(it).second]) {
                        vizitedCopy[d.getIndices(it).first][d.getIndices(it).second] = true;
                        depth[d.getIndices(it).first][d.getIndices(it).second] =
                                depth[current.first][current.second] + 1;
                        bfsQ.push(d.getIndices(it));
                    }
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

    // if there are no edges -> the vector with all nodes
    if(numberOfEdges == 0 && findCompleteTopologicalSort) {
        for(int i=0;i<n;i++)
            sortedVector.push_back(i);
        return sortedVector;
    }

    // find the nodes with precedence 0 and put them in the nodeQueue
    for(int i=0;i<precedence.size();i++)
        if(precedence[i] == 0)
            nodes.push(i);

    while(!nodes.empty()) {
        int temp = nodes.front();
        nodes.pop();

        sortedVector.push_back(temp);

        for(int i=0;i<connections[temp].size();i++) {
            // "remove" the edge from the graph
            precedence[connections[temp][i]]--;
            countEdgeRemoval++;
            // if new precedence is 0 push the node in the queue
            if(precedence[connections[temp][i]] == 0) {
                nodes.push(connections[temp][i]);
            }
            // deleting v[2] places v[2] in position v[1] so we need to decrement i when deleting
            connections[temp].erase(connections[temp].begin() + i);
            i--;
        }
    }

    // if we didnt remove all edges it means that the graph has at leas one cycle
    if(countEdgeRemoval != numberOfEdges && findCompleteTopologicalSort) return {};

    return sortedVector;
}

// method to reverse graph, used for findSafeStates
void Graph::transposeGraph(vector<vector<int>> &graph) {
    // here precedence is actually subsequence
    precedence.resize(graph.size(),0);
    // connections becomes there reverse graph
    connections.resize(graph.size());

    for(int i=0;i<graph.size();i++) {
        if(graph[i].size() > 0) precedence[i] += graph[i].size();
        for(int j=0;j<graph[i].size();j++) {
            connections[graph[i][j]].push_back(i);
        }
    }

    this->findCompleteTopologicalSort = false;
}

vector<int> Graph::findSafeNodes(vector<vector<int>> &graph) {
    // reverse the graph
    this->transposeGraph(graph);
    // get the topological sort
    vector<int> sortedVector = this->topologicalSort();
    // sort the nodes
    sort(sortedVector.begin(),sortedVector.end());

    return sortedVector;
}

void Graph::DFSforCriticalConnections(int node, vector<int> &level, vector<int> &low, vector<vector<int>>& result) {
    // level = depth of each node
    // low = lowest level reachable from each node
    vizited[node] = true;
    for(int i=0;i<connections[node].size();i++) {
        if(!vizited[connections[node][i]]) {
            level[connections[node][i]] = level[node] + 1;
            low[connections[node][i]] = level[node] + 1;

            DFSforCriticalConnections(connections[node][i],level,low,result);

            // checks to see if next node can take us lower
            if(low[node] >= low[connections[node][i]])
                low[node] = low[connections[node][i]];

            // if its true it means that there is no return edge
            // so we got a solution
            if(low[connections[node][i]] > level[node])
                result.push_back({node,connections[node][i]});
        }
        else {
            // if the next node is vizited, it means we have a cycle, and can go lower
            // so we update accordingly
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

pair<int,int> Graph::BFSFromOneNodeToAnother(int startNode) {
    queue<int> nodeQueue;
    vector<int> depth(n+1,0);
    // first value is the marked node furthest from start node, second the depth
    pair<int,int> maxDepthMarkedNode(0,0);

    vizited[startNode] = true;
    nodeQueue.push(startNode);

    while(!nodeQueue.empty()) {
        int current = nodeQueue.front();
        nodeQueue.pop();

        for(int i=0;i<connections[current].size();i++) {
            if (!vizited[connections[current][i]]) {
                vizited[connections[current][i]] = true;
                depth[connections[current][i]] += depth[current] + 1;

                // if current node is marked and its depth is lower than the current depth -> update maxDepthMarkedNode
                if(markedNodes[connections[current][i]] && maxDepthMarkedNode.second < depth[connections[current][i]]) {
                    maxDepthMarkedNode = {connections[current][i], depth[connections[current][i]]};
                }
                nodeQueue.push(connections[current][i]);
            }
        }
    }

    return maxDepthMarkedNode;
}

int Graph::getMinimumMaximumDistanceBetweenTwoMarkedNodes(int startNode) {
    // here we need to call BFSFromOneNodeToAnother on a random marked node
    pair<int,int> firstResult = this->BFSFromOneNodeToAnother(startNode);

    // clear the vizited vector
    if(!this->vizited.empty()) this->vizited.clear();
    this->vizited.resize(n+1,false);

    // call it again for the node max depth marked node from the first BFS
    pair<int,int> secondResult = this->BFSFromOneNodeToAnother(firstResult.first);

    // return the maximum out of those 2 , add 1 , divide by 2
    return (max(firstResult.second,secondResult.second) + 1)/2;
}

int Graph::shortestCostInWeightedGraph(vector<vector<int>> &grid) {
    deque <pair<int,int>> nodeQueue;
    // depth but acts more like a cost matrix
    vector<vector<int>> depth(grid.size(), vector<int>(grid[0].size(),INT_MAX));
    depth[startNode.first][startNode.second] = 0;
    nodeQueue.push_back(startNode);

    while(!nodeQueue.empty()) {
        pair<int,int> current = nodeQueue.front();
        nodeQueue.pop_front();
        Neighbours d(current, grid,1,false);

        for (auto it:directions) {
            pair<int,int> temp = d.getIndices(it);
            int newRow = temp.first, newCol = temp.second;

            // if depth of new node is higher than current node and
                // cells are different, then give new node depth = current node depth + 1 and push it back
                // else give it the same depth and push it front
            // we do this so we can prioritize the path that doesnt cost anything
            if(d.getValue(it) != -1 && depth[newRow][newCol] > depth[current.first][current.second])
            {
                if(grid[newRow][newCol] != grid[current.first][current.second]) {
                    depth[newRow][newCol] = depth[current.first][current.second] + 1;
                    nodeQueue.push_back(temp);
                }
                else {
                    depth[newRow][newCol] = depth[current.first][current.second];
                    nodeQueue.push_front(temp);
                }
            }
        }
    }

    return depth[destinationNode.first][destinationNode.second];
}

int Graph::find(int node) {
    if (parent[node] == node) return node;

    // find the root node and do compression
    int result = find(parent[node]);
    parent[node] = result;
    return result;
}

void Graph::Union(int firstNode, int secondNode) {
    int firstNodeRoot = find(firstNode);
    int secondNodeRoot = find(secondNode);

    if (size[firstNode] < size[secondNode]) {
        parent[firstNodeRoot] = secondNodeRoot;
        return;
    }

    if (size[firstNode] > size[secondNode]) {
        parent[secondNodeRoot] = firstNodeRoot;
        return;
    }

    // if both sizes are equal then size goes up by one and it doesnt matter which ones the parent
    parent[firstNodeRoot] = secondNodeRoot;
    size[secondNodeRoot]++;
}

bool Graph::equationsPossible(vector<std::string> &equations) {

    // watch out for test case where a == b, b != c, c == a
    // sort the vector ? or traverse trough it twice?
    for (auto it:equations) {
        int firstLetter = it[0] - 'a';
        int secondLetter = it[3] - 'a';

        if (it[1] == '=')
            Union(firstLetter,secondLetter);
    }

    for (auto it:equations) {
        int firstLetter = it[0] - 'a';
        int secondLetter = it[3] - 'a';

        if (it[1] == '!' && find(firstLetter) == find(secondLetter))
            return false;
    }

    return true;
}

int main() {
    // Possible Bipartition Tests
    /*vector<vector<int>> d = {{1,2},{3,4},{5,6},
                            {6,7},{8,9},{7,8}};

    vector<vector<int>> d2 = {{1,2},{1,3},{2,4}};
    vector<vector<int>> d3 = {{1,2},{1,3},{2,3}};
    vector<vector<int>> d4 = {{1,2},{3,4},{4,5},{3,5}};
    vector<vector<int>> d5 = {{39,46},{4,41},{3,35},{8,44},{22,44},{7,49},{28,41},{7,25},{6,35},{2,22},{34,35},{3,7},{1,11},{11,48},{8,24},{6,7},{38,40},{37,48},{3,45},{44,45},{4,46},{23,35},{28,46},{7,28},{35,36},{18,20},{8,15},{17,41},{13,35},{6,22},{22,48},{22,39},{4,35},{8,38},{23,41},{10,41},{6,41},{18,48},{16,41},{37,44},{8,12},{18,36},{16,18},{7,44},{3,18},{10,46},{20,37},{2,37},{11,49},{30,45},{28,37},{23,37},{22,23},{5,37},{29,40},{16,35},{22,26},{46,49},{18,26},{8,9},{24,46},{8,28},{11,29},{22,24},{7,15},{4,37},{9,40},{8,32},{23,40},{40,42},{33,40},{17,45},{40,48},{12,41},{43,45},{38,41},{45,47},{12,18},{7,31},{34,37},{8,48},{4,11},{46,48},{2,7},{17,40},{12,46},{22,49},{46,50},{37,50},{22,36},{22,43},{41,44},{13,22},{11,16},{7,47},{14,37},{37,43},{13,37},{26,40},{19,41},{46,47},{16,22},{19,22},{22,33},{11,19},{35,44},{7,33},{41,49},{38,45},{25,35},{3,37},{15,22},{6,18},{11,30},{5,41},{8,33},{1,46},{31,46},{41,42},{18,28},{15,41},{35,49},{25,41},{20,45},{26,46},{8,43},{5,45},{28,40},{1,18},{23,46},{13,18},{35,38},{8,49},{11,44},{18,33},{4,7},{5,7},{10,11},{37,49},{9,22},{4,45},{32,45},{32,37},{29,35},{26,35},{7,29},{1,37},{8,14},{5,11},{18,29},{18,49},{21,41},{17,35},{7,10},{22,38},{40,43},{5,35},{33,35},{6,40},{34,40},{22,34},{16,40},{19,46},{18,39},{24,35},{19,35},{18,50},{8,17},{11,12},{27,35},{8,47},{7,9},{7,36},{8,34},{7,26},{31,41},{29,41},{10,45},{9,35},{33,46},{11,32},{34,45},{42,46},{15,40},{40,50},{30,40},{25,40},{15,37}};

    Graph g(3,d3);
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
    /*vector<vector<string>> inputs = {{"a==b","b!=a"},{"b==a","a==b"},{"a==b","b==c","a!=c"},{"c==c","b==d","x!=z"},{"a!=b","b!=c","c!=a"},{"b==b","b==e","e==c","d!=e"},{"a!=a"}};
    vector<bool> solutions = {false,true,false,true,true,true,false};

    for(int i=0;i<solutions.size();i++) {
        Graph g(true);
        cout<<"TEST "<<i<<": ";
        if(solutions[i] != g.equationsPossible(inputs[i])) cout<<"FAILED\n";
        else cout<<"PASSED\n";
    }*/

    // Find Eventual Safe Nodes
    /*Graph g;
    vector<vector<int>> graph1 = {{1,2},{2,3},{5},{0},{5},{},{}};
    vector<vector<int>> graph2 = {{1,2,3,4},{1,2},{3,4},{0,4},{}};
    vector<vector<int>> graph3 = {{1},{2},{0,3},{}};
    vector<int> result = g.findSafeNodes(graph3);
    cout<<"\n\tRESULT: "<<endl;
    for(auto it:result) cout<<it<<" ";
    cout<<endl;*/

    // Critical Connections Tests
    /*vector<vector<int>> connections1 = {{0,1},{1,2},{2,0},{1,3}};
    vector<vector<int>> connections2 = {{0,1}};
    Graph g(2,connections2);
    for(auto it:g.criticalConnections())
        cout<<"("<<it[0]<<", "<<it[1]<<") ";*/

    // Graph Without Long Directed Paths
    /*int n,m,i,j;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for (int k=0;k<m;k++)
    {
        cin >> i >> j;
        edges.push_back(make_pair(i,j));
    }

    Graph g(n,m,edges);
    cout << g.directedGraphPathRestriction(edges);*/

    // Minimum Maximum Distance
    /*int t,n,k;

    cin >> t;
    for (int i=0;i<t;i++) {
        cin >> n >> k;
        vector<bool> marked(n+1,false);
        vector<vector<int>> connections(n+1);
        int temp;
        for (int j=0;j<k;j++) {
            cin >> temp;
            marked[temp] = true;
        }
        for (int j=0;j<n-1;j++) {
            int node1, node2;
            cin >> node1 >> node2;
            connections[node1].push_back(node2);
            connections[node2].push_back(node1);
        }
        Graph g(n,connections, marked);
        cout << g.getMinimumMaximumDistanceBetweenTwoMarkedNodes(temp) << endl;
    }*/

    // Minimum Cost Path in Forest
        // CHANGE PATH WHEN UPLOADING TO INFOARENA
    /*ifstream f("../padure.in");
    ofstream g("../padure.out");

    int n,m,pl,pc,cl,cc;
    f >> n >> m >> pl >> pc >> cl >> cc;
    vector<vector<int>> grid(n+1,vector<int>(m+1,0));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            f >> grid[i][j];

    Graph ob(make_pair(pl,pc), make_pair(cl,cc));

    g << ob.shortestCostInWeightedGraph(grid);

    f.close();
    g.close();*/

    return 0;
}
