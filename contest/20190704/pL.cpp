#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1000006;
const ll mod = 1000000007; 

ll f[N], revf[N];

ll ppow(ll a, ll n) {
    ll ret = 1, now = a;
    while (n) {
        if (n & 1) {
            ret = ret * now;
            ret %= mod;
        }
        now = now * now;
        now %= mod;
        n >>= 1;
    }
    return ret;
}

void build() {
    f[0] = revf[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = f[i-1] * i % mod;
    }
    revf[N - 1] = ppow(f[N - 1], mod - 2);
    for (int i = N - 2; i >= 1; --i) {
        revf[i] = revf[i + 1] * (i + 1) % mod;
    }
}

ll C(int n, int m) {
    return (f[n] * revf[m] % mod) * revf[n - m] % mod;
}

int l[N], r[N];
map<ll, int> mp;

typedef long long ll;
int n;


ll f1(int L, int R) {
    if (L >= R) return 1;
    int i = mp[ L * 1ll * (n + 10) + R ];
    assert(L <= i && i <= R);
    return (f1(L, i - 1) * f1(i + 1, R) % mod) * C(R - L, R - i) % mod;
}

typedef pair<int, int> pii;
bool vis[N];

#define MP make_pair
#define F first
#define S second

ll ans[N];

int Q(int L, int R) {
    //assert(mp.find(L * 1ll * (n + 10) + R) != mp.end());
    return mp[ L * 1ll * (n + 10) + R ];
}

ll stackf1(int L, int R) {
    if (L >= R) return 1;
    stack<pii> sta;
    sta.push(MP(L, R));
    while (!sta.empty()) {
        pii p = sta.top();
        int L = p.F, R = p.S;
        int i = mp[ L * 1ll * (n + 10) + R ];
        if (vis[i]) {
            ans[i] = C(R - L, R - i);
            if (L <= i - 1) ans[i] *= ans[ Q(L, i - 1) ];
            ans[i] %= mod;
            if (i + 1 <= R) ans[i] *= ans[ Q(i + 1, R) ];
            ans[i] %= mod;
            sta.pop();
        }
        else {
            vis[i] = true;
            if (L <= i - 1) sta.push(make_pair(L, i - 1));
            if (i + 1 <= R) sta.push(make_pair(i + 1, R));
        }
    }
    return ans[Q(L, R)];
}

int main () {
    build();
    int cases = 0;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &l[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &r[i]);
        }
        printf("Case #%d: ", ++cases);
        set<int> st;
        vector<int> v;
        for (int i = 1; i <= n; ++i) {
            st.insert(i);
            v.push_back(i);
        }
        sort(v.begin(), v.end(), [](const int &a, const int &b) {
            return r[a] - l[a] < r[b] - l[b]; 
        });
        ll ans = 1;
        for (int i: v) {
            auto iter = st.lower_bound(l[i]);
            if (iter != st.end() && (*iter) <= r[i]) {
                ++iter;
                if (iter == st.end() || (*iter) > r[i]) {
                    --iter;
                    st.erase(iter);
                }
                else {
                    ans = 0;
                }
            }
            else {
                ans = 0;
            }
        }
        if (ans == 1) {
            for (int i = 1; i <= n; ++i) {
                ans *= (C(r[i] - l[i], r[i] - i));
                ans %= mod;
            }
        }
        printf("%lld\n", ans);
    }
}

