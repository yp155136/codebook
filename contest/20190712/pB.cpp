#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld pi = acos(-1);

typedef pair<ld, ld> pii;
#define F first
#define S second

pii operator-(const pii &p1, const pii &p2) {
    return {p1.F - p2.F, p1.S - p2.S};
}

ld operator*(const pii &p1, const pii &p2) {
    return p1.F * p2.F + p1.S * p2.S;
}

ld len(pii p) {
    return sqrt(p * p);
}

pii p[57];

int main () {
    int T; cin >> T;
    int cases = 0;
    while (T--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> p[i].F >> p[i].S;
        }
        pii q; cin >> q.F >> q.S;
        p[n] = p[0];
        p[n+1] = p[1];
        cout << "Case #" << ++cases << ": ";
        ld ans = 0;
        for (int i = 1; i <= n; ++i) {
            ld l = len(q - p[i]);
            ld theta = acos(((p[i] - p[i-1]) * (p[i] - p[i+1])) / len(p[i] - p[i-1]) / len(p[i] - p[i+1]));
            ans += l * (pi - theta);
        }
        cout << fixed << setprecision(3) << ans << endl;
    }
}

