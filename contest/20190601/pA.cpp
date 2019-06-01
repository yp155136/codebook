#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
using namespace std;
// using namespace __gnu_pbds;
typedef long long ll;
const int MAX = 1e5 + 5;
const int MM = 'A' + 'B';
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> pii;
#define eb emplace_back
#define F first
#define S second
// vector<int> adj[MAX];
// vector<int> rev[MAX];
ll arr[MAX];
ll sum[MAX];
ll  n, m;

map<int,int>  mp[MAX];
// gp_hash_table<int, gp_hash_table<int,int> > mp;
struct mann
{
    int u, v, c, w;
    mann(){}
    mann(int _u, int _v, int _c, int _w):u(_u), v(_v), c(_c), w(_w){}
} bb[MAX];
bool cmp(mann a, mann b) {
    if(a.c != b.c)  return a.c > b.c;
    if(a.u != b.u)  return a.u > b.u;
    if(a.v != b.v)  return a.v > b.v;
    if(a.w != b.w)  return a.w > b.w;
}
ll dfs(int i, int nd, ll lef) {
    ll rt = 0;
    if(sum[nd] < arr[nd]) {
        ll mi = min(lef, arr[nd] - sum[nd]);
        mp[nd][i] += mi;
        sum[nd] += mi;
        rt += mi;
        lef -= mi;
        if(!lef)    return rt;
    }
    if(nd != bb[i].u) {
        ll x = dfs(i, nd/ 2, lef);
        rt += x;
        lef -= x;
        if(!lef)    return rt;
    }
    for(auto ii : mp[nd]) {
        int u = ii.F;
        int c = ii.S;
        if(nd != bb[u].u) {
            ll x = dfs(u, nd / 2, min((ll)c, lef));
            if(x) {
                mp[nd][u] -= x;
                mp[nd][i] += x;
                rt += x;
                lef -= x;
                if(!lef)    return rt;
            }
        } 
    }
    return rt;
}
int main(){
    ios_base::sync_with_stdio(0);   cin.tie(0);
    int T;
    cin >> T;
    while(T --) {
        // memset(sum, 0, sizeof sum);
        // mp.clear();
        // memset(cnt, 0, sizeof cnt);
        cin >> n >> m;
        for(int i = 1; i <= n; ++ i ) {
            cin >> arr[i];
        }
        for(int i = 1; i <= m; ++ i) {
            int u, v, c, w; cin >> u >> v >> c >> w;
            bb[i] = mann(u, v, w, c);
        }
        sort(bb + 1, bb + m + 1, cmp);
        ll ans = 0;
        for(int i = 1; i <= m; ++ i) {
            while(1) {
                ll x = dfs(i, bb[i].v, bb[i].w);
                bb[i].w -= x;
                ans += x * bb[i].c;
                if(!x || !bb[i].w)  break;
            }
        }

        cout << ans << '\n';
        for(int i = 1; i <= n; ++ i){
            mp[i].clear();
            sum[i] = 0;
        }
    }

    return 0;
}
