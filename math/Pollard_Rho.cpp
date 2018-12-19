//const int G = (1LL<<31)-1;
LL mull(LL a,LL b,LL mod) {
    //if (a<G && b<G) return a*b%mod;
    LL ret = 0;
    LL now = a;
    while (b) {
        if (b&1) ret = addd(ret, now, mod);
        now = addd(now, now, mod);
        b >>= 1;
    }
    return ret;
}
LL ppow(LL a,LL n,LL mod) {
    LL ret = 1;
    LL now = a;
    while (n) {
        if (n&1) ret = mull(ret, now, mod);
        now = mull(now, now, mod);
        n >>= 1;
    }
    return ret;
}
LL gcd(LL a, LL b) {
    if (b==0) return a;
    else return gcd(b, a%b);
}
const bool PRIME = 1, COMPOSITE = 0;
bool miller_rabin(LL n, LL a) {
    if (gcd(n, a) == n) return PRIME;
    else if (gcd(n, a) != 1) return COMPOSITE;
    LL d = n - 1, r = 0;
    while (d % 2 == 0) {
        d >>= 1;
        ++r;
    }
    LL ret = ppow(a, d, n);
    if (ret == 1 || ret == n - 1) return PRIME;
    while (r--) {
        ret = mull(ret, ret, n);
        if (ret == n - 1) return PRIME;
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

const LL C = 2934852462451LL;
const LL D = 126871905557494LL;
LL rnd = 98134513458734897LL;
LL myRnd() {
    return rnd = (rnd + C) ^ D;
}

LL a, c;

LL doo(LL x, LL n) {
    return addd( mull( a, mull(x, x, n), n ), c, n);
}

#define aabs(x) (x) >= 0 ? (x):-(x)

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
            start = myRnd()%n;
            //a=myRnd()+1;
            a = myRnd() % n;
            if (!a) a = 1;
            c = myRnd() % n;
            while (c == 0 || c == 2) c = myRnd() % n;
            s1 = doo(start, n);
            s2 = doo(s1, n);
            continue;
        }
        LL _ = gcd(aabs(s1 - s2), n);
        if (_ != 1) {
            return min(solve(_), solve(n / _));
        }
        s1 = doo(s1, n);
        s2 = doo(s2, n);
        s2 = doo(s2, n);
    }
}
