struct Tree {
    int n, q;
    vector<vector<int>> adj;
    // each node has a query-list
    vector<vector<pair<int, int>>> queries;
    vector<int> ans;
    vector<int> f; // DSU
    vector<int> ancestor;
    vector<bool> vis;

    Tree(int _n, int _q) : n(_n), q(_q) {
        adj.resize(n);
        queries.resize(n);
        ans.resize(q);
        vis.assign(n, false);
        f.resize(n);
        ancestor.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
            ancestor[i] = i;
        }
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void addQuery(int u, int v, int idx) {
        queries[u].push_back({v, idx});
        queries[v].push_back({u, idx});
    }

    int find(int x) {
        while (f[x] != x) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    void merge(int u, int v) {
        int fu = find(u);
        int fv = find(v);
        f[fv] = fu;
    }

    void tarjan(int u, int fa = -1) {
        vis[u] = true;
        ancestor[u] = u;
        for (int v : adj[u]) {
            if (v == fa) {
                continue;
            }
            tarjan(v, u);
            merge(u, v);
            ancestor[find(u)] = u;
        }
        for (auto &q : queries[u]) {
            int v = q.first;
            int idx = q.second;
            if (vis[v]) {
                ans[idx] = ancestor[find(v)];
            }
        }
    }

    void solve(int root = 0) {
        tarjan(root, -1);
    }
};