#include "graph.h"
#include <queue>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
using namespace std;

// DFS helper for SCC algorithms
void dfs_scc(const Graph& g, int u, vector<bool>& visited, vector<int>& component, int comp_id) {
    visited[u] = true;
    component[u] = comp_id;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_scc(g, e.to, visited, component, comp_id);
        }
    }
}

// DFS on reverse graph
void dfs_scc_rev(const Graph& g, int u, vector<bool>& visited, vector<int>& component, int comp_id) {
    visited[u] = true;
    component[u] = comp_id;
    
    for (const Edge& e : g.adj_rev[u]) {
        if (!visited[e.to]) {
            dfs_scc_rev(g, e.to, visited, component, comp_id);
        }
    }
}

// BFS helper for SCC algorithms
void bfs_scc(const Graph& g, int start, vector<bool>& visited, vector<int>& component, int comp_id) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    component[start] = comp_id;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& e : g.adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                component[e.to] = comp_id;
                q.push(e.to);
            }
        }
    }
}

// BFS on reverse graph
void bfs_scc_rev(const Graph& g, int start, vector<bool>& visited, vector<int>& component, int comp_id) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    component[start] = comp_id;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& e : g.adj_rev[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                component[e.to] = comp_id;
                q.push(e.to);
            }
        }
    }
}

// Algorithm 1: DFS on G and G_R, mark common visited vertices
vector<int> algo1(const Graph& g) {
    vector<int> component(g.n, -1);
    int comp_id = 0;
    
    for (int i = 0; i < g.n; i++) {
        if (component[i] == -1) {
            // DFS from i in G
            vector<bool> visited_g(g.n, false);
            dfs_scc(g, i, visited_g, component, comp_id);
            
            // DFS from i in G_R
            vector<bool> visited_gr(g.n, false);
            dfs_scc_rev(g, i, visited_gr, component, comp_id);
            
            // Mark only common visited vertices
            for (int j = 0; j < g.n; j++) {
                if (visited_g[j] && visited_gr[j] && component[j] == comp_id) {
                    // Already marked
                } else if (component[j] == comp_id) {
                    component[j] = -1; // Unmark if not in both
                }
            }
            
            comp_id++;
        }
    }
    
    return component;
}

// Algorithm 2: BFS version of Algorithm 1
vector<int> algo2(const Graph& g) {
    vector<int> component(g.n, -1);
    int comp_id = 0;
    
    for (int i = 0; i < g.n; i++) {
        if (component[i] == -1) {
            // BFS from i in G
            vector<bool> visited_g(g.n, false);
            bfs_scc(g, i, visited_g, component, comp_id);
            
            // BFS from i in G_R
            vector<bool> visited_gr(g.n, false);
            bfs_scc_rev(g, i, visited_gr, component, comp_id);
            
            // Mark only common visited vertices
            for (int j = 0; j < g.n; j++) {
                if (visited_g[j] && visited_gr[j] && component[j] == comp_id) {
                    // Already marked
                } else if (component[j] == comp_id) {
                    component[j] = -1; // Unmark if not in both
                }
            }
            
            comp_id++;
        }
    }
    
    return component;
}

// DFS with finish time recording
void dfs_finish_time(const Graph& g, int u, vector<bool>& visited, 
                     vector<int>& finish_time, int& time_counter) {
    visited[u] = true;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_finish_time(g, e.to, visited, finish_time, time_counter);
        }
    }
    
    finish_time[u] = time_counter++;
}

// Algorithm 3: Kosaraju's algorithm
vector<int> algo3(const Graph& g) {
    vector<int> component(g.n, -1);
    vector<bool> visited(g.n, false);
    vector<int> finish_time(g.n);
    int time_counter = 0;
    
    // First DFS on G to get finish times
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_finish_time(g, i, visited, finish_time, time_counter);
        }
    }
    
    // Create vertices sorted by reverse finish time
    vector<pair<int, int>> finish_order;
    for (int i = 0; i < g.n; i++) {
        finish_order.push_back({finish_time[i], i});
    }
    sort(finish_order.rbegin(), finish_order.rend());
    
    // Second DFS on G_R in reverse finish time order
    fill(visited.begin(), visited.end(), false);
    int comp_id = 0;
    
    for (auto& p : finish_order) {
        int u = p.second;
        if (!visited[u]) {
            dfs_scc_rev(g, u, visited, component, comp_id);
            comp_id++;
        }
    }
    
    return component;
}

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        cout << "Usage: " << argv[0] << " <graph_type> <n> <m_or_sparsity> <seed> [algorithm]" << endl;
        cout << "graph_type: VARM or VARN" << endl;
        cout << "For VARM: n=nodes, m=edges" << endl;
        cout << "For VARN: n=nodes, sparsity=1(2n), 2(nlogn), 3(n√n), 4(n(n-1)/2)" << endl;
        cout << "algorithm (optional): algo1, algo2, algo3" << endl;
        return 0;
    }
    
    string graph_type = argv[1];
    int n = atoi(argv[2]);
    int m_or_sparsity = atoi(argv[3]);
    unsigned seed = atoi(argv[4]);
    string algorithm = (argc == 6) ? argv[5] : "all";
    
    int m;
    if (graph_type == "VARM") {
        m = m_or_sparsity;
    } else if (graph_type == "VARN") {
        switch (m_or_sparsity) {
            case 1: m = 2 * n; break;
            case 2: m = n * (int)(log(n) + 0.5); break;
            case 3: m = n * (int)sqrt(n); break;
            case 4: m = n * (n - 1) / 2; break;
            default: cout << "Invalid sparsity option" << endl; return 0;
        }
    } else {
        cout << "Invalid graph type" << endl;
        return 0;
    }
    
    // Generate directed graph
    Graph g = Graph::generateRandomGraph(n, m, true, 1, seed);
    
    if (algorithm == "all") {
        // Measure Algorithm 1
        auto start_time = chrono::high_resolution_clock::now();
        auto comp1 = algo1(g);
        auto end_time = chrono::high_resolution_clock::now();
        auto algo1_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Measure Algorithm 2
        start_time = chrono::high_resolution_clock::now();
        auto comp2 = algo2(g);
        end_time = chrono::high_resolution_clock::now();
        auto algo2_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Measure Algorithm 3
        start_time = chrono::high_resolution_clock::now();
        auto comp3 = algo3(g);
        end_time = chrono::high_resolution_clock::now();
        auto algo3_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Output results
        cout << "SCC," << graph_type << "," << n << "," << m << "," << "ALGO1," << algo1_time << endl;
        cout << "SCC," << graph_type << "," << n << "," << m << "," << "ALGO2," << algo2_time << endl;
        cout << "SCC," << graph_type << "," << n << "," << m << "," << "ALGO3," << algo3_time << endl;
    } else {
        // Run only specified algorithm
        auto start_time = chrono::high_resolution_clock::now();
        
        if (algorithm == "algo1") {
            auto comp = algo1(g);
        } else if (algorithm == "algo2") {
            auto comp = algo2(g);
        } else if (algorithm == "algo3") {
            auto comp = algo3(g);
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            return 1;
        }
        
        auto end_time = chrono::high_resolution_clock::now();
        auto exec_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        string alg_name;
        if (algorithm == "algo1") alg_name = "ALGO1";
        else if (algorithm == "algo2") alg_name = "ALGO2";
        else if (algorithm == "algo3") alg_name = "ALGO3";
        
        cout << "SCC," << graph_type << "," << n << "," << m << "," << alg_name << "," << exec_time << endl;
    }
    
    return 0;
}