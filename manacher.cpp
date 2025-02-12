vector<int> manacher(string &s) {
    string t = "#";
    for (auto c : s) {
        t += c;
        t += '#';
    }

    int n = t.size();
    vector<int> d(n);

    for (int i = 0, j = 0; i < n; i++) {
        if (2 * j - i >= 0 && j + d[j] > i) {
            d[i] = min(d[2 * j - i], j + d[j] - i);
        }
        while (i - d[i] >= 0 && i + d[i] < n && t[i - d[i]] == t[i + d[i]]) {
            d[i] += 1;
        }
        if (i + d[i] > j + d[j]) {
            j = i;
        }
    }
    return d;
}