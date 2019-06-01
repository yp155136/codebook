#include <bits/stdc++.h>
using namespace std;

#define y1 yuuki
#define y2 saki
#define SZ(x) ((int)(x).size())
#define F first
#define S second
typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<pii,int> piii;
const int N = 100006;

ll x1[N],x2[N],y1[N],y2[N];

vector<piii> v[N];

void f(pii &p) {
    ll gcd = __gcd(abs(p.F),abs(p.S));
    if (gcd != 0) {
        p.F /= gcd;
        p.S /= gcd;
    }
    if (p.F < 0) {
        p.F = -p.F;
        p.S = -p.S;
    }
    if (p.F == 0 && p.S < 0) {
        p.S = -p.S;
    }
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n; scanf("%d",&n);
        map<pii,int> mp;
        int id = 0;
        for (int i = 1;i <= n;++i) {
            scanf("%lld%lld%lld%lld",&x1[i],&y1[i],&x2[i],&y2[i]);
            pii p = make_pair(y2[i] - y1[i],x2[i] - x1[i]);
            f(p);
            auto iter = mp.find(p);
            if (iter == mp.end()) {
                ++id;
                mp[p] = id;
                v[id].push_back(make_pair(p,i));
            }
            else {
                int ret = iter->second;
                v[ret].push_back(make_pair(p,i));
            }
        }
        ll ans = n * 1ll * n;
        for (int i=1;i <= id;++i) {
            //cout << "v[i] size = " << SZ(v[i]) << endl;
            ans -= SZ(v[i])*1ll*SZ(v[i]);
            pii p = v[i][0].first;
            map<pii,int> mp2;
            if (p == make_pair(0ll,1ll)) {
                for (piii q:v[i]) {
                    mp2[ make_pair(y1[q.S],1) ]++;
                }
            }
            else if (p == make_pair(1ll,0ll)) {
                for (piii q:v[i]) {
                    mp2[ make_pair(x1[q.S],1) ]++;
                }
            }
            else {
                for (piii q:v[i]) {
                    int i = q.second;
                    pii pt = 
                    make_pair(x1[i]*(y2[i]-y1[i])-y1[i]*(x2[i]-x1[i]) 
                    ,y2[i]-y1[i] );
                    f(pt);
                    mp2[pt]++;
                }
            }
            for (auto p:mp2) {
                //cout << "p = " << p.S << endl;
                ans += p.S * 1ll * (p.S - 1);
            }
        }
        printf("%lld\n",ans/2);

        for (int i=1;i <= id;++i) {
            v[i].clear();
        }
    }
}

