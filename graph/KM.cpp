int n , w[MAX][MAX] , lx[MAX] , ly[MAX] , slk[MAX];
int s[MAX] , t[MAX] , good[MAX];
int match(int now){
    s[now] = 1;
    REP(to , 1 , n + 1){
        if(t[to]) continue;
        if(lx[now] + ly[to] == w[now][to]){
            t[to] = 1;
            if(good[to] == 0 || match(good[to]))
                return good[to] = now , 1;
        }
        else slk[to] = min(slk[to] , lx[now] + ly[to] - w[now][to]);
    }
    return 0;
}
int update(){
    int val = INF;
    REP(i , 1 , n + 1) if(t[i] == 0) val = min(val , slk[i]);
    REP(i , 1 , n + 1){
        if(s[i]) lx[i] -= val;
        if(t[i]) ly[i] += val;
    }
}
void solve(){
    REP(i , 1 , n + 1) REP(j , 1 , n + 1)
        lx[i] = max(lx[i] , w[i][j]);
    REP(i , 1 , n + 1){
        MEM(slk , INF);
        while(1){
            MEM(s , 0) , MEM(t , 0);
            if(match(i)) break;
            else update();
        }
    }
}
