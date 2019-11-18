int n , x[MAX] , ans = 0;
vector<int> v;
int DFS(int now){
    int val = v[now] + v[now + 1];
    ans += val;
    v.erase(v.begin() + now);
    v.erase(v.begin() + now);
    int id = 0;
    RREP(i , now - 1 , 0) if(v[i] >= val) { id = i + 1; break; }
    v.insert(v.begin() + id , val);
    while(id >= 2 && v[id - 2] <= v[id]){
        int dis = v.size() - id;
        DFS(id - 2);
        id = v.size() - dis;
    }
}
int32_t main(){
    IOS;
    cin >> n;
    REP(i , 0 , n) cin >> x[i];
    REP(i , 0 , n){
        v.pb(x[i]);
        while(v.size() >= 3 && v[v.size() - 3] <= v[v.size() - 1]) 
            DFS(v.size() - 3);
    }
    while(v.size() > 1) DFS(v.size() - 2);
    cout << ans << endl;
    return 0;
}
