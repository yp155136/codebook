#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 300006;

int a[N];
ll ans = 0;
int vis[N], vis_id = 0;

void dc(int L, int R) {
    if (L == R) {
        ++ans;
        return;
    }
    int mid = (L + R) >> 1;
    dc(L, mid);
    dc(mid + 1, R);
    /*for (int i = L; i <= mid; ++i) {
        for (int j = mid + 1; j <= R; ++j) {
            set<int> st;
            for (int k = i; k <= j; ++k) {
                st.insert(a[k]);
            }
            if ( *(--st.end()) - *st.begin() == (int)st.size() - 1) cout << i << ' ' << j << endl,++ans;
            //if ( *max_element(a + i, a + j + 1) - i == *min_element(a + i, a + j + 1) - j) ++ans;
        } 
    }*/
    ++vis_id;
    int last = -1;
    for (int i = mid + 1; i <= R; ++i) {
        if (vis[ a[i] ] == vis_id) {
            ;;;
        }
    }
}

int main () {
    memset(vis, -1, sizeof(vis));
    int T; scanf("%d", &T);
    int cases = 0;
    while (T--) {
        int n; scanf("%d", &n);
        vector<int> v;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            v.push_back(a[i]);
            v.push_back(a[i] + 1);
            v.push_back(a[i] - 1);
        }
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
        }
        ans = 0;
        dc(1, n);
        printf("Case #%d: %lld\n", ++cases, ans);
    }
}

