int low[N],dfn[N];
bool vis[N];
int cnt[N], e[N], x[N], y[N];
int stamp, bcc_no = 0;

vector<int> G[N], bcc[N];
stack<int> sta;

void dfs(int now,int par) {
    vis[now] = true;
    dfn[now] = low[now] = (++stamp);
    for (int i:G[now]) {
        int to= ( e[i] ^ now );
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
