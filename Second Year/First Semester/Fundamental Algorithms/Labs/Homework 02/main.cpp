#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>
#include <cmath>
#include <iomanip>

using namespace std;

double distance(pair<int, int>, pair<int, int>);

struct Edge {
    long long node, cost;

    bool operator<(const Edge& e) const {
        return this->cost > e.cost;
    }
};

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
    // adjacency list
    vector<vector<int>> connections;
    // adjacency list with weighted connections
    vector<vector<Edge>> connectionsWithCost;
    // for matrix traversal to get all directions: N S W E
    vector<pair<int,int>> directions = {{1,0}, {-1,0}, {0,-1}, {0,1}};

    // private helper functions
    void DFSforCriticalConnections(int node, vector<int> &level, vector<int> &low, vector<vector<int>> &result,
                                   vector<bool> &vizited);
    void DFSforShortestBridge(pair<int, int> indices, vector<vector<int>>& grid, vector<vector<bool>>& vizited, queue<pair<int,int>>& waterNodes);

public:
    // constructors
    Graph();
    Graph(int n);
    Graph(int n, int numberOfEdges);
    Graph(vector<vector<int>> &connections);
    Graph(int n, vector<vector<Edge>>& connectionsWithCost);
    Graph(int n, int numberOfEdges, vector<vector<Edge>>& connectionsWithCost);
    Graph(int n, int numberOfEdges, vector<pair<int,int>> &edges);
    // copy = to distinguish between copying a full
    // adjacency list or initializing it
    Graph(int n, vector<vector<int>> &connections, int copy);
    Graph(int n, vector<vector<int>> &connections, bool isOriented = false);

    // returns a vector with a bipartition or empty if its not possible
    vector<int> getBipartition();
    // true/false is its bipartite
    bool isBipartite();
    // returns vector with edges that are critical connections
    vector<vector<int>> criticalConnections();
    // transposes the graph
    void transposeGraph();
    // returns the topologic order of the graph, parameter is used if the graph is DAG or not
    vector<int> topologicalSort(bool = true);
    int shortestBridge(vector<vector<int>>& grid);

    // <node, distance> between 2 marked nodes
    // startNode = nodes to start search from
    pair<int,int> MaxDistanceToMarkedNode(int startNode, vector<bool> &markedNodes);

    // first parameter = start node
    // second one = destination node
    int shortestCostInWeightedGraph(pair<int,int>, pair<int,int>);

    // cablaj & camionas
    double MstForCoordinates(vector<pair<int, int>> &coordinates);
    vector<int> BfsZeroOne(int source);

    int shortestPathWithMaxStops(int source, int destination, int maxStops);

    // returning a pointer to the dynamically alocated vector
    // so we can avoid copying
    const vector<vector<int>>* floydWarshall() const;
    const vector<long long int> *dijkstraFromSource(int source = 1) const;

    // getters
    int getSize() const { return n; }
};

Graph::Graph() { }

Graph::Graph(int n) {
    this->n = n;
}

Graph::Graph(int n, vector<vector<int>> &connections, int copy): connections(connections){
    this->n = n;
}

Graph::Graph(int n, vector<vector<Edge>> &connectionsWithCost) {
    this->n = n;
    this->connectionsWithCost = connectionsWithCost;
}

Graph::Graph(int n, int numberOfEdges, vector<vector<Edge>> &connectionsWithCost) {
    this->n = n;
    this->numberOfEdges = numberOfEdges;
    this->connectionsWithCost = connectionsWithCost;
}

Graph::Graph(int n, int numberOfEdges, vector<pair<int,int>> &edges) {
    this->n = n;
    this->numberOfEdges = numberOfEdges;
    this->connections.resize(n+1);

    for (int i=0;i<edges.size();i++) {
        this->connections[edges[i].first].push_back(edges[i].second);
        this->connections[edges[i].second].push_back(edges[i].first);
    }
}

