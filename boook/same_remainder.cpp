#define INF 0x3f3f3f3f
void extgcd(ll a , ll b , ll &d , ll &x , ll &y){
    if(b == 0) d = a , x = 1 , y = 0;
    else extgcd(b , a % b , d , y , x) , y -= (a / b) * x;
}
ll n;
vector<ll> v , m;
int main(){
    while(cin >> n){
        v.clear() , m.clear();
        ll ans , mod , d , x , y;
        REP(i , 0 , n) cin >> mod >> ans , m.pb(mod) , v.pb(ans);
        mod = m[0] , ans = v[0];
        REP(i , 1 , n){
            ll res = ((v[i] - ans) % m[i] + m[i]) % m[i];
            extgcd(mod , m[i] , d , x , y);
            if(res % d != 0){ ans = -1; break; }

            res = (res / d * x % m[i] + m[i]) % m[i];
            ans = ans + res * mod;
            mod = mod * m[i] / d;
        }
        if(ans == -1) cout << ans << endl;
        else cout << ans % mod << endl;
    }
    return 0;
}
