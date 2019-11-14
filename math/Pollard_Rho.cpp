//const int G = (1LL<<31)-1;
LL mull(LL a,LL b,LL mod) {
    //if (a<G && b<G) return a*b%mod;
    LL ret = 0, now = a;
    while (b) {
        if (b&1) ret = addd(ret, now, mod);
        now = addd(now, now, mod);
        b >>= 1;
    }
    return ret;
}
LL ppow(LL a,LL n,LL mod) {
    LL ret = 1, now = a;
    while (n) {
        if (n&1) ret = mull(ret, now, mod);
        now = mull(now, now, mod);
        n >>= 1;
    }
    return ret;
}
bool miller_robin(LL n,LL a) {
    if (__gcd(a,n) == n) return PRIME;
    if (__gcd(a,n) != 1) return COMPOSITE;
    LL d=n-1,r=0,ret;
    while (d%2==0) {
        r++;
        d/=2;
    }
    ret = pow(a,d,n);
    if (ret==1 ||ret==n-1) return PRIME;
    while (r--) {
        ret = mul(ret,ret,n);
        if (ret==n-1) return PRIME;
    }
    return COMPOSITE;
}
bool isPrime(LL n) {
    LL as[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int i = 0; 7 > i; ++i) {
        if (miller_rabin(n, as[i]) == COMPOSITE) return COMPOSITE;
    }
    return PRIME;
}
LL a, c;

LL doo(LL x, LL n) {
    return addd( mull( a, mull(x, x, n), n ), c, n);
}

LL solve(LL n) {
    if (isPrime(n)) return n;
    if (!(n & 1)) return 2;
    a = myRnd() % n;
    if (!a) a=1;
    c = myRnd() % n;
    while (c == 0 || c == 2) c = myRnd()%n;
    LL start = myRnd()%n;
    LL s1 = doo(start, n);
    LL s2 = doo(s1, n);
    while (true) {
        if (s1 == s2) {
            start = myRnd() % n;
            //a=myRnd()+1;
            a = Rnd() % n; if (!a) a = 1;
            c = Rnd() % n; while (c == 0 || c == 2) c = myRnd() % n;
            s1 = doo(start, n), s2 = doo(s1, n);
            continue;
        }
        LL _ = gcd(abs(s1 - s2), n);
        if (_ != 1) {
            return min(solve(_), solve(n / _));
        }
        s1 = doo(s1, n); s2 = doo(s2, n); s2 = doo(s2, n);
    }
}
