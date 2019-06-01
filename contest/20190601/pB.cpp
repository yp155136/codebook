#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define F first
#define S second
const int N = 100006;

vector<int> v[N];
int l[N];
int a[N], b[N];

void f(pii &p) {
    ll g = __gcd(p.F,p.S);
    p.F /= g;
    p.S /= g;
}

ll pre[N];
bool ff[N];

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n,m; scanf("%d%d",&n,&m);
        for (int i = 1;i <= m; ++i) {
            v[i].clear();
            scanf("%d",&l[i]);
        }
        for (int i=1;i <= n;++i) {
            scanf("%d%d",&a[i],&b[i]);
            v[ b[i] ].push_back(a[i]);
            pre[i] = 0;
            ff[i] = false;
        }
        vector<pii> vv;
        for (int i = 1;i <= m; ++i) {
            sort(v[i].begin(), v[i].end(),[](const int &a,const int &b) {
                return a>b;
            });
            int x = (int)v[i].size();
            ll tmp = 0;
            for (int j = 0;j < x; ++j) {
                if (j+1 == l[i]) {
                    pre[ l[i] ] += tmp;
                }
                else {
                    tmp += v[i][j];
                }
                if (j+1 >= l[i])vv.push_back(make_pair(v[i][j],j+1));
            }
        }
        sort(vv.begin(),vv.end(),[](const pii &p1,const pii &p2) {
            return p1.S < p2.S;
        });
        pii ans = make_pair(0,1);
        ll s=0;
        for (pii p:vv) {
            if (!ff[p.S]) {
                s += pre[p.S];
                ff[p.S] = true;
            }
            s += p.F;
            pii tmp = make_pair(s,p.S);
            f(tmp);
            if (tmp.first * ans.second > tmp.second * ans.first) ans = tmp;
        }
        printf("%lld/%lld\n",ans.F,ans.S);
    }
}

