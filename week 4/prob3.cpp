#include "graph.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

// DFS helper for SCC algorithms
void dfs_scc(const Graph& g, int u, std::vector<bool>& visited, std::vector<int>& component, int comp_id) {
    visited[u] = true;
    component[u] = comp_id;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_scc(g, e.to, visited, component, comp_id);
        }
    }
}

// DFS on reverse graph
void dfs_scc_rev(const Graph& g, int u, std::vector<bool>& visited, std::vector<int>& component, int comp_id) {
    visited[u] = true;
    component[u] = comp_id;
    
    for (const Edge& e : g.adj_rev[u]) {
        if (!visited[e.to]) {
            dfs_scc_rev(g, e.to, visited, component, comp_id);
        }
    }
}

// BFS helper for SCC algorithms
void bfs_scc(const Graph& g, int start, std::vector<bool>& visited, std::vector<int>& component, int comp_id) {
    std::queue<int> q;
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
void bfs_scc_rev(const Graph& g, int start, std::vector<bool>& visited, std::vector<int>& component, int comp_id) {
    std::queue<int> q;
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
std::vector<int> scc_algo1(const Graph& g) {
    std::vector<int> component(g.n, -1);
    int comp_id = 0;
    
    for (int i = 0; i < g.n; i++) {
        if (component[i] == -1) {
            // DFS from i in G
            std::vector<bool> visited_g(g.n, false);
            dfs_scc(g, i, visited_g, component, comp_id);
            
            // DFS from i in G_R
            std::vector<bool> visited_gr(g.n, false);
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
std::vector<int> scc_algo2(const Graph& g) {
    std::vector<int> component(g.n, -1);
    int comp_id = 0;
    
    for (int i = 0; i < g.n; i++) {
        if (component[i] == -1) {
            // BFS from i in G
            std::vector<bool> visited_g(g.n, false);
            bfs_scc(g, i, visited_g, component, comp_id);
            
            // BFS from i in G_R
            std::vector<bool> visited_gr(g.n, false);
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
void dfs_finish_time(const Graph& g, int u, std::vector<bool>& visited, 
                     std::vector<int>& finish_time, int& time_counter) {
    visited[u] = true;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_finish_time(g, e.to, visited, finish_time, time_counter);
        }
    }
    
    finish_time[u] = time_counter++;
}

// Algorithm 3: Kosaraju's algorithm
std::vector<int> scc_algo3(const Graph& g) {
    std::vector<int> component(g.n, -1);
    std::vector<bool> visited(g.n, false);
    std::vector<int> finish_time(g.n);
    int time_counter = 0;
    
    // First DFS on G to get finish times
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_finish_time(g, i, visited, finish_time, time_counter);
        }
    }
    
    // Create vertices sorted by reverse finish time
    std::vector<std::pair<int, int>> finish_order;
    for (int i = 0; i < g.n; i++) {
        finish_order.push_back({finish_time[i], i});
    }
    std::sort(finish_order.rbegin(), finish_order.rend());
    
    // Second DFS on G_R in reverse finish time order
    std::fill(visited.begin(), visited.end(), false);
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
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <graph_type> <n> <m_or_sparsity> <seed>" << std::endl;
        std::cerr << "graph_type: VARM or VARN" << std::endl;
        std::cerr << "For VARM: n=nodes, m=edges" << std::endl;
        std::cerr << "For VARN: n=nodes, sparsity=1(2n), 2(nlogn), 3(n√n), 4(n(n-1)/2)" << std::endl;
        return 1;
    }
    
    std::string graph_type = argv[1];
    int n = atoi(argv[2]);
    int m_or_sparsity = atoi(argv[3]);
    unsigned seed = atoi(argv[4]);
    
    int m;
    if (graph_type == "VARM") {
        m = m_or_sparsity;
    } else if (graph_type == "VARN") {
        switch (m_or_sparsity) {
            case 1: m = 2 * n; break;
            case 2: m = n * (int)(log(n) / log(2) + 0.5); break;
            case 3: m = n * (int)sqrt(n); break;
            case 4: m = n * (n - 1) / 2; break;
            default: std::cerr << "Invalid sparsity option" << std::endl; return 1;
        }
    } else {
        std::cerr << "Invalid graph type" << std::endl;
        return 1;
    }
    
    // Generate directed graph
    Graph g = Graph::generateRandomGraph(n, m, true, 1, seed);
    
    // Measure Algorithm 1
    auto start_time = std::chrono::high_resolution_clock::now();
    auto comp1 = scc_algo1(g);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto algo1_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Measure Algorithm 2
    start_time = std::chrono::high_resolution_clock::now();
    auto comp2 = scc_algo2(g);
    end_time = std::chrono::high_resolution_clock::now();
    auto algo2_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Measure Algorithm 3
    start_time = std::chrono::high_resolution_clock::now();
    auto comp3 = scc_algo3(g);
    end_time = std::chrono::high_resolution_clock::now();
    auto algo3_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Output results
    std::cout << "SCC," << graph_type << "," << n << "," << m << ","
              << "ALGO1_DFS," << algo1_time << std::endl;
    std::cout << "SCC," << graph_type << "," << n << "," << m << ","
              << "ALGO2_BFS," << algo2_time << std::endl;
    std::cout << "SCC," << graph_type << "," << n << "," << m << ","
              << "ALGO3_KOSARAJU," << algo3_time << std::endl;
    
    return 0;
}