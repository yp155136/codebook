string s;
const int N = 4000006;
int f[N];
void solve() {
    s = s + s;
    int n = (int)s.size();
    for (int i=0;i<n;++i) f[i] = -1;
    int k=0;
    for (int j=1;j<n;++j) {
        char sj = s[j];
        int i = f[j-k-1];
        while (i != -1 && sj != s[k+i+1]) {
            if (sj < s[k+i+1]) {
                k = j-i-1;
            }
            i = f[i];
        }
        if (sj != s[k+i+1]) {
            if (sj < s[k]) {
                k = j;
            }
            f[j-k] = -1;
        }
        else f[j-k] = i+1;
    }
    n>>=1;
    if (k >= n) k-= n;
    for (int i=k;i<k+n;++i) {
        cout << s[i];
    }
    cout << endl;
}




