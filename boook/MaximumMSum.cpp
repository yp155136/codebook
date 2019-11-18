---------------------Greedy---------------------
int n , m , fr[MAX] , ba[MAX];
int v[MAX] , idx = 1;
set<PII> cc;
void erase(int id){
    if(id == 0) return;
    int f = fr[id] , b = ba[id];
    ba[fr[id]] = b , fr[ba[id]] = f;
    cc.erase(mp(abs(v[id]) , id));
}
int32_t main(){
    cin >> n >> m;
    int sum = 0 , pos = 0 , ans = 0;
    REP(i , 0 , n){
        int tmp; cin >> tmp;
        if(tmp == 0) continue;
        if((tmp >= 0 && sum >= 0) || (tmp <= 0 && sum <= 0)){
            sum += tmp;
        }
        else {
            if(sum > 0) ans += sum , pos ++;
            v[idx ++] = sum , sum = tmp;
        }
    }
    if(sum) v[idx ++] = sum;
    if(sum > 0) ans += sum , pos ++;
    REP(i , 0 , idx){
        fr[i + 1] = i;
        ba[i] = i + 1;
        if(i) cc.insert(mp(abs(v[i]) , i));
    } ba[idx - 1] = 0;
    while(pos > m){
        auto tmp = cc.begin();
        int val = (*tmp).A , id = (*tmp).B;
        cc.erase(tmp);
        if(v[id] < 0 && (fr[id] == 0 || ba[id] == 0)) continue;
        if(v[id] == 0) continue;
        ans -= val , pos --;
        v[id] = v[fr[id]] + v[id] + v[ba[id]];
        cc.insert(mp(abs(v[id]) , id));
        erase(fr[id]) , erase(ba[id]);
    }
    cout << ans << endl;
    return 0;
}
---------------------Aliens---------------------
int n , k , x[MAX];
PII dp[MAX] , rd[MAX]; // max value , times , can be buy , times
int judge(int now){
    dp[1] = mp(0 , 0) , rd[1] = mp(-x[1] , 0);
    REP(i , 2 , n + 1){
        dp[i] = max(dp[i - 1] , mp(rd[i - 1].A + x[i] - now , rd[i - 1].B + 1));
        rd[i] = max(rd[i - 1] , mp(dp[i - 1].A - x[i]       , dp[i - 1].B));
    }
    return dp[n].B;
}
int32_t main(){
    IOS;
    cin >> n >> k;
    n ++;
    REP(i , 2 , n + 2) cin >> x[i];
    REP(i , 1 , n + 1) x[i] += x[i - 1];
    if(judge(0) <= k) cout << dp[n].A << endl;
    else {
        int l = 0 , r = 1000000000000LL;
        while(r - l > 1){
            int mid = l + ((r - l) >> 1) , res = judge(mid);
            if(res == k) return cout << dp[n].A + dp[n].B * mid << endl , 0;
            else if(res < k) r = mid;
            else if(res > k) l = mid;
        }
        judge(l);
        cout << dp[n].A + k * l << endl;
    }
    return 0;
}
