#define MAX 100000
#define INF 0x3f3f3f3f
#define mod 10000
int n , k , x[MAX] , c[MAX];
vector<int> mul(vector<int> a , vector<int> b){
    vector<int> ans(n + n + 1);
    REP(i , 1 , n + 1) REP(j , 1 , n + 1)
        ans[i + j] = (ans[i + j] + (a[i] * b[j])) % mod;
    RREP(i , n + n , n + 1){
        REP(j , 1 , n + 1) ans[i - j] = (ans[i - j] + ans[i] * c[j]) % mod;
        ans[i] = 0;
    }
    return ans;
}
vector<int> ppow(vector<int> a , int k){
    if(k == 1) return a;
    if(k % 2 == 0) return     ppow(mul(a , a) , k >> 1);
    if(k % 2 == 1) return mul(ppow(mul(a , a) , k >> 1) , a);
}
int main(){
    IOS;
    while(cin >> n && n){
        REP(i , 1 , n + 1) cin >> x[i];
        REP(i , 1 , n + 1) cin >> c[i];
        vector<int> v(n + n + 1);
        v[1] = 1;
        cin >> k , k ++;
        v = ppow(v , k);
        int ans = 0;
        REP(i , 1 , n + 1) ans = (ans + x[i] * v[i]) % mod;
        cout << ans << endl;
    }
    return 0;
}
