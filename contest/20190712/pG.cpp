#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int K = 101;
const int N = 100001;
const ll INF = (1ll << 60);

vector<int> G[N];

int x[N], y[N], w[N], e[N];

ll dp[N][K];

int n, k;

int dfs(int now, int par, int par_w) {
    dp[now][0] = 0;
    if ((int)G[now].size() == 1)  {
        dp[now][1] = par_w * (k - 1);
        return 1;
    }
    int ret_sz = 0;
    for (int id: G[now]) {
        int to = (e[id] ^ now);
        if (to == par) continue;
        int ret = dfs(to, now, w[id]);
        ret_sz += ret;
        for (int i = min(k, ret_sz); i >= 0; --i) {
            for (int j = 0; j <= min(k, ret); ++j) {
                dp[now][i] = min(dp[now][i], dp[now][i - j] + dp[to][j]);
            }
        }
    }
    for (int i = 0; i <= min(ret_sz, k); ++i) {
        dp[now][i] += i * 1ll * (k - i) * 1ll * par_w;
    }
    return ret_sz;
}

int main () {
    int T; scanf("%d", &T);
    int cases = 0;
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i <= n; ++i) {
            G[i].clear();
        }
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%d", &x[i], &y[i], &w[i]);
            e[i] = x[i] ^ y[i];
            G[ x[i] ].push_back(i);
            G[ y[i] ].push_back(i);
        }
        printf("Case #%d: ", ++cases);
        if (n <= 2) {
            if (k <= 1) puts("0");
            else printf("%d\n", w[1]);
            continue;
        }
        int root = -1;
        for (int i = 1; i <= n; ++i) {
            if ( (int)G[i].size() != 1) {
                root = i;
                break;
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = INF;
            }
        }
        dfs(root, root, 0);
        printf("%lld\n", dp[root][k]);
    }
}

