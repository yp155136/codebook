#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1006;

ll x[N],y[N],r[N];

struct DJS {
    int p[N];
    void init() {
        for (int i=0;i<N;++i) p[i] = i;
    }
    int Find(int x) {
        return p[x] == x?x:p[x]=Find(p[x]);
    }
    void Union(int x,int y) {
        p[ Find(x) ] = Find(y);
    }
} djs;

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n,w,l; scanf("%d%d%d",&n,&w,&l);
        for (int i=1;i<=n;++i) {
            scanf("%lld%lld%lld",&x[i],&y[i],&r[i]);
        }
        djs.init();
        for (int i=1;i<=n;++i) {
            for (int j=i+1;j<=n;++j) {
                if ((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) <= (r[i]+r[j])*(r[i] + r[j])) {
                    djs.Union(i,j);
                }
            }
        }
        int ans=0;
        for (int i=1;i<=n;++i) {
            if (djs.Find(i) == i) {
                ll L = (1<<30), R = -(1<<30);
                for (int j=1;j<=n;++j) {
                    if (djs.Find(j) == djs.Find(i)) {
                        L = min(L,x[j] - r[j]);
                        R = max(R,x[j] + r[j]);
                    }
                }
                if (L <= 0 && w <= R) ++ans;
            }
        }
        cout << ans << endl;
    }
}

