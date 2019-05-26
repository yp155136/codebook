#include <bits/stdc++.h>
using namespace std;

int main () {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int tot=n;
        for (int i=1;i<n;++i) {
            int x; cin >> x;
            tot ^= i;
            tot ^= x;
        }
        cout << tot << endl;
    }
}

