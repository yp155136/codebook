struct BKB{
    static const int MAX_N = 50;
    typedef bitset<MAX_N> bst;
    bst N[MAX_N];
    int n;
    ll wei[MAX_N], ans, cc;
    BKB(int _n = 0): n(_n), ans(0), cc(0){
        for(int i = 0; i < _n; ++ i)
            N[i].reset();
    }
    void add_edge(int a, int b) {
        N[a][b] = N[b][a] = 1;
    }
    void set_wei(int a, ll w) {
        wei[a] = w;
    }
    ll CNT(bst P) {
        //if vertices have no weight: return P.count();
        ll rt = 0;
        for(int i = P._Find_first(); i < n; i = P._Find_next(i) ) 
            rt += wei[i];
        return rt;
    } 
    void pro(bst P, ll cnt = 0) {
        if (!P.any()){
            if(cnt == ans)
                ++ cc;
            else if(cnt > ans) {
                ans = cnt;
                cc = 1;
            }
            return;
        }
        // "<" can be change to "<=" if we don't need to count
        if ( CNT(P) + cnt < ans) 
            return;
        int u = P._Find_first();
        bst now = P & ~N[u];
        for (int i = now._Find_first(); i < n; i = now._Find_next(i) ) {
            pro(P & N[i], cnt + wei[i]);
            P[i] = 0;
        }
        return;
    }
    pll solve() {
        bst tmp;
        tmp.reset();
        for(int i = 0; i < n; ++ i)
            tmp[i] = 1;
        pro(tmp);
        return pll(ans, cc);
    }
} ss(0);
