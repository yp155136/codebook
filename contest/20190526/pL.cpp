#include <bits/stdc++.h>
using namespace std;

const int N = 506;
const int INF = (1<<20);
int n;
int a[N][N];
int b[N];

int L[N],R[N];

long long solve() {
    long long ret=0;
    for (int x=1;x<=n;++x) {
        for (int i=1;i<=n;++i) {
            b[i] = a[x][i];
        }
        for (int y=x;y<=n;++y) {
            for (int i=1;i<=n;++i) {
                b[i] = max(b[i],a[y][i]);
            }
            stack<int> sta;
            b[0] = b[n+1] = INF;
            for (int i=1;i<=n+1;++i) {
                while (!sta.empty() && b[sta.top()] <= b[i]) {
                    int x = sta.top();
                    sta.pop();
                    R[x] = i-1;
                }
                sta.push(i);
            }
            while (!sta.empty()) sta.pop();
            for (int i=n;i>=0;--i) {
                while (!sta.empty() && b[sta.top()] < b[i]) {
                    int x = sta.top();
                    sta.pop();
                    L[x] = i+1;
                }
                sta.push(i);
            }
            for (int i=1;i<=n;++i) {
                ret += (i-L[i]+1)*(R[i]-i+1)*b[i];
            }
        }
    }
    return ret;
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                scanf("%d",&a[i][j]);
            }
        }
        long long ans = solve();
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                a[i][j] = -a[i][j];
            }
        }
        ans += solve();
        printf("%lld\n",ans);
    }
}

