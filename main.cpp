#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

// Part 1 (Connect the cities)
/* Read an input file of a graph represented in a adjacency
matrix with the weights (distance in km)

Find the optimal way to wire all the cities using the less
optical fiber 

Create a MST 
*/

// Part 1: MST using Prim's Algorithm
vector<pair<pair<int, int>, int>> primMST(vector<vector<int>>& graph, int n) {
    vector<bool> inMST(n, false);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<pair<pair<int, int>, int>> mstEdges;
    
    key[0] = 0;
    
    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        int minKey = INT_MAX;
        
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        
        inMST[u] = true;
        
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    for (int i = 1; i < n; i++) {
        mstEdges.push_back({{parent[i], i}, graph[parent[i]][i]});
    }
    
    return mstEdges;
}

/* Part 2 (Traveling Salesman Problem) 
Find the shortest possible route that visits each neighborhood 
exactly once and returns to the neighborhood of origin.

Display the route with cities labeled as A, B, C, etc.
The first city will be called A, the second B, and so on.

This is a classic TSP (Traveling Salesman Problem).
*/

// Part 2: TSP - Try all permutations for small graphs
pair<vector<int>, int> solveTSP(vector<vector<int>>& graph, int n) {
    vector<int> bestPath;
    int minDist = INT_MAX;
    
    // Generate all permutations starting from 0
    vector<int> cities;
    for (int i = 1; i < n; i++) {
        cities.push_back(i);
    }
    
    do {
        int currentDist = 0;
        int current = 0;
        vector<int> currentPath = {0};
        
        // Calculate total distance for this permutation
        for (int city : cities) {
            if (graph[current][city] == 0) {
                currentDist = INT_MAX;
                break;
            }
            currentDist += graph[current][city];
            currentPath.push_back(city);
            current = city;
        }
        
        // Add return to start
        if (currentDist != INT_MAX && graph[current][0] > 0) {
            currentDist += graph[current][0];
            
            if (currentDist < minDist) {
                minDist = currentDist;
                bestPath = currentPath;
            }
        }
        
    } while (next_permutation(cities.begin(), cities.end()));
    
    bestPath.push_back(0);
    return {bestPath, minDist};
}

/* Part 3 (Maximum Flow Problem)
Read another square matrix of N x N data representing the maximum 
capacity of data transmission between neighborhood i and neighborhood j.

The cities have electromagnetic fields that can generate interference,
which is already reflected in this capacity matrix.

Find the maximum information flow from the initial node to the final node.
Display this maximum flow in the standard output.

This is a classic Maximum Flow problem.
*/

// Part 3: Maximum Flow using Ford-Fulkerson with BFS (Edmonds-Karp)
bool bfs(vector<vector<int>>& residualGraph, int s, int t, vector<int>& parent, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < n; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) return true;
            }
        }
    }
    
    return false;
}

int maxFlow(vector<vector<int>>& capacity, int s, int t, int n) {
    vector<vector<int>> residualGraph = capacity;
    vector<int> parent(n);
    int maxFlowValue = 0;
    
    while (bfs(residualGraph, s, t, parent, n)) {
        int pathFlow = INT_MAX;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        
        maxFlowValue += pathFlow;
    }
    
    return maxFlowValue;
}

/* Part 4 (Closest Exchange/Central)
Given the geographic location of several "exchanges" (centrals) to which 
new homes can be connected, determine which exchange is geographically 
closest to a new service contract.

Note: There is not necessarily one exchange for each neighborhood.
- Some neighborhoods may have no central
- Some neighborhoods may have more than one central

Find the closest exchange for any new contract location.
*/

// Part 4: Voronoi diagram - find closest point
double distance(pair<double, double> p1, pair<double, double> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

vector<vector<pair<double, double>>> voronoiRegions(vector<pair<double, double>>& centrals) {
    vector<vector<pair<double, double>>> regions;
    
    // Find bounding box
    double minX = centrals[0].first, maxX = centrals[0].first;
    double minY = centrals[0].second, maxY = centrals[0].second;
    
    for (auto& p : centrals) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
        minY = min(minY, p.second);
        maxY = max(maxY, p.second);
    }
    
    // Expand bounding box
    double margin = 100;
    minX -= margin;
    maxX += margin;
    minY -= margin;
    maxY += margin;
    
    // For each central, create a polygon approximation
    for (size_t i = 0; i < centrals.size(); i++) {
        vector<pair<double, double>> polygon;
        
        // Sample points around the region
        int samples = 36;
        for (int angle = 0; angle < 360; angle += 360 / samples) {
            double rad = angle * M_PI / 180.0;
            double maxDist = 1000;
            
            // Find the edge of this region in this direction
            for (double dist = 0; dist < maxDist; dist += 10) {
                double x = centrals[i].first + dist * cos(rad);
                double y = centrals[i].second + dist * sin(rad);
                pair<double, double> testPoint = {x, y};
                
                // Check if this point is still closest to central i
                bool stillClosest = true;
                double distToCentral = distance(testPoint, centrals[i]);
                
                for (size_t j = 0; j < centrals.size(); j++) {
                    if (i != j && distance(testPoint, centrals[j]) < distToCentral) {
                        stillClosest = false;
                        break;
                    }
                }
                
                if (!stillClosest) {
                    polygon.push_back({x, y});
                    break;
                }
            }
        }
        
        regions.push_back(polygon);
    }
    
    return regions;
}

int main() {
    ifstream file("inputs/input1.txt");

    if (!file.is_open()){
        cout << "Error opening file" << endl;
        return 1;
    }

    int n;
    file >> n;
    
    // Read distance matrix
    vector<vector<int>> distanceMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> distanceMatrix[i][j];
        }
    }
    
    // Read capacity matrix
    vector<vector<int>> capacityMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> capacityMatrix[i][j];
        }
    }
    
    // Read coordinates
    vector<pair<double, double>> coordinates(n);
    for (int i = 0; i < n; i++) {
        char paren, comma;
        file >> paren >> coordinates[i].first >> comma >> coordinates[i].second >> paren;
    }
    
    file.close();
    
    // Part 1: MST
    cout << "1. Optimal wiring (MST):" << endl;
    vector<pair<pair<int, int>, int>> mst = primMST(distanceMatrix, n);
    for (auto& edge : mst) {
        char from = 'A' + edge.first.first;
        char to = 'A' + edge.first.second;
        cout << "(" << from << "," << to << ") ";
    }
    cout << endl << endl;
    
    // Part 2: TSP
    cout << "2. Shortest route (TSP):" << endl;
    auto [path, totalDist] = solveTSP(distanceMatrix, n);
    for (size_t i = 0; i < path.size(); i++) {
        char city = 'A' + path[i];
        cout << city;
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl << endl;
    
    // Part 3: Maximum Flow
    cout << "3. Maximum flow from source to sink:" << endl;
    int maxFlowValue = maxFlow(capacityMatrix, 0, n - 1, n);
    cout << maxFlowValue << endl << endl;
    
    // Part 4: Voronoi regions
    cout << "4. Voronoi regions (approximated polygons):" << endl;
    vector<vector<pair<double, double>>> regions = voronoiRegions(coordinates);
    for (size_t i = 0; i < regions.size(); i++) {
        cout << "Region " << (char)('A' + i) << ": ";
        for (size_t j = 0; j < regions[i].size(); j++) {
            cout << "(" << fixed << setprecision(2) << regions[i][j].first 
                 << "," << regions[i][j].second << ")";
            if (j < regions[i].size() - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}

