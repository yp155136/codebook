#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main () {
    int T; cin >> T;
    int cases = 0;
    while (T--) {
        int n, m; cin >> n >> m;
        cout << "Case #" << ++cases << ": ";
        cout << fixed << setprecision(6);
        if (n == 1) cout << 1.0;
        else cout << 0.5;
        cout << ' ';
        if (m == 1) cout << 1.0;
        else cout << (m + 1) * 1.0 / (2 * m);
        cout << endl;
    }
}

