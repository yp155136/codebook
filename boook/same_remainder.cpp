#define INF 0x3f3f3f3f
void extgcd(long long a , long long b , long long &d , long long &x , long long &y){
    if(b == 0) d = a , x = 1 , y = 0;
    else extgcd(b , a % b , d , y , x) , y -= (a / b) * x;
}
long long n;
vector<long long> v , m;
int main(){
    while(cin >> n){
        v.clear() , m.clear();
        long long ans , mod , d , x , y;
        REP(i , 0 , n) cin >> mod >> ans , m.pb(mod) , v.pb(ans);
        mod = m[0] , ans = v[0];
        REP(i , 1 , n){
            long long res = ((v[i] - ans) % m[i] + m[i]) % m[i];
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
