#define MAX 50900
#define mod 1000000007LL
int n , dp[MAX];
int32_t main(){
    dp[0] = 1;
    REP(i , 1 , MAX){
        REP(j , 1 , MAX){
            int tmp = j * (j * 3 - 1) / 2;
            if(tmp > i) break;
            else if(j % 2 == 1) dp[i] = (dp[i] + dp[i - tmp]) % mod;
            else if(j % 2 == 0) dp[i] = (dp[i] - dp[i - tmp] + mod) % mod;
        }
        REP(j , 1 , MAX){
            int tmp = j * (j * 3 + 1) / 2;
            if(tmp > i) break;
            else if(j % 2 == 1) dp[i] = (dp[i] + dp[i - tmp]) % mod;
            else if(j % 2 == 0) dp[i] = (dp[i] - dp[i - tmp] + mod) % mod;
        }
    }
    cin >> n;
    cout << dp[n] << endl;
    return 0;
}
