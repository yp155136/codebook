#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100006;
const ll mod = 1000000007;

int a[N], b[N];
bool visa[N], visb[N];

ll cnt[N];
ll cnt3[N];

int main () {
    int n, m;
    int cases = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            visa[i] = false;
            cnt[i] = cnt[i + 1] = 0;
            cnt3[i] = cnt3[i + 1] = 0;
        }
        for (int j = 0; j < m; ++j) {
            scanf("%d", &b[j]);
            visb[j] = false;
        }
        vector<int> sza, szb;
        for (int i = 0; i < n; ++i) {
            if (visa[i]) continue;
            int cnt = 0;
            int now = i;
            while (!visa[now]) {
                visa[now] = true;
                ++cnt;
                now = a[now];
            }
            sza.push_back(cnt);
        }
        for (int i = 0; i < m; ++i) {
            if (visb[i]) continue;
            int cnt2 = 0;
            int now = i;
            while (!visb[now]) {
                visb[now] = true;
                ++cnt2;
                now = b[now];
            }
            cnt[ cnt2 ] += cnt2;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; j += i) {
                cnt3[j] += cnt[i];
            }
        }
        ll ans = 1;
        for (int i: sza) {
            ans *= cnt3[i];
            ans %= mod;
        }
        printf("Case #%d: %lld\n", ++cases, ans);
    }
}

