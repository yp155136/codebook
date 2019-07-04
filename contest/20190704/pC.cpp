#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 400006;

struct BIT {
    int a[N];
    int n;
    void init(int _n) {
        n = _n + 3;
        for (int i = 0; i <= n; ++i) {
            a[i] = 0;
        }
    }
    void update(int pos, int val) {
        for (int i = pos; i < n; i += i & (-i)) {
            a[i] += val;
        }
    }
    int query(int pos) {
        if (pos == 0) return 0;
        int ret = 0;
        for (int i = pos; i > 0; i -= i & -i) {
            ret += a[i];
        }
        return ret;
    }
    int Q(int L, int R) {
        return query(R) - query(L - 1);
    }
} bit;

vector<int> G[N];
vector<int> sons[N];
vector<int> v[N];
int c[N];
int sz[N];
int stamp;
int idx[N];
int L[N], R[N];

void dfs(int now, int par) {
    ++stamp;
    L[now] = stamp;
    sz[now] = 1;
    for (int i: G[now]) {
        if (i != par) {
            dfs(i, now);
            sz[now] += sz[i];
            sons[now].push_back(i);
        }
    }
    v[ c[now] ].push_back(now);
    R[now] = stamp;
}

typedef long long ll;

int main () {
    int n;
    int cases = 0;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; ++i) {
            G[i].clear();
            sons[i].clear();
            v[i].clear();
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &c[i]);
        }
        for (int i = 1; i < n; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            G[x].push_back(y); G[y].push_back(x);
        }
        stamp = 0;
        dfs(1, 1);
        bit.init(n);
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (v[i].empty()) continue;
            //color i
            long long all = n * 1ll * (n - 1) / 2;
            vector< pair<int, int> > vv;
            for (int j: v[i]) {
                ll s = 1;
                for (int son: sons[j]) {
                    int tmp = sz[son] - bit.Q(L[son], R[son]);
                    all -= tmp * 1ll * (tmp - 1) / 2;
                    s += tmp;
                }
                bit.update(L[j], s);
                vv.push_back(make_pair(L[j], s));
            }
            ll yuuki = n - bit.Q(1, n);
            all -= yuuki * (yuuki - 1) / 2;
            ans += all;
            for (pair<int, int> p: vv) {
                bit.update(p.first, -p.second);
            }
        }
        printf("Case #%d: %lld\n", ++cases, ans);
    }
}

