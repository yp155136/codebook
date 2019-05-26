#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main () {
    int T; cin >> T;
    while (T--) {
        ll a,b,c;
        cin >> a >> b >> c;
        cout << max(0ll,(a-b)*c) << endl;
    }
}

