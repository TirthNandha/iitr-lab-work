#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <chrono>
#include <limits>
#include <functional>
#include <deque>
using namespace std;

const int INF = numeric_limits<int>::max();

// Dijkstra's algorithm
vector<int> dijkstra(const Graph& g, int source) {
    vector<int> dist(g.n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const Edge& e : g.adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    
    return dist;
}

// BFS for unweighted graphs (all weights = 1)
vector<int> bfs_shortest_path(const Graph& g, int source) {
    vector<int> dist(g.n, INF);
    queue<int> q;
    
    dist[source] = 0;
    q.push(source);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& e : g.adj[u]) {
            if (dist[e.to] == INF) {
                dist[e.to] = dist[u] + 1;
                q.push(e.to);
            }
        }
    }
    
    return dist;
}

// 0-1 BFS for graphs with weights 0 or 1
vector<int> zero_one_bfs(const Graph& g, int source) {
    vector<int> dist(g.n, INF);
    deque<int> dq;
    
    dist[source] = 0;
    dq.push_back(source);
    
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        for (const Edge& e : g.adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                if (e.weight == 0) {
                    dq.push_front(e.to);
                } else {
                    dq.push_back(e.to);
                }
            }
        }
    }
    
    return dist;
}

// Weighted BFS for graphs with weights 0 to c
vector<int> weighted_bfs(const Graph& g, int source, int c) {
    vector<int> dist(g.n, INF);
    vector<queue<int>> buckets(c + 1);
    
    dist[source] = 0;
    buckets[0].push(source);
    
    for (int d = 0, waves = 0; waves < g.n; d = (d + 1) % (c + 1)) {
        while (!buckets[d].empty()) {
            int u = buckets[d].front();
            buckets[d].pop();
            
            if (dist[u] < d) continue;
            
            for (const Edge& e : g.adj[u]) {
                if (dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                    buckets[dist[e.to] % (c + 1)].push(e.to);
                }
            }
            waves++;
        }
    }
    
    return dist;
}

// Check if all edge weights are equal
bool check_all_weights_equal(const Graph& g, int weight) {
    for (int u = 0; u < g.n; u++) {
        for (const Edge& e : g.adj[u]) {
            if (e.weight != weight) return false;
        }
    }
    return true;
}

// Check maximum weight in graph
int get_max_weight(const Graph& g) {
    int max_weight = 0;
    for (int u = 0; u < g.n; u++) {
        for (const Edge& e : g.adj[u]) {
            max_weight = max(max_weight, e.weight);
        }
    }
    return max_weight;
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <graph_type> <n> <m_or_sparsity> <weight_type> <seed>" << endl;
        cout << "graph_type: VARM or VARN" << endl;
        cout << "For VARM: n=nodes, m=edges" << endl;
        cout << "For VARN: n=nodes, sparsity=1(2n), 2(nlogn), 3(n√n), 4(n(n-1)/2)" << endl;
        cout << "weight_type: unweighted, 01, wbfs_c (where c is max weight)" << endl;
        return 0;
    }
    
    string graph_type = argv[1];
    int n = atoi(argv[2]);
    int m_or_sparsity = atoi(argv[3]);
    string weight_type = argv[4];
    unsigned seed = atoi(argv[5]);
    
    int m;
    if (graph_type == "VARM") {
        m = m_or_sparsity;
    } else if (graph_type == "VARN") {
        switch (m_or_sparsity) {
            case 1: m = 2 * n; break;
            case 2: m = n * (int)(log(n) / log(2) + 0.5); break;
            case 3: m = n * (int)sqrt(n); break;
            case 4: m = n * (n - 1) / 2; break;
            default: cout << "Invalid sparsity option" << endl; return 0;
        }
    } else {
        cout << "Invalid graph type" << endl;
        return 0;
    }
    
    Graph g(1); // dummy initialization
    
    // Generate graph based on weight type
    if (weight_type == "unweighted") {
        g = Graph::generateRandomGraph(n, m, false, 1, seed);
    } else if (weight_type == "01") {
        g = Graph::generateRandomGraph01(n, m, false, 0.3, seed);
    } else if (weight_type.substr(0, 5) == "wbfs_") {
        int c = atoi(weight_type.substr(5).c_str());
        g = Graph::generateRandomGraph(n, m, false, c, seed);
    } else {
        cout << "Invalid weight type" << endl;
        return 0;
    }
    
    // Run all sources shortest path (averaging over multiple sources)
    int num_sources = min(10, n); // Test with 10 random sources
    
    long long dijkstra_time = 0;
    long long bfs_time = 0;
    
    for (int i = 0; i < num_sources; i++) {
        int source = rand() % n;
        
        // Measure Dijkstra
        auto start_time = chrono::high_resolution_clock::now();
        auto dist_dijkstra = dijkstra(g, source);
        auto end_time = chrono::high_resolution_clock::now();
        dijkstra_time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Measure BFS variant
        start_time = chrono::high_resolution_clock::now();
        if (weight_type == "unweighted") {
            auto dist_bfs = bfs_shortest_path(g, source);
            end_time = chrono::high_resolution_clock::now();
        } else if (weight_type == "01") {
            auto dist_bfs = zero_one_bfs(g, source);
            end_time = chrono::high_resolution_clock::now();
        } else if (weight_type.substr(0, 5) == "wbfs_") {
            int c = atoi(weight_type.substr(5).c_str());
            auto dist_bfs = weighted_bfs(g, source, c);
            end_time = chrono::high_resolution_clock::now();
        }
        bfs_time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    
    // Average the times
    dijkstra_time /= num_sources;
    bfs_time /= num_sources;
    
    // Output results
    cout << "SHORTEST_PATH," << graph_type << "," << n << "," << m << ","
              << weight_type << ",DIJKSTRA," << dijkstra_time << endl;
    cout << "SHORTEST_PATH," << graph_type << "," << n << "," << m << ","
              << weight_type << ",BFS_VARIANT," << bfs_time << endl;
    
    return 0;
}