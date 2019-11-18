int siz[MAX] , son[MAX] , dep[MAX] , ffa[MAX];
int top[MAX] , idx[MAX] , idpo = 0;
int n , m;
int e[MAX][3];
vector<int> v[MAX];
struct node{ int big , sml; } st[MAX * 4];
void init(){
    REP(i , 0 , MAX) v[i].clear();
    MEM(siz , 0) , MEM(son , 0) , MEM(dep , 0) , MEM(ffa , 0);
    MEM(top , 0) , MEM(idx , 0) , idpo = 0;
}
void DFS1(int now , int fa , int deep){
    siz[now] = 1;
    dep[now] = deep;
    ffa[now] = fa;
    int big = 0;
    REP(i , 0 , v[now].size()){
        int to = v[now][i];
        if(to != fa){
            DFS1(to , now , deep + 1);
            siz[now] += siz[to];
            if(siz[to] > big) big = siz[to] , son[now] = to;
        }
    }
}
void DFS2(int now , int fa , int root){
    top[now] = root;
    idx[now] = ++idpo;
    if(son[now] != 0) DFS2(son[now] , now , root);
    REP(i , 0 , v[now].size()){
        int to = v[now][i];
        if(to != fa && to != son[now]) DFS2(to , now , to);
    }
}
void solveinit(){
    DFS1(1 , 0 , 0);
    DFS2(1 , 0 , 1);
    REP(i , 2 , n + 1){
        int a = e[i][0] , b = e[i][1] , c = e[i][2];
        if(dep[a] < dep[b]) swap(a , b);
        update(1 , 1 , n , idx[a] , c);
    }
}
void query(int a , int b){
    node ans;
    ans.big = -INF , ans.sml = INF;
    int t1 = top[a] , t2 = top[b];
    while(t1 != t2){
        if(dep[t1] < dep[t2]) swap(t1 , t2) , swap(a , b);
        ans = pull(ans , query(1 , 1 , n , idx[t1] , idx[a]));
        a = ffa[t1] , t1 = top[a];
    }
    if(dep[a] > dep[b]) swap(a , b);
    if(a != b) ans = pull(ans , query(1 , 1 , n , idx[son[a]] , idx[b]));
    return cout << ans.sml << " " << ans.big << endl , void();
}
init();
REP(i , 2 , n + 1){
    int a , b , c; cin >> a >> b >> c;
    e[i][0] = a , e[i][1] = b , e[i][2] = c;
    v[a].pb(b); v[b].pb(a);
}
solveinit();
query(a , b);
