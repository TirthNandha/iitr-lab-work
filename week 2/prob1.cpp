#include <iostream>
#include<vector>
#include<list>
#include<queue>
#include<climits>
using namespace std;
    
int n, m;
bool directed;

void dfsRec(vector<vector<int>> &adj, vector<bool> &visited ,int s, int level, vector<pair<int, int>> & res) {
        visited[s] = true;
        res.push_back({s, level});
        for(int adjVert: adj[s]) {
            if(!visited[adjVert])
            dfsRec(adj, visited, adjVert, level + 1, res);
        }
    }

void bfs(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    vector<pair<int, int>> res;
    queue<pair<int, int>> queue;
    queue.push({0, 0});
    visited[0] = true;

    while(!queue.empty()) {
        pair<int, int> front = queue.front();
        int curr = front.first;
        int level = front.second;
        queue.pop();

        res.push_back({curr, level});
        
        for(int adjVert: adj[curr]){
            if(!visited[adjVert]){
                visited[adjVert] = true;
                queue.push({adjVert, level+1});
            }
        }
    }

    for (auto& pair : res) {
        cout << pair.first << " " << pair.second << endl;
    }
}

void dfs(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    vector<pair<int, int>> res;
    dfsRec(adj, visited, 0, 0, res);
    for (auto& pair : res) {
        cout << pair.first << " " << pair.second << endl;
    }
}
void dijkstra(vector<list<pair<int,int>>> &adj) {
    int n = adj.size();
    vector<int> visited(n, false);
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[0] = 0;
    pq.push({0,0});
    
    while(!pq.empty()){
        pair<int, int> top = pq.top();
        pq.pop();
        int  d = top.first;
        int u = top.second;

        if(visited[u]) continue;

        visited[u] = true;
        
        for(auto &edge: adj[u]){
            int v = edge.first;
            int w = edge.second;
            if(!visited[v] && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1) {
            cout << parent[v] << " " << v << "\n";
        }
    }
}
void wbfs(vector<list<pair<int,int>>> &adj);void wbfs(vector<list<pair<int, int>>> &adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    deque<int> dq;
    dist[0] = 0;
    dq.push_front(0);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (w == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            cout << parent[v] << " " << v << "\n";
        }
    }
}

void prim(vector<list<pair<int,int>>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> key(n, INT_MAX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int k = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1) {
            cout << parent[v] << " " << v << "\n";
        }
    }
}



int main() {
    freopen("inp.txt", "r", stdin);
    cin >> n >> m;
#ifdef DIR
    directed = true;
#endif

#ifdef BFS
    vector<vector<int>> adj(n);
    for(int i=0;i < m; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        if(!directed) adj[v].push_back(u);
    }
    bfs(adj);
#elif DFS
    vector<vector<int>> adj(n);
    for(int i=0;i < m; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        if(!directed) adj[v].push_back(u);
    }
    dfs(adj);
#elif DJK
    vector<list<pair<int,int>>> adj(n);
    for(int i=0;i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        if(!directed) adj[v].push_back({u,w});
    }
    dijkstra(adj);
#elif WBFS
    vector<list<pair<int,int>>> adj(n);
    for(int i=0;i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        if(!directed) adj[v].push_back({u,w});
    }
    wbfs(adj);
#elif PRM
    vector<list<pair<int,int>>> adj(n);
    for(int i=0;i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        if(!directed) adj[v].push_back({u,w});
    }
    prim(adj);
#endif
    
    return 0;
}