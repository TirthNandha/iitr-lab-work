#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <random>
#include <set>

struct Edge {
    int to;
    int weight;
    Edge(int t, int w = 1) : to(t), weight(w) {}
};

class Graph {
public:
    int n; // number of nodes
    int m; // number of edges
    std::vector<std::vector<Edge>> adj; // adjacency list
    std::vector<std::vector<Edge>> adj_rev; // reverse adjacency list for directed graphs
    bool directed;
    
    Graph(int nodes, bool dir = false) : n(nodes), m(0), directed(dir) {
        adj.resize(n);
        if (directed) {
            adj_rev.resize(n);
        }
    }
    
    void addEdge(int u, int v, int weight = 1) {
        adj[u].push_back(Edge(v, weight));
        if (!directed) {
            adj[v].push_back(Edge(u, weight));
            m += 1;
        } else {
            adj_rev[v].push_back(Edge(u, weight));
            m += 1;
        }
    }
    
    // Generate random graph with n nodes and m edges
    static Graph generateRandomGraph(int nodes, int edges, bool directed = false, int maxWeight = 1, unsigned seed = 0) {
        if (seed == 0) {
            seed = time(NULL);
        }
        srand(seed);
        
        Graph g(nodes, directed);
        int maxPossibleEdges = directed ? nodes * (nodes - 1) : nodes * (nodes - 1) / 2;
        edges = std::min(edges, maxPossibleEdges);
        
        std::set<std::pair<int, int>> usedEdges;
        
        while (g.m < edges) {
            int u = rand() % nodes;
            int v = rand() % nodes;
            
            if (u == v) continue; // no self-loops
            
            if (!directed && u > v) std::swap(u, v); // for undirected graphs, normalize edge representation
            
            if (usedEdges.find({u, v}) == usedEdges.end()) {
                int weight = (maxWeight > 1) ? (rand() % maxWeight) + 1 : 1;
                g.addEdge(u, v, weight);
                usedEdges.insert({u, v});
            }
        }
        
        return g;
    }
    
    // Generate graph with 0-1 weights
    static Graph generateRandomGraph01(int nodes, int edges, bool directed = false, double prob0 = 0.3, unsigned seed = 0) {
        if (seed == 0) {
            seed = time(NULL);
        }
        srand(seed);
        
        Graph g(nodes, directed);
        int maxPossibleEdges = directed ? nodes * (nodes - 1) : nodes * (nodes - 1) / 2;
        edges = std::min(edges, maxPossibleEdges);
        
        std::set<std::pair<int, int>> usedEdges;
        
        while (g.m < edges) {
            int u = rand() % nodes;
            int v = rand() % nodes;
            
            if (u == v) continue;
            
            if (!directed && u > v) std::swap(u, v);
            
            if (usedEdges.find({u, v}) == usedEdges.end()) {
                double r = (double)rand() / RAND_MAX;
                int weight = (r < prob0) ? 0 : 1;
                g.addEdge(u, v, weight);
                usedEdges.insert({u, v});
            }
        }
        
        return g;
    }
};

#endif // GRAPH_H