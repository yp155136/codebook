#define NXT(x) ((x + 1) % m)
int main () {
    vector<pii> v; // v is the input points
    sort(v.begin(), v.end());
    vector<pii> up, down;
    for (pii p: v) {
        while (SZ(down) >= 2 && sgn((p - down[SZ(down) - 2]) ^ (p - down.back())) >= 0) {
            down.pop_back();
        }
        down.push_back(p);
    }
    reverse(v.begin(), v.end());
    for (pii p: v) {
        while (SZ(up) >= 2 && sgn((p - up[SZ(up) - 2]) ^ (p - up.back())) >= 0) {
            up.pop_back();
        }
        up.push_back(p);
    }
    vector<pii> all;
    for (pii p: down) { all.push_back(p); }  all.pop_back();
    for (pii p: up) { all.push_back(p); }
    all.pop_back();
    int m = all.size();
    int ptr = (int)down.size() - 1;
    for (int i = 0; i < m; ++i) {
        while (((all[NXT(ptr)] - all[ptr]) ^ (all[NXT(i)] - all[i])) > 0) {
            ptr = NXT(ptr);
        }
    }
}
 