Graph::Graph(int n, vector<vector<int>> &connections, bool isOriented) {
    this->n = n;
    this->connections.resize(n+1);
    this->numberOfEdges = connections.size();

    if (isOriented == false) {
        for (int i = 0; i < connections.size(); i++) {
            this->connections[connections[i][0]].push_back(connections[i][1]);
            this->connections[connections[i][1]].push_back(connections[i][0]);
        }
    }
    else {
        for(int i=0;i<connections.size();i++) {
            this->connections[connections[i][1]].push_back(connections[i][0]);
        }
    }
}

Graph::Graph(int n, int numberOfEdges) {
    this->n = n;
    this->numberOfEdges = numberOfEdges;
}

Graph::Graph(vector<vector<int>> &connections) {
    this->n = connections.size();
    this->connections = connections;
}

vector<int> Graph::getBipartition() {
    // team = represents colors
    vector<int> team(n+1,0);
    queue<int> nodeQueue;
    vector<bool> vizited (n+1, false);

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

bool Graph::isBipartite() {
    // it getBipartiton returns empty array -> its not bipartit
    if (this->getBipartition().empty()) return false;
    return true;
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

vector<int> Graph::topologicalSort(bool isDAG) {
    vector<int> sortedVector;
    queue<int> nodes;
    vector<int> precedence(n, 0);
    int countEdgeRemoval = 0;

    for(int i=0; i<connections.size(); i++) {
        for (auto it:connections[i])
            precedence[it]++;
    }

    // if there are no edges -> the vector with all nodes
    if(numberOfEdges == 0 && isDAG) {
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
    if(countEdgeRemoval != numberOfEdges && isDAG) return {};

    return sortedVector;
}

void Graph::transposeGraph() {
    vector<vector<int>> transposed(connections.size());

    for(int i=0;i<connections.size();i++) {
        for(int j=0;j<connections[i].size();j++) {
            transposed[connections[i][j]].push_back(i);
        }
    }

    connections = transposed;
}

void Graph::DFSforCriticalConnections(int node, vector<int> &level, vector<int> &low, vector<vector<int>> &result,
                                      vector<bool> &vizited) {
    // level = depth of each node
    // low = lowest level reachable from each node
    vizited[node] = true;
    for(int i=0;i<connections[node].size();i++) {
        if(!vizited[connections[node][i]]) {
            level[connections[node][i]] = level[node] + 1;
            low[connections[node][i]] = level[node] + 1;

            DFSforCriticalConnections(connections[node][i], level, low, result, vizited);

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
    vector<bool> vizited(n+1,false);

    DFSforCriticalConnections(0, level, low, result, vizited);

    return result;
}

pair<int,int> Graph::MaxDistanceToMarkedNode(int startNode, vector<bool> &markedNodes) {
    queue<int> nodeQueue;
    vector<int> depth(n+1,0);
    // first value is the marked node furthest from start node, second the depth
    pair<int,int> maxDepthMarkedNode(0,0);
    vector<bool> vizited (n+1, false);

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

int Graph::shortestCostInWeightedGraph(pair<int,int> startNode, pair<int,int> destinationNode) {
    deque <pair<int,int>> nodeQueue;
    // depth but acts more like a cost matrix
    vector<vector<int>> depth(connections.size(), vector<int>(connections[0].size(),INT_MAX));
    depth[startNode.first][startNode.second] = 0;
    nodeQueue.push_back(startNode);

    while(!nodeQueue.empty()) {
        pair<int,int> current = nodeQueue.front();
        nodeQueue.pop_front();
        Neighbours d(current, connections,1,false);

        for (auto it:directions) {
            pair<int,int> temp = d.getIndices(it);
            int newRow = temp.first, newCol = temp.second;

            // if depth of new node is higher than current node and
                // cells are different, then give new node depth = current node depth + 1 and push it back
                // else give it the same depth and push it front
            // we do this so we can prioritize the path that doesnt cost anything
            if(d.getValue(it) != -1 && depth[newRow][newCol] > depth[current.first][current.second])
            {
                if(connections[newRow][newCol] != connections[current.first][current.second]) {
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

double Graph::MstForCoordinates(vector<pair<int, int>> &coordinates) {
    double totalCost = 0.0;
    vector<bool> vizited(n+1, false);
    vizited[0] = true;

    vector<double> cost(n+1, 50000.00);
    cost[0] = 0.0;
    for (int i=1;i<n;i++) {
        cost[i] = distance(coordinates[i], coordinates[0]);
    }

    for (int i=1;i<n;i++) {
        double minimumDistance = 50000.00;
        int nextIndex = -1;

        for (int j=0;j<n;j++)
            if (vizited[j] == false)
                if (cost[j] < minimumDistance) {
                    minimumDistance = cost[j];
                    nextIndex = j;
                }

        // set next node as vizited and update totalCost
        vizited[nextIndex] = true;
        totalCost += minimumDistance;

        for (int j=0;j<n;j++)
            if (vizited[j] == false) {
                double newDistance = distance(coordinates[nextIndex],coordinates[j]);
                if (cost[j] > newDistance) cost[j] = newDistance;
            }
    }

    return totalCost;
}

vector<int> Graph::BfsZeroOne(int source) {
    deque<int> nodeQueue;
    vector<int> depth(n+1,INT_MAX);
    depth[source] = 0;
    nodeQueue.push_back(source);

    while(!nodeQueue.empty()) {
        int currentNode = nodeQueue.front();
        nodeQueue.pop_front();

        for(auto neighbour:connectionsWithCost[currentNode]) {
            if (depth[neighbour.node] - neighbour.cost > depth[currentNode]) {
                depth[neighbour.node] = depth[currentNode] + neighbour.cost;

                if (neighbour.cost == 0)
                    nodeQueue.push_front(neighbour.node);
                else
                    nodeQueue.push_back(neighbour.node);
            }
        }
    }

    return depth;
}

int Graph::shortestPathWithMaxStops(int source, int destination, int maxStops) {
    vector<int> distance(n, INT_MAX);
    distance[source] = 0;

    // first int = number of stops for that node
    queue<pair<int, Edge>> nodeQueue;
    nodeQueue.emplace(0, Edge {.node = source, .cost = 0});

    int currentNode = source, cost, numberOfStops;
    while(!nodeQueue.empty()) {
        numberOfStops = nodeQueue.front().first;
        if (numberOfStops > maxStops) break;

        currentNode = nodeQueue.front().second.node;
        cost = nodeQueue.front().second.cost;
        nodeQueue.pop();

        for(auto it:connectionsWithCost[currentNode]) {
            if (distance[it.node] > cost + it.cost) {
                distance[it.node] = cost + it.cost;
                nodeQueue.emplace(numberOfStops + 1, Edge {.node = it.node, .cost = distance[it.node]});
            }
        }
    }

    if (distance[destination] != INT_MAX) return distance[destination];

    return -1;
}

// TODO: useless so far
const vector<vector<int>>* Graph::floydWarshall() const {
    vector<vector<int>>* costs = new vector<vector<int>>(n+1, vector<int>(n+1, INT_MAX));
    // TODO: initialize for each edge

    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                if ((*costs)[i][j] > (*costs)[i][k] + (*costs)[k][j])
                    (*costs)[i][j] = (*costs)[i][k] + (*costs)[k][j];

    return costs;
}

const vector<long long int> * Graph::dijkstraFromSource(int source) const {
    vector<bool> visited(n+1, false);
    vector<long long>* costs = new vector<long long>(n+1, LONG_LONG_MAX);
    (*costs)[source] = 0;

    priority_queue<Edge> priorityQueue;
    priorityQueue.push((Edge {.node = source, .cost = 0}));

    while (!priorityQueue.empty()) {
        long long currentNode = priorityQueue.top().node;
        long long currentCost = priorityQueue.top().cost;
        priorityQueue.pop();

        if (visited[currentNode] == false) {
            visited[currentNode] = true;

            for(auto neighbour : connectionsWithCost[currentNode]) {
                if ((*costs)[neighbour.node] > (*costs)[currentNode] + neighbour.cost) {
                    (*costs)[neighbour.node] = (*costs)[currentNode] + neighbour.cost;
                    priorityQueue.push(Edge {.node = neighbour.node, .cost = (*costs)[neighbour.node]});
                }
            }
        }
    }

    return costs;
}

// TODO: outside class functions
double distance(pair<int, int> pointA, pair<int, int> pointB) {
    return sqrt(pow(pointB.first - pointA.first,2) + pow(pointB.second - pointA.second,2));
}

class Solution {
private:
    // union & find
    int find(int node);
    void Union(int firstNode, int secondNode);
    // for union find, size for the rank of trees
    vector<int> parent, size;

public:
    // CONSTRUCTOR
    Solution () { }
    Solution(int n) {
        this->parent.resize(n+1);
        this->size.resize(n+1,0);
        for (int i=0;i<parent.size();i++) parent[i] = i;
    }

    // LEETCODE PROBLEMS
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        Graph g(n,dislikes);
        return g.isBipartite();
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        Graph g(graph);
        // reverse the graph
        g.transposeGraph();
        // get the topological sort
        vector<int> sortedVector = g.topologicalSort(false);
        // sort the nodes
        sort(sortedVector.begin(),sortedVector.end());

        return sortedVector;
    }

    bool equationsPossible(vector<string>& equations) {
        this->parent.resize(27);
        this->size.resize(27,0);
        for (int i=0;i<parent.size();i++) parent[i] = i;

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

    int shortestBridge(vector<vector<int>>& grid) {
        Graph g;
        return g.shortestBridge(grid);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        Graph g(numCourses, prerequisites, true);
        return g.topologicalSort();
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        Graph g(n, connections);
        return g.criticalConnections();
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<Edge>> connectionsWithCost(n);
        for (auto it:flights) {
            connectionsWithCost[it[0]].push_back(Edge {.node = it[1], .cost = it[2]});
        }

        Graph g(n,connectionsWithCost);
        return g.shortestPathWithMaxStops(src, dst, k);
    }

    // INFOARENA PROBLEMS
    void padure() {
        ifstream f("padure.in");
        ofstream g("padure.out");

        int n,m,pl,pc,cl,cc;
        f >> n >> m >> pl >> pc >> cl >> cc;
        vector<vector<int>> grid(n+1,vector<int>(m+1,0));
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                f >> grid[i][j];

        Graph ob(grid);
        g << ob.shortestCostInWeightedGraph(make_pair(pl,pc), make_pair(cl,cc));

        f.close();
        g.close();
    }

    void cablaj() {
        ifstream f("cablaj.in");
        ofstream g("cablaj.out");

        int n;
        f >> n;

        vector<pair<int,int>> coordinates;
        coordinates.reserve(n+1);

        for (int i=0;i<n;i++) {
            int x,y;
            f >> x >> y;
            coordinates.emplace_back(x,y);
        }

        Graph ob(n);
        g << fixed << setprecision(4) << ob.MstForCoordinates(coordinates);

        f.close();
        g.close();
    }

    void camionas() {
        ifstream f("camionas.in");
        ofstream g ("camionas.out");

        int n,m,G,x,y,c;
        f >> n >> m >> G;
        vector<vector<Edge>> connections(n+1);

        for (int i=0;i<m;i++) {
            f >> x >> y >> c;
            connections[x].push_back(Edge {.node = y, .cost = c < G});
            connections[y].push_back(Edge {.node = x, .cost = c < G});
        }

        Graph ob(n,m, connections);
        vector<int> costs = ob.BfsZeroOne(1);

        g << costs[n] << endl;

        f.close();
        g.close();
    }

    void rusuoaica() {
        ifstream f("rusuoaica.in");
        ofstream g("rusuoaica.out");

        struct edge {
            int node1, node2, cost;

            bool operator<(const edge& e) {
                return this->cost < e.cost;
            }
        };

        vector<edge> tunels;

        int N,M,A, totalSum = 0, numberOfEdgesAdded = 0;
        f >> N >> M >> A;
        tunels.reserve(M);

        int t1, t2, t3;
        for (int i=0; i<M; i++) {
            f >> t1 >> t2 >> t3;
            tunels.emplace_back(edge {.node1 = t1, .node2 = t2, .cost = t3});
        }

        sort(tunels.begin(), tunels.end());

        this->parent.resize(N + 1);
        this->size.resize(N + 1,0);
        for (int i=0;i<parent.size();i++) parent[i] = i;

        for (auto & tunel : tunels) {
            if (numberOfEdgesAdded >= N-1) break;

            int parent1 = find(tunel.node1);
            int parent2 = find(tunel.node2);

            if (parent1 != parent2 && tunel.cost <= A) {
                totalSum += tunel.cost;
                numberOfEdgesAdded++;
                Union(parent1, parent2);
            }
            else {
                totalSum -= tunel.cost;
            }
        }

        g << totalSum + (N - numberOfEdgesAdded - 1) * A << endl;

        f.close();
        g.close();
    }

    int dragoni1(vector<vector<int>>& connections,const vector<int>& dmax) {
        vector<vector<Edge>> connectionsWithCost(connections.size());

        for (auto it:connections) {
            connectionsWithCost[it[0]].push_back(Edge {.node = it[1], .cost = dmax[1] < it[2]});
            connectionsWithCost[it[1]].push_back(Edge {.node = it[0], .cost = dmax[1] < it[2]});
        }

        // -1 because i create it with +1
        Graph g(connections.size()-1, connectionsWithCost);
        vector<int> costs = g.BfsZeroOne(1);

        int maxCost = 0, maxCostIndex = -1;
        for (int i=1; i<costs.size(); i++)
            if (costs[i] == 0 && maxCost < dmax[i]) {
                maxCost = dmax[i];
                maxCostIndex = i;
            }

        return dmax[maxCostIndex];
    }

    int dragoni2(vector<vector<int>>& connections,const vector<int>& dmax) {
        vector<vector<Edge>> connectionsWithCost(dmax.size());

        for (auto it: connections) {
            connectionsWithCost[it[0]].push_back(Edge{.node = it[1], .cost = it[2]});
            connectionsWithCost[it[1]].push_back(Edge{.node = it[0], .cost = it[2]});
        }

        vector<int> costs(dmax.size(), INT_MAX);
        vector<int> dragons(dmax.size(), 0);
        costs[1] = 0;
        dragons[1] = dmax[1];

        // edge and value of dragon
        priority_queue<pair<Edge, int>> priorityQueue;
        priorityQueue.emplace(Edge{.node = 1, .cost = 0}, dmax[1]);

        while (!priorityQueue.empty()) {
            int currentNode = priorityQueue.top().first.node;
            int currentCost = priorityQueue.top().first.cost;
            int currentDragon = priorityQueue.top().second;
            priorityQueue.pop();

            for (auto neighbour: connectionsWithCost[currentNode])
                if (currentDragon >= neighbour.cost)
                    if (costs[neighbour.node] > currentCost + neighbour.cost) {
                        costs[neighbour.node] = currentCost + neighbour.cost;

                        if (dmax[neighbour.node] > currentDragon) {
                            dragons[neighbour.node] = dmax[neighbour.node];
                            priorityQueue.emplace(Edge{.node = neighbour.node, .cost = costs[neighbour.node]},
                                                   dmax[neighbour.node]);
                        } else {
                            dragons[neighbour.node] = currentDragon;
                            priorityQueue.emplace(Edge{.node = neighbour.node, .cost = costs[neighbour.node]},
                                                   currentDragon);
                        }
                    }
                    else if (dragons[neighbour.node] < currentDragon) {
                        dragons[neighbour.node] = currentDragon;
                        priorityQueue.emplace(Edge {.node = neighbour.node, .cost = currentCost + neighbour.cost},
                                                   currentDragon);
                    }
        }

        return costs[dmax.size()-1];
    }

    void dragoni() {
        ifstream f("dragoni.in");
        ofstream g("dragoni.out");

        int p,n,m,a,b,d;
        f >> p >> n >> m;
        vector<int> dmax(n+1);
        vector<vector<int>> connections;

        for (int i=1; i<=n; i++)
            f >> dmax[i];

        for (int i=0; i<m; i++) {
            f >> a >> b >> d;
            connections.push_back({a, b, d});
        }

        if (p == 1)
            g << dragoni1(connections, dmax) << endl;
        else
            g << dragoni2(connections, dmax) << endl;
    }

    // CODEFORCES PROBLEMS
    void minimumMaximumDistance() {
        int t,n,k;

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

            Graph g(n,connections,0);
            // here we need to call MaxDistanceToMarkedNode on a random marked node
            pair<int,int> firstResult = g.MaxDistanceToMarkedNode(temp, marked);

            // call it again for the node max depth marked node from the first BFS
            pair<int,int> secondResult = g.MaxDistanceToMarkedNode(firstResult.first, marked);

            cout << (max(firstResult.second,secondResult.second) + 1)/2 << endl;
        }
    }

    void graphWithoutLongDirectedPaths() {
        int n,m,i,j;
        cin >> n >> m;
        vector<pair<int,int>> edges(m);

        for (int k=0;k<m;k++)
        {
            cin >> i >> j;
            edges.push_back(make_pair(i,j));
        }

        Graph g(n,m,edges);
        vector<int> teams = g.getBipartition();
        string result = "";

        if(!teams.empty()) result += "YES\n";
        else {
            cout << "NO\n";
            return;
        }

        // a bipartit problem, for each edge the orientation depends in which team the node is
        for(auto it:edges) {
            if (teams[it.first] == 1) result += "1";
            else if(teams[it.first] == 2) result += "0";
        }

        cout << result;
    }

    void JzzhuAndCities() {
        int n,m,k,u,v,s;
        long long x,y, counter = 0;
        cin >> n >> m >> k;

        vector<long long> railway(n + 1, LONG_LONG_MAX);
        vector<vector<Edge>> connectionsWithCost(n+1);
        vector<long long> numberOfTrains(n+1, 0);

        for (int i=0; i<m; i++) {
            cin >> u >> v >> x;
            connectionsWithCost[u].push_back(Edge {.node = v, .cost = x});
            connectionsWithCost[v].push_back(Edge {.node = u, .cost = x});
        }

        for (int i=0; i<k; i++) {
            cin >> s >> y;
            numberOfTrains[s]++;
            railway[s] = min(railway[s], y);
        }

        for (int i=1; i<=n; i++) {
            if (numberOfTrains[i] > 0)
                // one sided because we wont need to go from any node to 1
                connectionsWithCost[1].push_back(Edge {.node = i, .cost = railway[i]});
        }

        Graph g(n, k,connectionsWithCost);
        const vector<long long>* costs = g.dijkstraFromSource(1);

        for (int i=1; i<=n; i++)
            if (numberOfTrains[i] > 0) {
                // start with maximum number of trains to eliminate
                counter += numberOfTrains[i] - 1;

                // if its bigger eliminate last one as well
                if (railway[i] > (*costs)[i])
                    counter++;

                // if its equal check to see if we have more connections to the city
                if (railway[i] == (*costs)[i]) {
                    bool hasConnection = false;

                    for (auto it: connectionsWithCost[i])
                        if ((*costs)[i] == (*costs)[it.node] + it.cost) {
                            hasConnection = true;
                            break;
                        }

                    // if we do we can eliminate the train as well
                    if (hasConnection)
                        counter++;
                }
            }

        cout << counter << endl;

        delete costs;
    }
};

int Solution::find(int node) {
    if (parent[node] == node) return node;

    // find the root node and do compression
    int result = find(parent[node]);
    parent[node] = result;
    return result;
}

void Solution::Union(int firstNode, int secondNode) {
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

int main() {
        // HOMEWORK 01
    // POSSIBLE BIPARTITIONS
    /*vector<vector<int>> d = {{1,2},{3,4},{5,6},
                            {6,7},{8,9},{7,8}};

    vector<vector<int>> d2 = {{1,2},{1,3},{2,4}};
    vector<vector<int>> d3 = {{1,2},{1,3},{2,3}};
    vector<vector<int>> d4 = {{1,2},{3,4},{4,5},{3,5}};
    vector<vector<int>> d5 = {{39,46},{4,41},{3,35},{8,44},{22,44},{7,49},{28,41},{7,25},{6,35},{2,22},{34,35},{3,7},{1,11},{11,48},{8,24},{6,7},{38,40},{37,48},{3,45},{44,45},{4,46},{23,35},{28,46},{7,28},{35,36},{18,20},{8,15},{17,41},{13,35},{6,22},{22,48},{22,39},{4,35},{8,38},{23,41},{10,41},{6,41},{18,48},{16,41},{37,44},{8,12},{18,36},{16,18},{7,44},{3,18},{10,46},{20,37},{2,37},{11,49},{30,45},{28,37},{23,37},{22,23},{5,37},{29,40},{16,35},{22,26},{46,49},{18,26},{8,9},{24,46},{8,28},{11,29},{22,24},{7,15},{4,37},{9,40},{8,32},{23,40},{40,42},{33,40},{17,45},{40,48},{12,41},{43,45},{38,41},{45,47},{12,18},{7,31},{34,37},{8,48},{4,11},{46,48},{2,7},{17,40},{12,46},{22,49},{46,50},{37,50},{22,36},{22,43},{41,44},{13,22},{11,16},{7,47},{14,37},{37,43},{13,37},{26,40},{19,41},{46,47},{16,22},{19,22},{22,33},{11,19},{35,44},{7,33},{41,49},{38,45},{25,35},{3,37},{15,22},{6,18},{11,30},{5,41},{8,33},{1,46},{31,46},{41,42},{18,28},{15,41},{35,49},{25,41},{20,45},{26,46},{8,43},{5,45},{28,40},{1,18},{23,46},{13,18},{35,38},{8,49},{11,44},{18,33},{4,7},{5,7},{10,11},{37,49},{9,22},{4,45},{32,45},{32,37},{29,35},{26,35},{7,29},{1,37},{8,14},{5,11},{18,29},{18,49},{21,41},{17,35},{7,10},{22,38},{40,43},{5,35},{33,35},{6,40},{34,40},{22,34},{16,40},{19,46},{18,39},{24,35},{19,35},{18,50},{8,17},{11,12},{27,35},{8,47},{7,9},{7,36},{8,34},{7,26},{31,41},{29,41},{10,45},{9,35},{33,46},{11,32},{34,45},{42,46},{15,40},{40,50},{30,40},{25,40},{15,37}};

    Solution s;
    cout << s.possibleBipartition(4,d2);*/

    // SHORTEST BRIDGE
    /*vector<vector<int>> t1 = {{0,1},{1,0}};
    vector<vector<int>> t2 = {{0,1,0},{0,0,0},{0,0,1}};
    vector<vector<int>> t3 = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    vector<vector<int>> t4 = {{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};

    Solution s;
    cout << s.shortestBridge(t4);*/

    // COURSE SCHEDULE 2
    /*vector<vector<int>> prerequisites1 = {{1,0}};
    vector<vector<int>> prerequisites2 = {{1,0},{2,0},{3,1},{3,2}};
    vector<vector<int>> prerequisites3 = {};

    Solution s;

    vector<int> result = s.findOrder(2,prerequisites1);
    for(auto i:result) cout<<i<<" ";*/

    // SATISFIABILITY OF EQUALITY EQUATIONS
    /*vector<vector<string>> inputs = {{"a==b","b!=a"},{"b==a","a==b"},{"a==b","b==c","a!=c"},{"c==c","b==d","x!=z"},{"a!=b","b!=c","c!=a"},{"b==b","b==e","e==c","d!=e"},{"a!=a"}};
    vector<bool> solutions = {false,true,false,true,true,true,false};

    for(int i=0;i<solutions.size();i++) {
        Solution s;
        cout<<"TEST "<<i<<": ";
        if(solutions[i] != s.equationsPossible(inputs[i])) cout<<"FAILED\n";
        else cout<<"PASSED\n";
    }*/

    // FIND EVENTUAL SAFE STATES
    /*Solution s;
    vector<vector<int>> graph1 = {{1,2},{2,3},{5},{0},{5},{},{}};
    vector<vector<int>> graph2 = {{1,2,3,4},{1,2},{3,4},{0,4},{}};
    vector<vector<int>> graph3 = {{1},{2},{0,3},{}};
    vector<int> result = s.eventualSafeNodes(graph2);
    cout<<"\n\tRESULT: "<<endl;
    for(auto it:result) cout<<it<<" ";
    cout<<endl;*/

    // CRITICAL CONNECTIONS
    /*vector<vector<int>> connections1 = {{0,1},{1,2},{2,0},{1,3}};
    vector<vector<int>> connections2 = {{0,1}};
    Solution s;
    for(auto it:s.criticalConnections(4,connections1))
        cout<<"("<<it[0]<<", "<<it[1]<<") ";*/

    // GRAPH WITHOUT LONG DIRECTED PATHS
    /*Solution s;
    s.graphWithoutLongDirectedPaths();*/

    // MINIMUM MAXIMUM DISTANCE
    /*Solution s;
    s.minimumMaximumDistance();*/

    // PADURE
    /*Solution s;
    s.padure();*/

        // HOMEWORK 02
    // CABLAJ
    /*Solution s;
    s.cablaj();*/

    // CAMIONAS
    /*Solution s;
    s.camionas();*/

    // CHEAPEST FLIGHTS
    /*Solution s1, s2, s3;
    int n1 = 4, src1 = 0, dst1 = 3, k1 = 1;
    vector<vector<int>> flights1 = {
            {0, 1, 100},
            {1, 2, 100},
            {2, 0, 100},
            {1, 3, 600},
            {2, 3, 200}
    };
    int n2 = 2, src2 = 1, dst2 = 0, k2 = 0;
    vector<vector<int>> flights2 {
            {0, 1, 2}
    };

    int n3 = 4, src3 = 0, dst3 = 3, k3 = 1;
    vector<vector<int>> flights3 = {
            {0, 1, 1},
            {0, 2, 5},
            {1, 2, 1},
            {2, 3, 1}
    };

    cout << s1.findCheapestPrice(n1, flights1, src1, dst1, k1) << endl;
    cout << s2.findCheapestPrice(n2, flights2, src2, dst2, k2) << endl;
    cout << s3.findCheapestPrice(n3, flights3, src3, dst3, k3);*/

    // RUSUOAICA
    /*Solution s;
    s.rusuoaica();*/

    // JZZHU AND CITIES
    /*Solution s;
    s.JzzhuAndCities();*/

    // DRAGONI
    /*Solution s;
    s.dragoni();*/
    return 0;
}
