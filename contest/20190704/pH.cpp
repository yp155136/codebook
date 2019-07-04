#include <bits/stdc++.h>
using namespace std;

typedef uint32_t uint;

uint x, y, z, t;
uint rng61() {
    x = x ^ (x << 16);
    x = x ^ (x >> 5);
    x = x ^ (x << 1);
    t = x;
    x = y;
    y = z;
    z = (t ^ x) ^ y;
    return z;
}

const int N = (1 << 16);

vector<uint> v[N + 10];
int pre[N + 10];
bool need[N + 10];

void Q(int b) {
    for (int i = 0; ; ++i) {
        if (b - pre[i] <= 0) {
            need[i] = true;
            return;
            //sort(v[i].begin(), v[i].end());
            //return v[i][ b - 1 ];
        }
        b -= pre[i];
    }
}

uint Q2(int b) {
    for (int i = 0; ; ++i) {
        if (b - pre[i] <= 0) {
            need[i] = true;
            //sort(v[i].begin(), v[i].end());
            return v[i][ b - 1 ];
        }
        b -= pre[i];
    }
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    int cases = 0;
    while (cin >> n >> m >> x >> y >> z) {
        for (int i = 0 ; i < N + 10; ++i) {
            v[i].clear();
        }
        memset(pre, 0, sizeof(pre));
        memset(need, 0, sizeof(need));
        uint xx = x, yy = y, zz = z;
        for (int i = 0; i < n; ++i) {
            uint r = rng61();
            //v[ r/N ].push_back(r);
            pre[ r/N ]++;
        }
        cout << "Case #" << ++cases << ":";
        vector<int> yuuki;
        for (int i = 0; i < m; ++i) {
            int b; cin >> b;
            yuuki.push_back(b);
            Q(b + 1);
            //cout << " " << Q(b + 1);
        }
        x = xx, y = yy, z = zz;
        for (int i = 0; i < n; ++i) {
            uint r = rng61();
            if (need[r / N]) v[r / N].push_back(r);
        }
        for (int i = 0 ; i < N + 10; ++i) {
            if (need[i]) sort(v[i].begin(), v[i].end());
        }
        for (int i: yuuki) {
            cout << " " << Q2(i + 1);
        }
        cout << endl;
    }
}

