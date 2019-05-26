#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 56;
const ll mod = 1000000007;
ll dp[N][N];

int pre[N];
string s;

int Sum(int L,int R) {
    int ret=0;
    for (int i=L;i<R;++i) ret += (s[i] == '1');
    return ret;
}

int sum[N][N];

ll DP(int L,int R) {
    if (dp[L][R] != -1) return dp[L][R];
    if (L == R) return 1;
    if (L+1 == R) return 1;
    ll ret = 0;
    for (int l=L+1;l<=R;++l) {
        for (int r=l;r<R;++r) {
            //if (l == L && r == R) continue;
            if (sum[L][l] == sum[r][R]) {
                ret += DP(l,r);
                ret %= mod;
            }
        }
    }
    ++ret;
    dp[L][R] =ret;
    return ret;
}

int main () {
    int T; cin >> T;
    while (T--) {
        cin >> s;
        int n = (int)s.size();
        for (int i=0;i<n;++i) {
            for (int j=i;j<=n;++j) {
                sum[i][j] = Sum(i,j);
            }
        }
        memset(dp,-1,sizeof(dp));
        ll ans = DP(0,n);
        cout << (ans%mod+mod)%mod << endl;
    }
}

