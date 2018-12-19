#include <bits/stdc++.h>
using namespace std;
const int N = 800006;

int low[N],dfn[N];
bool vis[N];
int cnt[N];
int e[N],x[N],y[N];
int stamp;

vector<int> G[N];
vector<int> bcc[N];
int bcc_no = 0;
stack<int> sta;

void dfs(int now,int par) {
    vis[now] = true;
    dfn[now] = low[now] = (++stamp);
    for (int i:G[now]) {
        int to=(e[i]^now);
        if (to == par) continue;
        if (!vis[to]) {
            sta.push(i); dfs(to,now);
            low[now] = min(low[now],low[to]);
            if (low[to] >= dfn[now]) {
                ++bcc_no; int p;
                do {
                    p = sta.top(); sta.pop();
                    bcc[bcc_no].push_back(p);
                } while (p != i);
            }
        }
        else if (dfn[to] < dfn[now]) {
            sta.push(i);
            low[now] = min(low[now],dfn[to]);
        }
    }
}
