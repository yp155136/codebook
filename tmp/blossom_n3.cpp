
## Graph Matching ##
```cpp
struct Graph {
  int n, match[maxn];
  bool adj[maxn][maxn];
  void clear() {
    memset(adj, 0, sizeof(adj));
    n = 0;
  }
  int max(int a, int b) {
    if (a > b) { return a; }
    return b;
  }
  void get_max(int &n, int k) {
    if (k > n) { n = k; }
    return;
  }
  void insert(const int &u, const int &v) {
    get_max(n, max(u, v) + 1);
    adj[u][v] = adj[v][u] = 1;
  }
  int max_match() {
    memset(match, -1, sizeof(match));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (match[i] == -1) {
        ans += bfs(i);
      }
    }
    return ans;
  }
  int Q[maxn], pre[maxn], base[maxn];
  bool hash[maxn];
  bool in_blossom[maxn];
  int bfs(int p) {
    memset(pre, -1, sizeof(pre));
    memset(hash, 0, sizeof(hash));
    for (int i = 0; i < n; ++i) {
      base[i] = i;
    }
    Q[0] = p;
    hash[p] = 1;
    for (int s = 0, t = 1; s < t; ++s) {
      int u = Q[s];
      for (int v = 0; v < n; ++v) {
        if (adj[u][v] && base[u] != base[v] && v != match[u]) {
          if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
            int b = contract(u, v);
            for (int i = 0; i < n; ++i) {
              if (in_blossom[base[i]]) {
                base[i] = b;
                if (hash[i] == 0) {
                  hash[i] = 1;
                  Q[t++] = i;
                }
              }
            }
          } else if (pre[v] == -1) {
            pre[v] = u;
            if (match[v] == -1) {
              argument(v);
              return 1;
            } else {
              Q[t++] = match[v];
              hash[match[v]] = 1;
            }
          }
        }
      }
    }
    return 0;
  }
  void argument(int u) {
    while (u != -1) {
      int v = pre[u];
      int k = match[v];
      match[u] = v;
      match[v] = u;
      u = k;
    }
  }
  void change_blossom(int b, int u) {
    while (base[u] != b) {
      int v = match[u];
      in_blossom[base[v]] = in_blossom[base[u]] = true;
      u = pre[v];
      if (base[u] != b) {
        pre[u] = v;
      }
    }
  }
  int contract(int u, int v) {
    memset(in_blossom, 0, sizeof(in_blossom));
    int b = find_base(base[u], base[v]);
    change_blossom(b, u);
    change_blossom(b, v);
    if (base[u] != b) {
      pre[u] = v;
    }
    if (base[v] != b) {
      pre[v] = u;
    }
    return b;
  }
  int find_base(int u, int v) {
    bool in_path[maxn] = {};
    while (true) {
      in_path[u] = true;
      if (match[u] == -1) {
        break;
      }
      u = base[pre[match[u]]];
    }
    while (!in_path[v]) {
      v = base[pre[match[v]]];
    }
    return v;
  }
};
