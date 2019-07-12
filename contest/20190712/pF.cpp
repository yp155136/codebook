#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
const int N = 206;
const int INF = 0x3f3f3f3f;

int dp[N][N];
int d[N][N];

int r[N];
int u[N * N], v[N * N], w[N * N];
int ans[N * N];

int main () {
    int T; scanf("%d", &T);
    int cases = 0;
    while (T--) {
        int n, q; scanf("%d%d", &n, &q);
        memset(dp, INF, sizeof(dp));
        vector<int> idx;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &r[i]);
            dp[i][i] = 0;
            idx.push_back(i);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &d[i][j]);
                dp[i][j] = d[i][j];
            }
        }
        vector<int> ok;
        vector<int> qs;
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d", &u[i], &v[i], &w[i]);
            qs.push_back(i);
        }
        sort(idx.begin(), idx.end(), [](const int &a, const int &b) {
            return r[a] < r[b];
        });
        sort(qs.begin(), qs.end(), [](const int &a, const int &b) {
            return w[a] < w[b];
        });
        int ptr = 0;
        for (int k: idx) {
            while (ptr < (int)qs.size() && w[qs[ptr]] < r[k]) {
                ans[ qs[ptr] ] = dp[ u[ qs[ptr] ] ][ v[ qs[ptr] ] ];
                ++ptr;
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        while (ptr < (int)qs.size()) {
            ans[ qs[ptr] ] = dp[ u[ qs[ptr] ] ][ v[ qs[ptr] ] ];
            ++ptr;
        }
        printf("Case #%d:\n", ++cases);
        for (int i = 1; i <= q; ++i) {
            printf("%d\n", ans[i]);
        }
    }
}

