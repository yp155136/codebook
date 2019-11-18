int n , k , dp[MAX] , ans;
vector<int> v[MAX];
void DFS(int now , int fa){
    if(v[now].size() == 1 && v[now][0] == fa)
        return dp[now] = -1 , void();
    int sml = INF , big = -INF;
    for(auto to : v[now]) if(to != fa){
        DFS(to , now);
        sml = min(sml , dp[to]);
        big = max(big , dp[to]);
    }
    if(sml == -k) dp[now] = k , ans ++;
    else if(big - 1 >= abs(sml)) dp[now] = big - 1;
    else dp[now] = sml - 1;
}
int32_t main(){
    IOS;
    cin >> n >> k;
    REP(i , 2 , n + 1){
        int a , b; cin >> a >> b;
        v[a].pb(b); v[b].pb(a);
    }
    if(k == 0) cout << n << endl;
    else {
        DFS(0 , 0) , ans += dp[0] < 0;
        cout << ans << endl;
    }
    return 0;
}
