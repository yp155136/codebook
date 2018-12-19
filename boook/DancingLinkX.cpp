#define MAX 1050
#define INF 0x3f3f3f3f
struct DLX{
    int n , sz , s[MAX];
    int row[MAX * 100] , col[MAX * 100];
    int l[MAX * 100] , r[MAX * 100] , u[MAX * 100] , d[MAX * 100];
    int ans;
    void init(int n){
        this -> n = n;
        ans = INF;
        REP(i , 0 , n + 1){
            u[i] = d[i] = i;
            l[i] = i - 1;
            r[i] = i + 1;
        }
        r[n] = 0 , l[0] = n;
        sz = n + 1;
        MEM(s , 0);
    }
    void AddRow(int rr , vector<int> sol){
        int tmp = sz;
        for(auto to : sol){
            l[sz] = sz - 1;
            r[sz] = sz + 1;
            d[sz] = to;
            u[sz] = u[to];
            d[u[to]] = sz , u[to] = sz;
            row[sz] = rr , col[sz] = to;
            s[to] ++ , sz ++;
        }
        r[sz - 1] = tmp , l[tmp] = sz - 1;
    }
#define FOR(i , way , to) for(int i = way[to] ; i != to ; i = way[i])
    void remove(int c){
        l[r[c]] = l[c];
        r[l[c]] = r[c];
        FOR(i , d , c) FOR(j , r , i){
            u[d[j]] = u[j];
            d[u[j]] = d[j];
            --s[col[j]];
        }
    }
    int restore(int c){
        FOR(i , u , c) FOR(j , l , i){
            ++s[col[j]];
            u[d[j]] = j;
            d[u[j]] = j;
        }
        l[r[c]] = c;
        r[l[c]] = c;
    }
    void DFS(int floor){
        if(r[0] == 0){
            ans = min(ans , floor);
            return;
        }
        if(floor >= ans) return;
        int c = r[0];
        FOR(i , r , 0) if(s[i] < s[c]) c = i;
        remove(c);
        FOR(i , d , c){
            FOR(j , r , i) remove(col[j]);
            DFS(floor + 1);
            FOR(j , l , i) restore(col[j]);
        }
        restore(c);
    }
} solver;
int n , m;
int32_t main(){
    IOS;
    while(cin >> n >> m){
        solver.init(m);
        REP(i , 0 , n){
            int nn , in;
            cin >> nn;
            vector<int> sol;
            REP(j , 0 , nn) cin >> in , sol.pb(in);
            solver.AddRow(i , sol);
        }
        solver.DFS(0);
        if(solver.ans == INF) cout << "No" << endl;
        else cout << solver.ans << endl;
    }
    return 0;
}
