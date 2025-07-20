struct Prim {
    int n;
    vector<vector<PII>> adj;
    
    Prim(int n): n(n) {
        adj.assign(n, vector<PII>());
    }
    
    void add(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    int MST(int start = 0) {
        int cost = 0;
        vector<bool> vis(n, false);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({0, start});
        while (!pq.empty()){
            auto [w, u] = pq.top();
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            cost += w;
            for (auto [v, w] : adj[u]) {
                if (!vis[v])
                    pq.push({w, v});
            }
        }
        return cost;
    }
};