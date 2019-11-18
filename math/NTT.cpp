// Remember coefficient are mod P
/*
(mod,root)
(65537,3)
(23068673,3)
(998244353,3) 
(1107296257,10)
(2013265921,31)
(2885681153,3) 
*/
typedef long long ll;
const int maxn = 65536;

struct NTT{
    ll mod = 2013265921, root = 31;
    ll omega[maxn+1];
    void prentt() {
        ll x=fpow(root,(mod-1)/maxn);
        omega[0] = 1;
        for (int i=1;i<=maxn;++i) {
            omega[i] = omega[i-1] * x % mod;
        }
    }
    void real_init(ll _mod,ll _root) {
        mod = _mod;
        root = _root;
        prentt();
    }
    ll fpow(ll a,ll n) {
        (n += mod-1) %= mod - 1;
        ll r = 1;
        for (; n; n>>=1) {
            if (n&1) (r*=a)%=mod;
            (a*=a)%=mod;
        }
        return r;
    }
    void bitrev(vector<ll> &v,int n) {
        int z = __builtin_ctz(n)-1;
        for (int i=0;i<n;++i) {
            int x=0;
            for (int j=0;j<=z;++j) x ^= ((i>>j&1) << (z-j));
            if (x>i) swap(v[x],v[i]);
        }
    }
    void ntt(vector<ll> &v,int n) {
        bitrev(v,n);
        for (int s=2;s<=n;s<<=1) {
            int z = s>>1;
            for (int i=0;i<n;i+=s) {
                for (int k=0;k<z;++k) {
                    ll x = v[i+k+z] * omega[maxn/s * k] % mod;
                    v[i+k+z] = (v[i+k] + mod - x)%mod;
                    (v[i+k] += x) %= mod;
                }
            }
        }
    }
    void intt(vector<ll> &v,int n) {
        ntt(v,n);
        reverse(v.begin()+1,v.end());
        ll inv = fpow(n,mod-2);
        for (int i=0;i<n;++i) {
            (v[i] *= inv) %= mod;
        }
    }
    vector<ll> conv(vector<ll> a,vector<ll> b) {
        int sz=1;
        while (sz < a.size() + b.size() - 1) sz <<= 1;
        vector<ll> c(sz);
        while (a.size() < sz) a.push_back(0);
        while (b.size() < sz) b.push_back(0);
        ntt(a,sz), ntt(b,sz);
        for (int i=0;i<sz;++i) c[i] = (a[i] * b[i]) % mod;
        intt(c,sz);
        while (c.size() && c.back() == 0) c.pop_back();
        return c;
    }
};
ll chinese(ll b1, ll m1, ll b2, ll m2) {
    ll a1 = bigpow(m2,m1-2,m1)*b1 % m1;
    ll a2 = bigpow(m1,m2-2,m2)*b2 % m2;
    ll ret= (a1*m2 + a2*m1)%(m1*m2);
    assert(ret%m1 == b1 && ret%m2 == b2);
    return ret;
}
