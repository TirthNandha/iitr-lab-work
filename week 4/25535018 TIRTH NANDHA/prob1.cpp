#include "graph.h"
#include <queue>
#include <stack>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstring>
#include <vector>
using namespace std;

void bfsTraversal(const Graph& graph, unsigned int startVertex, vector<bool>& isVisited) {
    queue<unsigned int> q;
    q.push(startVertex);
    isVisited[startVertex] = true;
    
    while (!q.empty()) {
        unsigned int u = q.front();
        q.pop();
        
        for (const Edge& edge : graph.adj[u]) {
            if (!isVisited[edge.to]) {
                isVisited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }
}

void dfsTraversalIter(const Graph& graph, unsigned int startVertex, vector<bool>& isVisited) {
    stack<unsigned int> nodeStack;
    nodeStack.push(startVertex);
    
    while (!nodeStack.empty()) {
        unsigned int currentNode = nodeStack.top();
        nodeStack.pop();
        
        if (!isVisited[currentNode]) {
            isVisited[currentNode] = true;
            for (const Edge& edge : graph.adj[currentNode]) {
                if (!isVisited[edge.to]) {
                    nodeStack.push(edge.to);
                }
            }
        }
    }
}

void dfsRecurse(const Graph& graph, unsigned int node, vector<bool>& isVisited) {
    isVisited[node] = true;
    
    for (const Edge& edge : graph.adj[node]) {
        if (!isVisited[edge.to]) {
            dfsRecurse(graph, edge.to, isVisited);
        }
    }
}

void dfsTraversalRec(const Graph& graph, unsigned int startVertex, vector<bool>& isVisited) {
    dfsRecurse(graph, startVertex, isVisited);
}

void runFullBfs(const Graph& graph) {
    vector<bool> isVisited(graph.n, false);
    unsigned int vertex = 0;
    while (vertex < graph.n) {
        if (!isVisited[vertex]) {
            bfsTraversal(graph, vertex, isVisited);
        }
        vertex++;
    }
}

void runFullDfsIter(const Graph& graph) {
    vector<bool> isVisited(graph.n, false);
    for (unsigned int vertex = 0; vertex < graph.n; vertex++) {
        if (!isVisited[vertex]) {
            dfsTraversalIter(graph, vertex, isVisited);
        }
    }
}

void runFullDfsRec(const Graph& graph) {
    vector<bool> isVisited(graph.n, false);
    unsigned int vertex = 0;
    do {
        if (!isVisited[vertex]) {
            dfsTraversalRec(graph, vertex, isVisited);
        }
        vertex++;
    } while (vertex < graph.n);
}

int main(int argc, char* argv[]) {
    
    if (argc < 5 || argc > 6) {
        cout << "Use: <graphType> <nodes> <sparsityOrEdges> <seed> [algo]" << endl;
        cout << "Types: VARM, VARN" << endl;
        cout << "VARM: nodes, edges" << endl;
        cout << "VARN: sparsity=1(2n),2(nlogn),3(nsqrt(n)),4(max)" << endl;
        cout << "Algo: bfs,dfs_iter,dfs_rec" << endl;
        return 0;
    }
    
    unsigned int nodeCount = atoi(argv[2]);
    unsigned int edgeParam = atoi(argv[3]);
    unsigned int seedVal = atoi(argv[4]);
    string algoChoice = (argc == 6) ? argv[5] : "all";
    string graphKind = argv[1];
    
    unsigned int edgeCount;
    if (graphKind == "VARM") {
        edgeCount = edgeParam;
    } else if (graphKind == "VARN") {
        if (edgeParam == 1) {
            edgeCount = 2 * nodeCount;
        } else if (edgeParam == 2) {
            edgeCount = nodeCount * (unsigned int)(log(nodeCount) + 0.5);
        } else if (edgeParam == 3) {
            edgeCount = nodeCount * (unsigned int)sqrt(nodeCount);
        } else if (edgeParam == 4) {
            edgeCount = nodeCount * (nodeCount - 1) / 2;
        } else {
            cout << "Invalid sparsity" << endl;
            return 0;
        }
    } else {
        cout << "Wrong graph type" << endl;
        return 0;
    }
    
    Graph g = Graph::generateRandomGraph(nodeCount, edgeCount, false, 1, seedVal);
    
    if (algoChoice == "all") {
        auto startTime = chrono::high_resolution_clock::now();
        runFullBfs(g);
        auto endTime = chrono::high_resolution_clock::now();
        long long bfsTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
        
        startTime = chrono::high_resolution_clock::now();
        runFullDfsIter(g);
        endTime = chrono::high_resolution_clock::now();
        long long dfsIterTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
        
        startTime = chrono::high_resolution_clock::now();
        runFullDfsRec(g);
        endTime = chrono::high_resolution_clock::now();
        long long dfsRecTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
        
        cout << "GRAPH_TRAVERSAL," << graphKind << "," << nodeCount << "," << edgeCount << ",BFS," << bfsTime << endl;
        cout << "GRAPH_TRAVERSAL," << graphKind << "," << nodeCount << "," << edgeCount << ",DFS_ITER," << dfsIterTime << endl;
        cout << "GRAPH_TRAVERSAL," << graphKind << "," << nodeCount << "," << edgeCount << ",DFS_REC," << dfsRecTime << endl;
    } else {
        auto startTime = chrono::high_resolution_clock::now();
        string algoName;
        
        if (algoChoice == "bfs") {
            runFullBfs(g);
            algoName = "BFS";
        } else if (algoChoice == "dfs_iter") {
            runFullDfsIter(g);
            algoName = "DFS_ITER";
        } else if (algoChoice == "dfs_rec") {
            runFullDfsRec(g);
            algoName = "DFS_REC";
        } else {
            cout << "Bad algo: " << algoChoice << endl;
            return 1;
        }
        
        auto endTime = chrono::high_resolution_clock::now();
        long long execTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
        
        cout << "GRAPH_TRAVERSAL," << graphKind << "," << nodeCount << "," << edgeCount << "," << algoName << "," << execTime << endl;
    }
    
    return 0;
}