#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100006;
const ll mod = 1000000007;

string s[N];

vector<int> cnt[26];

bool can[26];

ll ppow[N];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    ppow[0] = 1;
    for (int i = 1; i < N; ++i) {
        ppow[i] = (ppow[i - 1] * 26) % mod;
    }
    int n;
    int cases = 0;
    while (cin >> n) {
        vector<int> v;
        for (int i = 0 ; i < 26; ++i) {
            cnt[i].clear();
            cnt[i].resize(100000);
            v.push_back(i);
        }
        memset(can, 0, sizeof(can));
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            int id = 0;
            for (int j = (int)s[i].size() - 1; j >= 0; --j) {
                cnt[ s[i][j] - 'a' ][id]++;
                ++id;
            }
            can[ s[i][0] - 'a' ] = true;
        }
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 100000 - 1; ++j) {
                cnt[i][j + 1] += cnt[i][j] / 26;
                cnt[i][j] %= 26;
            }
        }
        sort(v.begin(), v.end(), [](const int &a, const int &b) {
            for (int i = 99999; i >= 0; --i) {
                if (cnt[a][i] != cnt[b][i]) return cnt[a][i] > cnt[b][i];
            }
            return a > b;
        });
        int is_0 = -1;
        for (int i = 25; i >= 0; --i) {
            if (!can[ v[i] ]) {
                is_0 = v[i];
                break;
            }
        }
        ll ans = 0;
        int yuuki = 25;
        for (int i: v) {
            if (i == is_0) continue;
            for (int j = 0; j < 100000; ++j) {
                ans += ppow[j] * 1ll * cnt[i][j] * yuuki;
                ans %= mod;
            }
            yuuki--;
        }
        cout << "Case #" << (++cases) << ": " << ans << endl;
    }
}

