#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

int n, p, q, m;
uint sa, sb, sc;
uint rng61() {
    sa ^= sa << 16;
    sa ^= sa >> 5;
    sa ^= sa << 1;
    uint t = sa;
    sa = sb;
    sb = sc;
    sc ^= t ^ sa;
    return sc;
}

typedef pair<int, int> pii;
#define F first
#define S second
int sz;


stack<pii> sta;

void PUSH(int x) {
    ++sz;
    if (!sta.empty() && sta.top().F > x) return;
    sta.push(make_pair(x, sz));
}

void POP() {
    if (!sta.empty() && sta.top().S == sz) sta.pop();
    --sz;
}

int MAX() {
    if (sta.empty()) return 0;
    return sta.top().F;
}

int main () {
    int T; scanf("%d", &T);
    int cases = 0;
    while (T--) {
        while (!sta.empty()) sta.pop();
        sz = 0;
        scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &sa, &sb, &sc);
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (rng61() % (p + q) < p) {
                PUSH(rng61() % m + 1);
            }
            else {
                POP();
            }
            ans ^= (i * 1ll * MAX());
        }
        printf("Case #%d: %lld\n", ++cases, ans);
    }
}

