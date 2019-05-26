#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int in_group(ll x) {
    int ret=0;
    while (x>0) {
        ret++;
        x/=10;
    }
    return ret;
}

ll ppow(ll a,ll n) {
    ll ret=1;
    while (n--) ret*=a;
    return ret;
}

ll group_end(ll x) {
    return ppow(10,x)-1;
}

ll group_st(ll x) {
    return ppow(10,x-1);
}

ll cal(ll L,ll R) {
    //cout << "L = " << L << " , R = " << R << endl;
    ll ret=0;
    while (in_group(L) != in_group(R)) {
        ll tmpR = group_end( in_group(L) );
        ret += in_group(L) * (tmpR-L+1);
        L = group_st(in_group(L)+1);
    }
    if (in_group(L) == in_group(R)) {
        ret += in_group(L) * (R-L+1);
    }
    //cout << "L = " << L << " , R = " << R << " , ret = " << ret << endl;
    return ret;
}

void solve() {
    ll n,x; cin >> n >> x;
    ll L=x,R = ll(2e15) + 6;;
    while (R-L != 1) {
        ll mid=(L+R)>>1;
        if (cal(x,mid) <= n) L = mid;
        else R = mid;
    }
    if (cal(x,L) == n) printf("%lld\n",L-x+1);
    else puts("-1");
}

int main () {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

