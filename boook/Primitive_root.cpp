#define int int_fast64_t
int n;
int ppow(int a , int k , int mod){
    if(k == 0) return 1;
    if(k % 2 == 0) return ppow(a * a % mod , k >> 1 , mod);
    if(k % 2 == 1) return ppow(a * a % mod , k >> 1 , mod) * a % mod;
}
int32_t main(){
    IOS;
    while(cin >> n){
        if(n == 2){
            cout << 1 << endl;
            continue;
        }
        vector<int> sol;
        int val = n - 1;
        REP(i , 2 , INF){
            if(i * i > val) break;
            else if(val % i == 0){
                sol.pb(i);
                while(val % i == 0) val /= i;
            }
        }
        if(val != 1) sol.pb(val);
        int ans;
        REP(i , 2 , INF){
            int ok = 1;
            for(auto to : sol){
                if(ppow(i , (n - 1) / to , n) == 1){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                ans = i;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
