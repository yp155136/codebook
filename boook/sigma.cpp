//problem->for(int i = 1 ; i <= n ; i ++) ans += pow(i , k);
#define int long long
#define MAX 2020
#define INF 0x3f3f3f3f
#define mod 1000000007LL
 
int b[MAX] , c[MAX][MAX] , ni[MAX];
int ppow(int a , int k){
    if(k == 0) return 1;
    if(k % 2 == 0) return ppow(a * a % mod , k >> 1);
    if(k % 2 == 1) return ppow(a * a % mod , k >> 1) * a % mod;
}
void solveinit(){
    REP(i , 0 , MAX){
        REP(j , 0 , i + 1){
            if(j == 0 || j == i) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    REP(i , 1 , MAX) ni[i] = ppow(i , mod - 2);
    b[0] = 1;
    REP(i , 1 , MAX){
        REP(j , 0 , i) b[i] = (b[i] + c[i + 1][j] * b[j]) % mod;
        b[i] = b[i] * ni[i + 1] % mod;
        b[i] = mod - b[i];
    }
}
int t , n , k;
int32_t main(){
    solveinit();
    cin >> t;
    REP(times , 0 , t){
        cin >> n >> k;
        n %= mod;
        int ans = 0 , np = 1;
        REP(i , 1 , k + 2){
            np = np * (n + 1) % mod;
            ans = (ans + c[k + 1][i] * np % mod * b[k + 1 - i] % mod) % mod;
        }
        ans = (ans * ni[k + 1]) % mod;
        cout << ans << endl;
    }
    return 0;
}
