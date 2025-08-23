#include "graph.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <chrono>
#include <cstring>

// Iterative BFS
void bfs_iterative(const Graph& g, int start, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& e : g.adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
}

// Iterative DFS using stack
void dfs_iterative(const Graph& g, int start, std::vector<bool>& visited) {
    std::stack<int> s;
    s.push(start);
    
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        
        if (!visited[u]) {
            visited[u] = true;
            
            for (const Edge& e : g.adj[u]) {
                if (!visited[e.to]) {
                    s.push(e.to);
                }
            }
        }
    }
}

// Recursive DFS
void dfs_recursive_helper(const Graph& g, int u, std::vector<bool>& visited) {
    visited[u] = true;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_recursive_helper(g, e.to, visited);
        }
    }
}

void dfs_recursive(const Graph& g, int start, std::vector<bool>& visited) {
    dfs_recursive_helper(g, start, visited);
}

// Full graph traversal (visit all components)
void full_traversal_bfs(const Graph& g) {
    std::vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            bfs_iterative(g, i, visited);
        }
    }
}

void full_traversal_dfs_iterative(const Graph& g) {
    std::vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_iterative(g, i, visited);
        }
    }
}

void full_traversal_dfs_recursive(const Graph& g) {
    std::vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_recursive(g, i, visited);
        }
    }
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
    
    // Generate graph
    Graph g = Graph::generateRandomGraph(n, m, false, 1, seed);
    
    // Measure BFS
    auto start_time = std::chrono::high_resolution_clock::now();
    full_traversal_bfs(g);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto bfs_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Measure DFS Iterative
    start_time = std::chrono::high_resolution_clock::now();
    full_traversal_dfs_iterative(g);
    end_time = std::chrono::high_resolution_clock::now();
    auto dfs_iter_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Measure DFS Recursive
    start_time = std::chrono::high_resolution_clock::now();
    full_traversal_dfs_recursive(g);
    end_time = std::chrono::high_resolution_clock::now();
    auto dfs_rec_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    // Output results
    std::cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
              << "BFS," << bfs_time << std::endl;
    std::cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
              << "DFS_ITER," << dfs_iter_time << std::endl;
    std::cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
              << "DFS_REC," << dfs_rec_time << std::endl;
    
    return 0;
}