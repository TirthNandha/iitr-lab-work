#include <queue>
#include "graph.h"
#include <stack>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstring>
#include <vector>
using namespace std;

void bfs_itr(const Graph& g, int start, vector<bool>& visited) {
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

void dfs_itr(const Graph& g, int start, vector<bool>& visited) {
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

void dfs_rec_helper(const Graph& g, int u, vector<bool>& visited) {
    visited[u] = true;
    
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            dfs_rec_helper(g, e.to, visited);
        }
    }
}

void dfs_rec(const Graph& g, int start, vector<bool>& visited) {
    dfs_rec_helper(g, start, visited);
}

void full_bfs_traversal(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            bfs_itr(g, i, visited);
        }
    }
}

void full_dfs_itr_traversal(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_itr(g, i, visited);
        }
    }
}

void full_dfs_rec_traversal(const Graph& g) {
    vector<bool> visited(g.n, false);
    for (int i = 0; i < g.n; i++) {
        if (!visited[i]) {
            dfs_rec(g, i, visited);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        cout << "Heres how to use: " << argv[0] << " <graph_type> <n> <sparsity_or_m> <seed> [algorithm]" << endl;
        cout << "graph_type: VARM or VARN" << endl;
        cout << "For VARM: n is nodes, m is edges" << endl;
        cout << "For VARN: n is nodes, sparsity=1(2n), 2(nlogn), 3(n√n), 4(n(n-1)/2)" << endl;
        cout << "algorithm (optional): bfs, dfs_iter, dfs_rec" << endl;
        return 0;
    }
    
    int n = atoi(argv[2]);
    int sparsity_or_m = atoi(argv[3]);
    unsigned seed = atoi(argv[4]);
    string algorithm = (argc == 6) ? argv[5] : "all";
    string graph_type = argv[1];
    
    int m;
    if (graph_type == "VARM") {
        m = sparsity_or_m;
    } else if (graph_type == "VARN") {
        switch (sparsity_or_m) {
            case 1: m = 2 * n; break;
            case 2: m = n * (int)(log(n) + 0.5); break;
            case 3: m = n * (int)sqrt(n); break;
            case 4: m = n * (n - 1) / 2; break;
            default: cout << "Error in sparsity option" << endl; return 0;
        }
    } else {
        cout << "Error in graph type" << endl;
        return 0;
    }
    
    Graph g = Graph::generateRandomGraph(n, m, false, 1, seed);
    
    if (algorithm == "all") {
        auto start_time = chrono::high_resolution_clock::now();
        full_bfs_traversal(g);
        auto end_time = chrono::high_resolution_clock::now();
        auto bfs_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        start_time = chrono::high_resolution_clock::now();
        full_dfs_itr_traversal(g);
        end_time = chrono::high_resolution_clock::now();
        auto dfs_iter_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        start_time = chrono::high_resolution_clock::now();
        full_dfs_rec_traversal(g);
        end_time = chrono::high_resolution_clock::now();
        auto dfs_rec_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "BFS," << bfs_time << endl;
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "DFS_ITER," << dfs_iter_time << endl;
        cout << "GRAPH_TRAVERSAL," << graph_type << "," << n << "," << m << ","
                  << "DFS_REC," << dfs_rec_time << endl;
    } else {
        auto start_time = chrono::high_resolution_clock::now();
        
        if (algorithm == "bfs") {
            full_bfs_traversal(g);
        } else if (algorithm == "dfs_iter") {
            full_dfs_itr_traversal(g);
        } else if (algorithm == "dfs_rec") {
            full_dfs_rec_traversal(g);
        } else {
            cout << "Error in algorithm: " << algorithm << endl;
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