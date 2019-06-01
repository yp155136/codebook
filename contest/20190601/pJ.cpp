//input T
// n --> n numbers
// answer = a[1]*3 + max(a[i],1)
// answer = odd: answer++

#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int a[N];

int main () {
    int T;
    scanf("%d",&T);
    while (T--) {
        int n; scanf("%d",&n);
        for (int i=1;i<=n;++i) {
            scanf("%d",&a[i]);
            if (i == 1) a[i] *= 3;
            else a[i]++;
        }
        int ans = *max_element(a+1,a+n+1);
        if (ans %2 == 1) ++ans;
        printf("%d\n",ans);
    }
}
