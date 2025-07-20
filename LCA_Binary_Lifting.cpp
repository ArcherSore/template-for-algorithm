struct Tree {
    int n, LOG;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<vector<int>> adj;

    Tree(int n) : n(n) {
        LOG = __lg(n) + 1;
        parent.assign(LOG, vector<int>(n, -1));
        depth.assign(n, 0);
        adj.resize(n);
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p) {
        parent[0][u] = p;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void init(int root = 0) {
        dfs(root, -1);
        for (int k = 0; k < LOG - 1; k++) {
            for (int u = 0; u < n; u++) {
                if (parent[k][u] == -1) {
                    parent[k + 1][u] = -1;
                } else {
                    parent[k + 1][u] = parent[k][parent[k][u]];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (d & (1 << i)) {
                u = parent[i][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    }

    int dist(int u, int v) {
        // calculate the distance between node u and node v
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};