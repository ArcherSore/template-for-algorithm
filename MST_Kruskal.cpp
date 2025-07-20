struct DSU {
    vector<int> f, rank;

    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        rank.assign(n, 0);
    }
    
    int find(int x) {
        while (f[x] != x) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        f[b] = a;
        if (rank[a] == rank[b]) {
            rank[a]++;
        }
        return true;
    }
};

struct Kruskal {
    struct Edge {
        int u, v, w;
        Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
        bool operator<(const Edge &other) const {
            return w < other.w;
        }
    };

    int n;
    vector<Edge> edges;

    Kruskal(int n): n(n) {}

    void add(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
    }

    int MST() {
        // if maxmium the cost, use `greater<> ()`
        sort(edges.begin(), edges.end());
        DSU dsu(n);
        int cost = 0;
        for (auto &e : edges) {
            if (dsu.merge(e.u, e.v)) {
                cost += e.w;
            }
        }
        return cost;
    }
};