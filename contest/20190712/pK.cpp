#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
#define F first
#define S second
const int N = 41;

ll w[N];
vector<int> G[N];

bool adj[N][N];

bool in_range(int L, int R, int x) {
    return L <= x && x <= R;
}

int vis[N];
int vis_id;

bool okay(vector<pii> &e, int L, int R) {
    for (pii p: e) {
        if (in_range(L, R, p.F) && in_range(L, R, p.S)) {
            if (vis[p.F] != vis_id && vis[p.S] != vis_id) return false;
        }
    }
    return true;
}

ll c[(1 << 19) + 2]; //3^n
ll b[(1 << 19) + 2];
ll a[(1 << 19) + 2];

int maskno[N];

int main () {
    memset(vis, -1, sizeof(vis));
    int T; scanf("%d", &T);
    int cases = 0;
    while (T--) {
        int n, m; 
        ll mod; 
        scanf("%d%d%lld", &n, &m, &mod);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &w[i]);
        }
        memset(adj, 0, sizeof(adj));
        for (int i = 0; i < N; ++i) {
            G[i].clear();
        }
        vector<pii> e;
        for (int i = 1; i <= m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            adj[x][y] = adj[y][x] = true;
            e.push_back(make_pair(x, y));
        }
        int n1 = n - n / 2, n2 = n / 2;
        vector<pii> cross;
        memset(maskno, 0, sizeof(maskno));
        for (pii p: e) {
            if (p.F <= n1 && p.S > n1 || p.S <= n1 && p.F > n1) {
                if (p.F > p.S) swap(p.F, p.S);
                cross.push_back(p);
                maskno[p.F - 1] |= (1 << (p.S - n1 - 1));
            }
        }
        for (int i = 0; i < (1 << n2); ++i) {
            ++vis_id;
            ll totw = 1;
            for (int j = 0; j < n2; ++j) {
                if ( ( (1 << j) & i ) != 0 ) {
                    totw *= w[ j + n1 + 1 ];
                    totw %= mod;
                    vis[j + n1 + 1] = vis_id;
                }
            }
            if (okay(e, n1 + 1, n)) {
                b[i] = totw;
            }
            else {
                b[i] = 0;
            }
            c[i] = b[i];
        }
        for (int i = 0; i < n2; ++i) {
            for (int j = (1 << n2) - 1; j >= 0; --j) {
                if (((1<<i)&j) == 0) {
                    c[j] += c[j ^ (1<<i)];
                    c[j] %= mod;
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < (1 << n1); ++i) {
            ++vis_id;
            ll totw = 1;
            for (int j = 0; j < n1; ++j) {
                if ( ( (1 << j) & i ) != 0 ) {
                    totw *= w[j + 1];
                    totw %= mod;
                    vis[ j + 1 ] = vis_id;
                }
            }
            if (okay(e, 1, n1)) {
                a[i] = totw;
            }
            else {
                a[i] = 0;
            }
            int mask = 0;
            for (int j = 0; j < n1; ++j) {
                if ( ( (1 << j) & i ) == 0 ) {
                    mask |= maskno[j];
                }
            }
            ans += a[i] * c[mask];
            ans %= mod;
        }
        /*if (n == 1) {
            ans = (w[1] + 1) % mod;
        }*/
        printf("Case #%d: %lld\n", ++cases, ans);
    }
}

