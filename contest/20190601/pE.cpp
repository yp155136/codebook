/*
weight tree
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int N = 200006;

vector<pii> G[N];
ll ans;

void dfs(int now,int par) {
    ll sum=0;
    ll mn = (1ll<<60);
    int k = 0;
    for (pii p:G[now]) {
        sum += p.second;
        mn = min(mn,p.second*1ll);
        ++k;
        if (p.first != par) {
            dfs(p.first,now);
        }
    }
    ans += (k-1)*mn + (sum-mn);
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n; scanf("%d",&n);
        for (int i=0;i<=n;++i) {
            G[i].clear();
        }
        for (int i=1;i<n;++i) {
            int x,y,z; scanf("%d%d%d",&x,&y,&z);
            G[x].push_back(make_pair(y,z));
            G[y].push_back(make_pair(x,z));
        }
        ans = 0;
        dfs(1,1);
        printf("%lld\n",ans);
    }
}

