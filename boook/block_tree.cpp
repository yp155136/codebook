//Query on Tree 1, SPOJ
 
int t , n , m , N = 100;
vector<int> v[MAX] , g[MAX];
int pa[MAX] , dep[MAX] , val[MAX];
int siz[MAX] , id[MAX] , mm[MAX];
void init(){
    REP(i , 0 , n + 1) id[i] = 0;
    REP(i , 0 , n + 1) v[i].clear();
    REP(i , 0 , n + 1) g[i].clear();
}
void DFS(int now , int fa , int deep){
    pa[now] = fa , dep[now] = deep;
    if(id[now] == 0) siz[id[now] = now] = 1;
    for(auto to : v[now]){
        if(to == fa) continue;
        if(siz[id[now]] + 1 < N){
            g[now].pb(to);
            siz[id[to] = id[now]] ++;
        }
        DFS(to , now , deep + 1);
    }
}
void build(int now , int v){
    mm[now] = max(v , val[now]);
    for(auto to : g[now]){
        build(to , mm[now]);
    }
}
int query(int a , int b){
    int res = 0;
    while(a != b){
        if(id[a] == id[b]){
            if(dep[a] < dep[b]) swap(a , b);
            res = max(res , val[a]);
            a = pa[a];
        }
        else {
            if(dep[id[a]] < dep[id[b]]) swap(a , b);
            res = max(res , mm[a]);
            a = pa[id[a]];
        }
    }
    return res;
}
int x[MAX][3];
char c[MAX];
int32_t main(){
    scanf("%d" , &t);
    REP(times , 0 , t){
        scanf("%d" , &n);
        init();
        REP(i , 1 , n){
            REP(j , 0 , 3) scanf("%d" , &x[i][j]);
            v[x[i][0]].pb(x[i][1]);
            v[x[i][1]].pb(x[i][0]);
        }
        DFS(1 , 0 , 0);
        REP(i , 1 , n){
            if(dep[x[i][0]] > dep[x[i][1]]) val[x[i][0]] = x[i][2];
            else val[x[i][1]] = x[i][2];
        }
        REP(i , 1 , n + 1){
            if(id[i] == i) build(i , -INF);
        }
        int q , w , tmp;
        while(scanf("%s",c) == 1){
            if(c[0] == 'D') break;
            scanf("%d%d" , &q , &w);
            if(c[0] == 'C'){
                if(dep[x[q][0]] > dep[x[q][1]]) val[x[q][0]] = w , tmp = x[q][0];
                else val[x[q][1]] = w , tmp = x[q][1];
                if(tmp == id[tmp]) build(tmp , -INF);
                else build(tmp , mm[pa[tmp]]);
            }
            else if(c[0] == 'Q'){
                printf("%d\n", query(q , w));
            }
        }
    }
    return 0;
} 
