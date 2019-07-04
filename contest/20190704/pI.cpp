#include <bits/stdc++.h>
using namespace std;

const int N = 2006;

vector<int> G[N];
vector<int> v[N];
int x[N], y[N], w[N], e[N];
bool vis[N];

int d[N];
int fa_wei[N];
int fa[N];
int v_id = 0;

void ddfs(int now, int par, int cur_depth) {
    vis[now] = true;
    d[now] = cur_depth;
    for (int i: G[now]) {
        int to = (e[i] ^ now);
        if (to == par) continue;
        if (vis[to] == false) {
            fa_wei[to] = w[i];
            fa[to] = now;
            ddfs(to, now, cur_depth + 1);
        }
        else if (d[to] < d[now]){
            int tmp = now;
            v_id++;
            while (tmp != to) {
                v[ v_id ].push_back(fa_wei[tmp]);
                fa_wei[tmp] = 0;
                tmp = fa[tmp];
            }
            v[ v_id ].push_back( w[i] );
        }
    }
    /*if (now != par && fa_wei[now] > 0) {
        ++v_id;
        v[ v_id ].push_back(fa_wei[now]);
    }*/
}

int pre[N];

int Q(int L, int R) {
    return pre[R] - pre[L - 1];
}

int idx[N];

int tot = 0;
int tot_cnt = 0;
int tar;
int k;

#define yuuki if(tot_cnt>=k)return;

void dfs(int nowi, int pre) {
    if (Q(nowi, v_id) + pre < tar) return;
    if (nowi == v_id) {
        for (int j: v[ idx[nowi] ]) {
            if (pre + j >= tar) {
                ++tot_cnt;
                yuuki
                //if (tot_cnt >= k) return;
            }
            else break;
        }
        return;
    }
    else {
        for (int j: v[ idx[nowi] ]) {
            dfs(nowi + 1, pre + j);
            yuuki;
        }
    }
}

bool check(int mid) {
    tot_cnt = 0;
    tar = tot - mid;
    dfs(1, 0);
    if (tot_cnt >= k) return true;
    else return false;
}

vector<unsigned int> saki;

void dfs2(int nowi, int pre) {
    if (Q(nowi, v_id) + pre < tar) return;
    if (nowi == v_id) {
        for (int j: v[ idx[nowi] ]) {
            if (pre + j >= tar) {
                saki.push_back(pre + j);
                ++tot_cnt;
                yuuki
                //if (tot_cnt >= k) return;
            }
            else break;
        }
        return;
    }
    else {
        for (int j: v[ idx[nowi] ]) {
            dfs2(nowi + 1, pre + j);
            yuuki;
        }
    }
}

int main () {
    int n, m;
    int cases = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i <= m + 4; ++i) {
            G[i].clear();
            v[i].clear();
            vis[i] = false;
            fa_wei[i] = 0;
        }
        v_id = 0;
        tot = 0;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &x[i], &y[i], &w[i]);
            e[i] = (x[i] ^ y[i]);
            G[ x[i] ].push_back(i);
            G[ y[i] ].push_back(i);
            tot += w[i];
        }
        ddfs(1, 1, 1);
        scanf("%d", &k);
        int all = 1;
        int L = 0, R = 0;
        for (int i = 1; i <= v_id; ++i) {
            sort(v[i].begin(), v[i].end(), [](const int &a, const int &b) {
                return a > b;
            });
            idx[i] = i;
            all *= (int)v[i].size();
            if (all > k) all = k;
            int nn = (int)v[i].size();
            /*for (int j = 0; j < nn - 1; ++j) {
                R += v[i][j];
            }
            for (int j = 1; j < nn; ++j) {
                L += v[i][j];
            }*/
            R += v[i][ nn - 1 ];
            L += v[i][ 0 ];
        }
        k = all;
        sort(idx + 1, idx + v_id + 1, [](const int &a, const int &b) {
            return (int)v[a].size() > (int)v[b].size();
        });
        for (int i = 1; i <= v_id; ++i) {
            pre[ i ] = pre[ i - 1 ] + v[ idx[i] ][0];
        }
        R = tot - R;
        L = tot - L;
        --L;
        while (R - L != 1) {
            int mid = (L + R) >> 1;
            if (check(mid)) R = mid;
            else L = mid;
        }
        saki.clear();
        tot_cnt = 0;
        tar = tot - L;
        dfs2(1, 0);
        while ( (int)saki.size() != k) {
            saki.push_back(tot - (R));
        }
        sort(saki.begin(), saki.end());
        unsigned int ans = 0;
        unsigned int gg = 1;
        for (unsigned int i = k - 1; i >= 0 && i != (0u - 1); --i) {
            unsigned int x = tot - saki[i];
            ans += gg * x;
            ++gg;
        }
        cout << "Case #" << ++cases << ": " << ans << '\n';
    }
}

