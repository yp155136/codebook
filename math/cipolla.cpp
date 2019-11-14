#include <iostream>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define F first
#define S second
 
struct Cipolla
{
    ll p, n, a, w;
    Cipolla(ll _p, ll _n) : p(_p), n(_n){
        n %= p;
        a = -1;
    }
    ll power(ll a, ll x) {
        if(x == 0)  return 1;
        return power(a * a % p, x >> 1) * (x & 1 ? a : 1) % p;
    }
    inline int lgd(ll x) {
        return power(x, (p - 1) / 2);
    }
    ll rnd() {
        return ( ((ll)rand() << 28) + rand());
    }
    pll mul(pll a, pll b) {
        return pll( (a.F * b.F + a.S * b.S % p * w) % p,
                    (a.F * b.S + a.S * b.F) % p );
    }
    pll power(pll ii, ll x) {
        if(x == 0)  return pll(1, 0);
        return mul(power(mul(ii, ii), x >> 1), (x & 1 ? ii : pll(1, 0)));
    }
    ll solve() {
        if(p == 2)
            return n & 1;
        if(lgd(n) == p - 1)    return -1;
        if(n == 0)  return 0;
        while(a = rnd() % p, lgd((a * a  - n + p)% p) == 1);
        w = (a * a - n + p) % p;
        pll ii = power(pll(a, 1), (p + 1) / 2);
        assert(ii.S == 0);
        return ii.F;
    }
};
int main(){
    srand(time(0));
    ll p, n;
    while(cin >> p) {
        cin >> n;
        Cipolla C(p, n);
        cout << C.solve() << '\n';
    }
    return 0;
}
