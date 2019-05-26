#include <bits/stdc++.h>
using namespace std;

typedef bitset<22> bst;
const int N = 21;

bst b[N];

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n,m; scanf("%d%d",&n,&m);
        for (int i=0;i<=n;++i) {
            b[i].reset();
        }
        for (int i=1;i<=m;++i) {
            int x,y; scanf("%d%d",&x,&y);
            --x; --y;
            b[x][y] = true;
        }
        int ans = 0;
        for (int i=1;i<(1<<n);++i) {
            bst tmp;
            tmp.reset();
            tmp = ~tmp;
            for (int i=n;i<N;++i) tmp[i] = false;
            int ret=0;
            for (int j=0;j<n;++j) {
                if ((1<<j)&i) {
                    tmp &= b[j];
                    ++ret;
                }
            }
            ret += tmp.count();
            ans = max(ans,ret);
        }
        printf("%d\n",ans);
    }
}

