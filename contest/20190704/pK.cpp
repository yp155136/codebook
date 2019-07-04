#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main () {
    ll n, k;
    int cases = 0;
    while (cin >> n >> k) {
        cout << "Case #" << (++cases) << ": ";
        if (k < n) {
            cout << k << endl;
        }
        else {
            --n;
            k -= (n);
            ll x = k % (2 * n);
            if (x == 0) x = 2*n;
            if (x <= n) {
                if (x == 1) {
                    cout << n + 1 << endl;
                }
                else {
                    cout << x - 1 << endl;
                }
            }
            else if (x > n){
                if (x == n + 1) {
                    cout << n << endl;
                }
                else {
                    cout << x - n - 1 << endl;
                }
            }
        }
    }
}
