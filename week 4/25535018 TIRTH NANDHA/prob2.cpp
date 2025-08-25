#include <queue>
#include "graph.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <deque>
#include <functional>
#include <cmath>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

vector<long> dijkstraPath(const Graph& g, unsigned long src) {
    vector<long> distances(g.n, INF);
    priority_queue<pair<long, unsigned long>, vector<pair<long, unsigned long>>, greater<pair<long, unsigned long>>> pqNodes;
    
    distances[src] = 0;
    pqNodes.push({0, src});
    
    while (!pqNodes.empty()) {
        long currDist = pqNodes.top().first;
        unsigned long node = pqNodes.top().second;
        pqNodes.pop();
        
        if (currDist > distances[node]) continue;
        
        for (const Edge& edge : g.adj[node]) {
            long newDist = distances[node] + edge.weight;
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                pqNodes.push({newDist, edge.to});
            }
        }
    }
    
    return distances;
}

vector<long> bfsShortest(const Graph& g, unsigned long src) {
    vector<long> distances(g.n, INF);
    queue<unsigned long> nodesQueue;
    
    distances[src] = 0;
    nodesQueue.push(src);
        
    while (nodesQueue.size() > 0) {
        unsigned long node = nodesQueue.front();
        nodesQueue.pop();
        
        for (size_t i = g.adj[node].size(); i-- > 0;) {
            if (distances[g.adj[node][i].to] == INF) {
                distances[g.adj[node][i].to] = distances[node] + 1;
                nodesQueue.push(g.adj[node][i].to);
            }
        }
    }
    
    return distances;
}

vector<long> zeroOneBfs(const Graph& g, unsigned long src) {
    vector<long> distances(g.n, INF);
    deque<unsigned long> dqNodes;
    
    distances[src] = 0;
    dqNodes.push_back(src);
    
    while (!dqNodes.empty()) {
        unsigned long node = dqNodes.front();
        dqNodes.pop_front();
        
        for (const Edge& edge : g.adj[node]) {
            if (distances[node] + edge.weight < distances[edge.to]) {
                distances[edge.to] = distances[node] + edge.weight;
                if (edge.weight == 0) {
                    dqNodes.push_front(edge.to);
                } else {
                    dqNodes.push_back(edge.to);
                }
            }
        }
    }
    
    return distances;
}

vector<long> weightedBfs(const Graph& g, unsigned long src, int c) {
    vector<long> distances(g.n, INF);
    vector<queue<unsigned long>> buckets(c + 1);
    
    distances[src] = 0;
    buckets[0].push(src);
    
    long d = 0;
    long processed = 0;
    while (processed < (long)g.n) {
        while (!buckets[d].empty()) {
            unsigned long node = buckets[d].front();
            buckets[d].pop();
            if (distances[node] < d) continue;
            for (const Edge& edge : g.adj[node]) {
                if (distances[node] + edge.weight < distances[edge.to]) {
                    distances[edge.to] = distances[node] + edge.weight;
                    buckets[distances[edge.to] % (c + 1)].push(edge.to);
                }
            }
            processed++;
        }
    d = (d + 1) % (c + 1);
}

    
    return distances;
}

bool allWeightsEqual(const Graph& g, long weightVal) {
    for (unsigned long u = 0; u < g.n; ++u) {
        for (size_t i = 0; i < g.adj[u].size(); ++i) {
            if (g.adj[u][i].weight != weightVal) return false;
        }
    }
    return true;
}

long maxWeight(const Graph& g) {
    long maxVal = 0;
    for (unsigned long u = g.n; u-- > 0;) {
        for (const Edge& e : g.adj[u]) {
            maxVal = max(maxVal, (long)e.weight);
        }
    }
    return maxVal;
}

