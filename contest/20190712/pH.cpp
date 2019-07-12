#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100006;

ll h[N], a[N];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    int cases = 0;
    while (T--) {
        int n; cin >> n;
        vector<int> idx;
        for (int i = 0; i < n; ++i) {
            cin >> h[i] >> a[i];
            ll x = sqrt(2 * h[i]);
            while (x * (x + 1) < 2 * h[i]) ++x;
            h[i] = x;
            idx.push_back(i);
        }
        sort(idx.begin(), idx.end(), [](const int &x, const int &y) {
            return h[x] * a[y] < h[y] * a[x];
        });
        ll ans = 0;
        ll pre = 0;
        for (int i: idx) {
            pre += h[i];
            a[i] *= pre;
            ans += a[i];
        }
        cout << "Case #" << ++cases << ": " << ans << endl;
    }
}

