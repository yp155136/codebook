#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define F first
#define S second
const int N = 100006;

vector<pii> G[N];
vector<pii> yuuki;

pii make_range(int l1,int r1,int L,int R) {
    return make_pair(max(l1,L),min(r1,R));
}

bool okay(pii p) {
    return p.F <= p.S;
}

void dfs(int now,int par,int L,int R) {
    //cout << "now = " << now << " , par = " << par << " , L = " << L << " , R = " << R << endl;
    if (L > R) return;
    //[L, R] might be in now
    vector<pii> weights;
    for (pii p:G[now]) {
        if (p.F == par) continue;
        weights.push_back(make_pair(p.S,p.F));
    }
    sort(weights.begin(),weights.end());
    if (weights.size()) {
        //yuuki.push_back(make_pair(make_range(L,)))
        pii _ = make_range(L,weights[0].first,L,R);
        if (okay(_)) {
            yuuki.push_back(make_pair(_.first,now));
        }
        for (int i=0;i<(int)weights.size();++i) {
            if (i == (int)weights.size() - 1) {
                pii _ = make_range(weights[i].first+1,R,L,R);
                if (okay(_)) {
                    dfs(weights[i].second,now,_.F,_.S);
                }
            }
            else {
                pii _ = make_range(weights[i].first+1,weights[i+1].first,L,R);
                if (okay(_)) {
                    dfs(weights[i].second,now,_.F,_.S);
                }
            }
        }
    }
    else {
        yuuki.push_back(make_pair(L,now));
    }
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n,q;
        scanf("%d%d",&n,&q);
        for (int i=0;i<=n;++i) {
            G[i].clear();
        }
        for (int i=1;i<n;++i) {
            int x,y,z; scanf("%d%d%d",&x,&y,&z);
            G[x].push_back(make_pair(y,z));
            G[y].push_back(make_pair(x,z));
        }
        yuuki.clear();
        dfs(1,1,-1,1000000007);
        long long ans = 0;
        sort(yuuki.begin(),yuuki.end());
        yuuki.push_back(make_pair(1234567890,1));
        /*for (pii p:yuuki) {
            cout << "p = " << p.F << " , " << p.S << endl;
        }*/
        while (q--) {
            int x; cin >> x;
            pii p = *prev(lower_bound(yuuki.begin(),yuuki.end(),make_pair(x,n+1)));
            ans += p.S;
            //cout << "ans = " << p.F << " , " << p.S << endl;
        }
        printf("%lld\n",ans);
    }
}