int main(int argc, char* argv[]) {
    if (argc < 6 || argc > 7) {
        cout << "Run: " << argv[0] << " <typeGraph> <numNodes> <edgesOrSparsity> <weightType> <seedValue> [algorithm]" << endl;
        cout << "Types: VARM, VARN" << endl;
        cout << "VARM: nodes, edges" << endl;
        cout << "VARN: sparsity=1(2n),2(nlogn),3(nsqrt(n)),4(max)" << endl;
        cout << "Weights: unweighted, 01, wbfs_c" << endl;
        cout << "Algorithm: dijkstra, bfs" << endl;
        return 0;
    }
    
    string graphType = argv[1];
    unsigned long nodeCount = atoi(argv[2]);
    unsigned long sparsityOrEdges = atoi(argv[3]);
    string weightKind = argv[4];
    unsigned int seedValue = atoi(argv[5]);
    string algoChoice = (argc == 7) ? argv[6] : "all";
    
    unsigned long edgeCount;
    if (graphType == "VARM") {
        edgeCount = sparsityOrEdges;
    } else if (graphType == "VARN") {
        if (sparsityOrEdges == 1) {
            edgeCount = nodeCount * 2;
        } else if (sparsityOrEdges == 2) {
            edgeCount = nodeCount * (unsigned long)(log(nodeCount) + 0.5);
        } else if (sparsityOrEdges == 3) {
            edgeCount = nodeCount * (unsigned long)sqrt(nodeCount);
        } else if (sparsityOrEdges == 4) {
            edgeCount = nodeCount * (nodeCount - 1) / 2;
        } else {
            cout << "Error: bad sparsity" << endl;
            return 0;
        }
    } else {
        cout << "Error: bad graph type" << endl;
        return 0;
    }
    
    Graph graph(1);
    
    if (weightKind == "unweighted") {
        graph = Graph::generateRandomGraph(nodeCount, edgeCount, false, 1, seedValue);
    } else if (weightKind == "01") {
        graph = Graph::generateRandomGraph01(nodeCount, edgeCount, false, 0.3, seedValue);
    } else if (weightKind.substr(0, 5) == "wbfs_") {
        long maxW = atoi(weightKind.substr(5).c_str());
        graph = Graph::generateRandomGraph(nodeCount, edgeCount, false, maxW, seedValue);
    } else {
        cout << "Error: bad weight type" << endl;
        return 0;
    }
    
    long sourceCount = min(10L, (long)nodeCount);
    
    if (algoChoice == "all") {
        long long dijkstraDuration = 0;
        long long bfsDuration = 0;
        
        for (long i = 0; i < sourceCount; ++i) {
            unsigned long src = rand() % nodeCount;
            
            auto start = chrono::high_resolution_clock::now();
            auto distDijkstra = dijkstraPath(graph, src);
            auto end = chrono::high_resolution_clock::now();
            dijkstraDuration += chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            start = chrono::high_resolution_clock::now();
            if (weightKind == "unweighted") {
                auto distBfs = bfsShortest(graph, src);
            } else if (weightKind == "01") {
                auto distBfs = zeroOneBfs(graph, src);
            } else if (weightKind.substr(0, 5) == "wbfs_") {
                long maxW = atoi(weightKind.substr(5).c_str());
                auto distBfs = weightedBfs(graph, src, maxW);
            }
            end = chrono::high_resolution_clock::now();
            bfsDuration += chrono::duration_cast<chrono::microseconds>(end - start).count();
        }
        
        dijkstraDuration /= sourceCount;
        bfsDuration /= sourceCount;
        
        cout << "SHORTEST_PATH," << graphType << "," << nodeCount << "," << edgeCount << ","
             << weightKind << ",DIJKSTRA," << dijkstraDuration << endl;
        cout << "SHORTEST_PATH," << graphType << "," << nodeCount << "," << edgeCount << ","
             << weightKind << ",BFS_VARIANT," << bfsDuration << endl;
    } else {
        long long duration = 0;
        
        for (long i = 0; i < sourceCount; ++i) {
            unsigned long src = rand() % nodeCount;
            auto start = chrono::high_resolution_clock::now();
            
            if (algoChoice == "dijkstra") {
                auto dist = dijkstraPath(graph, src);
            } else if (algoChoice == "bfs") {
                if (weightKind == "unweighted") {
                    auto dist = bfsShortest(graph, src);
                } else if (weightKind == "01") {
                    auto dist = zeroOneBfs(graph, src);
                } else if (weightKind.substr(0, 5) == "wbfs_") {
                    long maxW = atoi(weightKind.substr(5).c_str());
                    auto dist = weightedBfs(graph, src, maxW);
                }
            } else {
                cout << "Error: invalid algorithm " << algoChoice << endl;
                return 1;
            }
            
            auto end = chrono::high_resolution_clock::now();
            duration += chrono::duration_cast<chrono::microseconds>(end - start).count();
        }
        
        duration /= sourceCount;
        
        string algoName = (algoChoice == "dijkstra") ? "DIJKSTRA" : "BFS_VARIANT";
        cout << "SHORTEST_PATH," << graphType << "," << nodeCount << "," << edgeCount << ","
             << weightKind << "," << algoName << "," << duration << endl;
    }
    
    return 0;
}