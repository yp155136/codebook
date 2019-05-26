#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


int main () {
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        priority_queue<int,vector<int>,greater<int> > pq;
        for (int i=0;i<n;++i) {
            int a[3]; cin >> a[0] >> a[1] >> a[2];
            sort(a,a+3);
            pq.push(a[0]);
            pq.push(a[1]);
        }
        ll ans=0;
        while (q--) {
            ans += pq.top();
            pq.pop();
        }
        cout << ans << endl;
    }
}

