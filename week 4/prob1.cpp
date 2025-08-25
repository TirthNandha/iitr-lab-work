#include "graph.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <chrono>
#include <cstring>
#include <cmath>
using namespace std;

// Iterative BFS
void bfs_iterative(const Graph& g, int start, vector<bool>& visited) {
    queue<int> q;
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
void dfs_iterative(const Graph& g, int start, vector<bool>& visited) {
    stack<int> s;
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
void dfs_recursive_helper(const Graph& g, int u, vector<bool>& visited) {
    visited[u] = true;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_recursive_helper(g, e.to, visited);
        }
    }
}

void dfs_recursive(const Graph& g, int start, vector<bool>& visited) {
    dfs_recursive_helper(g, start, visited);
}

// Full graph traversal (visit all components)
void full_traversal_bfs(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            bfs_iterative(g, i, visited);
        }
    }
}

void full_traversal_dfs_iterative(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_iterative(g, i, visited);
        }
    }
}

void full_traversal_dfs_recursive(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_recursive(g, i, visited);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        cout << "Usage: " << argv[0] << " <graph_type> <n> <m_or_sparsity> <seed> [algorithm]" << endl;
        cout << "graph_type: VARM or VARN" << endl;
        cout << "For VARM: n=nodes, m=edges" << endl;
        cout << "For VARN: n=nodes, sparsity=1(2n), 2(nlogn), 3(n√n), 4(n(n-1)/2)" << endl;
        cout << "algorithm (optional): bfs, dfs_iter, dfs_rec" << endl;
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
    
    // Generate graph
    Graph g = Graph::generateRandomGraph(n, m, false, 1, seed);
    
    if (algorithm == "all") {
        // Measure BFS
        auto start_time = chrono::high_resolution_clock::now();
        full_traversal_bfs(g);
        auto end_time = chrono::high_resolution_clock::now();
        auto bfs_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Measure DFS Iterative
        start_time = chrono::high_resolution_clock::now();
        full_traversal_dfs_iterative(g);
        end_time = chrono::high_resolution_clock::now();
        auto dfs_iter_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Measure DFS Recursive
        start_time = chrono::high_resolution_clock::now();
        full_traversal_dfs_recursive(g);
        end_time = chrono::high_resolution_clock::now();
        auto dfs_rec_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        // Output results
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "BFS," << bfs_time << endl;
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "DFS_ITER," << dfs_iter_time << endl;
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "DFS_REC," << dfs_rec_time << endl;
    } else {
        // Run only specified algorithm
        auto start_time = chrono::high_resolution_clock::now();
        
        if (algorithm == "bfs") {
            full_traversal_bfs(g);
        } else if (algorithm == "dfs_iter") {
            full_traversal_dfs_iterative(g);
        } else if (algorithm == "dfs_rec") {
            full_traversal_dfs_recursive(g);
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            return 1;
        }
        
        auto end_time = chrono::high_resolution_clock::now();
        auto exec_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        string alg_name;
        if (algorithm == "bfs") alg_name = "BFS";
        else if (algorithm == "dfs_iter") alg_name = "DFS_ITER";
        else if (algorithm == "dfs_rec") alg_name = "DFS_REC";
        
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << alg_name << "," << exec_time << endl;
    }
    
    return 0;
}