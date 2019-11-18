struct line {
    ll a, b;
    line(): a(0), b(0) {}
    line(ll a, ll b): a(a), b(b) {}
    ll operator()(ll x) const { return a * x + b; }
};

struct lichao {
    line st[NN];
    int sz, lc[NN], rc[NN];
    int gnode() {
        st[sz] = line(0, -1e18); //min: st[sz] = line(0, 1e18);
        lc[sz] = -1, rc[sz] = -1;
        return sz++;
    }
    void init() {
        sz = 0; gnode();
    }
    void add(int l, int r, line tl, int o) {
        //[l, r)
        bool lcp = st[o](l) < tl(l); //min: change < to >
        bool mcp = st[o]((l + r) / 2) < tl((l + r) / 2); //min: change < to >
        if (mcp) swap(st[o], tl);
        if (r - l == 1) return;
        if (lcp != mcp) {
            if (lc[o] == -1) lc[o] = gnode();
            add(l, (l + r) / 2, tl, lc[o]);
        } else {
            if (rc[o] == -1) rc[o] = gnode();
            add((l + r) / 2, r, tl, rc[o]);
        }
    }
    ll query(int l, int r, int x, int o) {
        if (r - l == 1) return st[o](x);
        if (x < (l + r) / 2) {
            if (lc[o] == -1) return st[o](x);
            return max(st[o](x), query(l, (l + r) / 2, x, lc[o]));
        } else {
            if (rc[o] == -1) return st[o](x);
            return max(st[o](x), query((l + r) / 2, r, x, rc[o]));
        }
    }
} solver;
