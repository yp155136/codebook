#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000007;
const int N = 800006;
//const int K = (int)sqrt(2 * N) + 3; //sqrt(N), sqrt(2N)
typedef pair<ll,ll> pll;

int a[N];
int b[N];

ll dp1[N]; // i < K
ll dp2[N]; // i >= K

ll pre[N];

ll Q(int L, int R) {
    if (L <= 0) return pre[R];
    return (pre[R] - pre[L - 1] + mod) % mod;
}

/*#include <bits/stdc++.h>
using namespace std;
*/
//FFT

const int MAXN = 262144 * 2;
typedef long double ld;
#define ld double
typedef complex<ld> cplx;
const ld pi = acos(-1);
const cplx I(0, 1);
cplx omega[MAXN + 1];
void pre_fft() {
    for (int i = 0; i <= MAXN; ++i) {
        omega[i] = exp(i * 2 * pi / MAXN * I);
    }
}

void fft(int n, cplx a[], bool inv = false) {
    int basic = MAXN/n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; ++i) {
            cplx w = omega[inv? MAXN - (i * theta % MAXN) : i * theta%MAXN];
            for (int j = i; j < n; j += m) {
                int k = j + mh;
                cplx x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
        theta = (theta * 2) % MAXN;
    }
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1) ;
        if (j < i) swap(a[i], a[j]);
    }
    if (inv) {
        for (int i = 0; i < n; ++i) a[i] /= n;
    }
}

cplx d[MAXN], e[MAXN], f[MAXN];

int main () {
    int n, m;
    int cases = 0;
    pre_fft();
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &b[i]);
        }
        for (int i = 0; i <= 2 * n; ++i) {
            dp1[i] = 0;
            dp2[i] = 0;
        }
        int K = sqrt(2 * n) + 3;
        dp2[0] = 1;
        pre[0] = 1;
        for (int i = 1; i < K; ++i) {
            pre[i] = 1;
        }
        for (int i = K; i <= n; ++i) {
            dp2[i] = Q(i - n, i - K);
            pre[i] = (pre[i - 1] + dp2[i]) % mod;
        }
        dp1[0] = 1;
        for (int i = 1; i < K; ++i) {
            if (!a[i]) continue;
            for (int j = 0; j < i; ++ j) {
                deque<pll> qu;
                ll sum = 0;
                for(int k = j ; k <= 2 * n; k += i ) {
                    while(qu.size() &&  
                        (k - (qu.front().second))/i > a[i] ){
                            sum -= qu.front().first;
                            qu.pop_front();
                        }
                    ll tmp1 = dp1[k];
                    ll tmp2 = k;
                    dp1[k] += sum%mod + mod;
                    dp1[k] %= mod;
                    qu.push_back(pll(tmp1, tmp2));
                    sum += tmp1;
                    sum %= mod;
                }
            }
        }
        int nn = 2 * n;
        nn = (1<<(__lg(nn)+1));
        nn *= 2;
        for (int i = 0 ; i < nn; ++i) {
            d[i] = cplx(dp1[i]%mod, 0);
        }
        for (int i = 0 ; i < nn; ++i) {
            e[i] = cplx(dp2[i], 0);
        }
        fft(nn, d);
        fft(nn, e);
        for (int i = 0; i < nn; ++i) {
            f[i] = d[i] * e[i];
        }
        for (int i = 0; i < nn; ++i) {
            dp1[i] = dp2[i] = 0;
        }
        fft(nn, f, 1);
        printf("Case #%d: ",++cases);
        ll ans = 0;
        for (int i = 1; i <= m; ++i) {
            ans += fmod(f[ 2*n - b[i] ].real() + 1e-9, mod);
            ans %= mod;
        }
        printf("%lld\n", ans);
    }
}

