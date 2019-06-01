#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define F first
#define S second
const int N = 100006;

ll pre_l[N];
ll pre_r[N];
ll l[N],r[N];

ll Q_l(int L,int R) {
    return pre_l[R] - pre_l[L-1];
}

ll Q_r(int L,int R) {
    return pre_r[R] - pre_r[L-1];
}

ll cal(ll x,int n) {
    ll ret = 0;
    int id = lower_bound(r+1,r+n+1,x) - r;
    --id;
    ret += x * id - Q_r(1, id);
    id = lower_bound(l+1,l+n+1,x) - l;
    ret += Q_l(id, n) - x * (n - id + 1);
    return ret;
}

ll f(vector<pii> v) {
    //ll ans = 0;
    int n = (int)v.size();
    for (int i = 0; i < n; ++i) {
        l[i + 1] = v[i].first;
        r[i + 1] = v[i].second;
    }
    sort(l+1, l+n+1);
    sort(r+1, r+n+1);
    for (int i=1;i<=n;++i) {
        pre_l[i] = pre_l[i-1] + l[i];
        pre_r[i] = pre_r[i-1] + r[i];
    }
    ll ans = (1ll<<60);
    for (int i=1;i<=n;++i) {
        //consider point l[i]
        ans = min(ans,cal(l[i],n));
        ans = min(ans,cal(r[i],n));
    }
    return ans;
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n; scanf("%d",&n);
        vector<pii> x,y;
        for (int i=1;i <= n;++i) {
            int a,b,c,d; scanf("%d%d%d%d",&a,&b,&c,&d);
            x.push_back(make_pair(a,c));
            y.push_back(make_pair(b,d));
        }
        printf("%lld\n",f(x) + f(y));
    }
}

