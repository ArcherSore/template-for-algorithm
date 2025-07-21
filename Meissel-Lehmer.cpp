/*
    求 π(x)，小于等于x的素数个数
    复杂度 O(n^{2/3}/log^2(n))
*/
i64 ML(i64 N) {
    if(N <= 1) return 0;
    int v = sqrt(N + 0.5);
    int n_4 = sqrt(v + 0.5);
    int T = min((int)sqrt(n_4) * 2, n_4);
    int K = pow(N, 0.625) / log(N) * 2;
    K = max(K, v);
    K = min<i64>(K, N);
    int B = N / K;
    B = N / (N / B);
    B = min<i64>(N / (N / B), K);

    vector<i64> l(v + 1);
    vector<int> s(K + 1);
    vector<bool> e(K + 1);
    vector<int> w(K + 1);
    for (int i = 1; i <= v; ++i) l[i] = N / i - 1;
    for (int i = 1; i <= v; ++i) s[i] = i - 1;

    const auto div = [] (i64 n, int d) -> int { return double(n) / d; };
    int p;
    for (p = 2; p <= T; ++p) 
        if (s[p] != s[p - 1]) {
            i64 M = N / p;
            int t = v / p, t0 = s[p - 1];
            for (int i = 1; i <= t; ++i) l[i] -= l[i * p] - t0;
            for (int i = t + 1; i <= v; ++i) l[i] -= s[div(M, i)] - t0;
            for (int i = v, j = t; j >= p; --j)
                for (int l = j * p; i >= l; --i)
                    s[i] -= s[j] - t0;
            for (int i = p * p; i <= K; i += p) e[i] = 1;
        }
    e[1] = 1;
    int cnt = 1;
    vector<int> roughs(B + 1);
    for (int i = 1; i <= B; ++i)
        if(!e[i]) roughs[cnt++] = i;
    roughs[cnt] = 0x7fffffff;
    for (int i = 1; i <= K; ++i) w[i] = e[i] + w[i - 1];
    for (int i = 1; i <= K; ++i) s[i] = w[i] - w[i - (i & -i)];

    const auto query = [&] (int x) -> int {
        int sum = x;
        while(x) sum -= s[x], x ^= x & -x;
        return sum;
    };
    const auto add = [&] (int x) -> void {
        e[x] = 1;
        while(x <= K) ++s[x], x += x & -x;
    };
    cnt = 1;
    for (; p <= n_4; ++p) 
        if(!e[p]) {
            i64 q = i64(p) * p, M = N / p;
            while(cnt < q) w[cnt] = query(cnt), cnt++;
            int t1 = B / p, t2 = min<i64>(B, M / q), t0 = query(p - 1);
            int id = 1, i = 1;
            for (; i <= t1; i = roughs[++id]) l[i] -= l[i * p] - t0;
            for (; i <= t2; i = roughs[++id]) l[i] -= query(div(M, i)) - t0;
            for (; i <= B; i = roughs[++id]) l[i] -= w[div(M, i)] - t0;
            for (int i = q; i <= K; i += p)
                if(!e[i]) add(i);
        }
    while(cnt <= v) w[cnt] = query(cnt), cnt++;

    vector<int> primes;
    primes.push_back(1);
    for (int i = 2; i <= v; ++i)
        if(!e[i]) primes.push_back(i);
    l[1] += i64(w[v] + w[n_4] - 1) * (w[v] - w[n_4]) / 2;
    for (int i = w[n_4] + 1; i <= w[B]; ++i) l[1] -= l[primes[i]];
    for (int i = w[B] + 1; i <= w[v]; ++i) l[1] -= query(N / primes[i]);
    for (int i = w[n_4] + 1; i <= w[v]; ++i) {
        int q = primes[i];
        i64 M = N / q;
        int e = w[M / q];
        if (e <= i)  break;
        l[1] += e - i;
        i64 t = 0;
        int m = w[sqrt(M + 0.5)];
        for (int k = i + 1; k <= m; ++k) t += w[div(M, primes[k])];
        l[1] += 2 * t - (i + m) * (m - i);
    }
    return l[1];
}