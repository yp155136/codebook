#include <bits/stdc++.h>
using namespace std;

const int N = 100006;
string s[N];

bool cmp(int x,int y) {
    return s[x] < s[y];
}

int a[N];
int b[N];

struct BIT {
    int a[N];
    int n;
    void init(int _n) {
        n = _n + 2;
        for (int i=0;i<=n;++i) {
            a[i] = 0;
        }
    }
    void update(int pos,int val) {
        for (int i=pos;i<n;i+=i&(-i)) {
            a[i] = max(a[i],val);
        }
    }
    int query(int pos) {
        if (pos == 0) return 0;
        int ret = 0;
        for (int i=pos;i>0;i-=i&(-i)) {
            ret = max(ret,a[i]);
        }
        return ret;
    }
} bitx,bity;

int c[N];

bool has_m(int id) {
    for (char i:s[id]) {
        if (i == 'm') return true;
    }
    return false;
}

int aa[N];
int bb[N];

bool hass_m[N];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i=1;i<=n;++i) {
            cin >> s[i];
            a[i] = i;
            b[i] = i;
            c[i] = i;
        }
        sort(a+1,a+n+1,cmp);
        for (int i=1;i<=n;++i) {
            reverse(s[i].begin(),s[i].end());
        }
        sort(b+1,b+n+1,cmp);
        bitx.init(n);
        bity.init(n);
        int ans = 0;
        vector<pair<int,int> > v;
        for (int i=1;i<=n;++i) {
            aa[ a[i] ] = i;
            bb[ b[i] ] = i;
        }
        for (int i=1;i<=n;++i) {
            v.push_back(make_pair(aa[i],bb[i]+(has_m(i)?N:0)));
        }
        sort(v.begin(),v.end());
        for (int i=1;i<=n;++i) {
            if (v[i-1].second >= N) {
                c[i] = v[i-1].second - N;
                hass_m[i] = true;
            }
            else {
                c[i] = v[i-1].second;
                hass_m[i] = false;
            }
            //c[i] = v[i-1].second;
        }
        for (int i=1;i<=n;++i) {
            if (hass_m[i]) {
                ans = max(ans,bity.query(c[i]-1)+1);
                bitx.update(c[i],bity.query(c[i]-1)+1);
            }
            else {
                ans = max(ans,bitx.query(c[i]-1)+1);
                bity.update(c[i],bitx.query(c[i]-1)+1);
            }
        }
        cout << ans << endl;
    }
}

