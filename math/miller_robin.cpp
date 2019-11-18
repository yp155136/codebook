ll mul(ll a,ll b,ll mod) {
    //return a*b%mod;
    //calculate a*b % mod
    ll r=0;
    a%=mod; b%=mod;
    while (b) {
        if (b&1) r=(a+r>=mod?a+r-mod:a+r);
        a=(a+a>=mod?a+a-mod:a+a);
        b>>=1;
    }
    return r;
}
ll pow(ll a,ll n,ll mod) {
    if (n==0) return 1ll;
    else if (n==1) return a%mod;
    return mul( pow(mul(a,a,mod),n/2,mod),n%2?a:1,mod );
}
const bool PRIME = 1, COMPOSITE = 0;
bool miller_robin(ll n,ll a) {
    if (__gcd(a,n) == n) return PRIME;
    if (__gcd(a,n) != 1) return COMPOSITE;
    ll d=n-1,r=0,ret;
    while (d%2==0) {
        r++; d/=2;
    }
    ret = pow(a,d,n);
    if (ret==1 ||ret==n-1) return PRIME;
    while (r--) {
        ret = mul(ret,ret,n);
        if (ret==n-1) return PRIME;
    }
    return COMPOSITE;
}
bool isPrime(ll n) {
    //for int: 2,7,61
    ll as[7] = {2,325,9375,28178,450775,9780504,1795265022};
    for (int i=0;7>i;i++) {
        if (miller_robin(n,as[i]) == COMPOSITE) return COMPOSITE;
    }
    return PRIME;
}
