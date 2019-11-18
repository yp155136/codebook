ll a, c;
ll doo(ll x, ll n) {
    return addd( mull( a, mull(x, x, n), n ), c, n);
}
ll solve(ll n) {
    if (isPrime(n)) return n;
    if (!(n & 1)) return 2;
    a = myRnd() % n; if (!a) a=1;
    c = myRnd() % n;
    while (c == 0 || c == 2) c = myRnd()%n;
    ll start = myRnd()%n;
    ll s1 = doo(start, n), s2 = doo(s1, n);
    while (true) {
        if (s1 == s2) {
            start = myRnd() % n;
            //a=myRnd()+1;
            a = Rnd() % n; if (!a) a = 1;
            c = Rnd() % n; while (c == 0 || c == 2) c = myRnd() % n;
            s1 = doo(start, n), s2 = doo(s1, n);
            continue;
        }
        ll _ = gcd(abs(s1 - s2), n);
        if (_ != 1) {
            return min(solve(_), solve(n / _));
        }
        s1 = doo(s1, n); s2 = doo(s2, n); s2 = doo(s2, n);
    }
}
