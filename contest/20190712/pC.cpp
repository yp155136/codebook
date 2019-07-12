#include <bits/stdc++.h>
using namespace std;

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int cases = 0;
    int T; cin >> T;
    while (T--) {
        int a, b; cin >> a >> b;
        string s, t; cin >> s >> t;
        int c = t[0] - s[0];
        string r; cin >> r;
        for (char &i: r) {
            i -= 'A';
            i -= c;
            i = (i + 26 * 100) % 26;
            i += 'A';
        }
        cout << "Case #" << ++cases << ": " << r << endl;
    }
}

