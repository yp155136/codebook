#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define REP(i,j,k)     for(int i = j ; i < k ; ++i)
#define RREP(i,j,k)    for(int i = j ; i >=k ; --i)
#define A    first
#define B    second
#define mp   make_pair
#define pb   push_back
#define PII pair<int , int>
#define MEM(i,j)   memset(i , j , sizeof i)
#define ALL(i)     i.begin() , i.end()
#define DBGG(i,j)     cout << i << " " << j << endl
#define DB4(i,j,k,l)  cout << i << " " << j << " " << k << " " << l << endl
#define IOS cin.tie(0) , cout.sync_with_stdio(0)
#define endl "\n"
///------------------------------------------------------------
#define MAX 100900
#define INF 0x3f3f3f3f
#define ls (now << 1)
#define rs (now << 1 | 1)
#define mid (l + r >> 1)
 
 
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
node pull(node a , node b){ return (node){max(a.big , b.big) , min(a.sml , b.sml)}; }
int update(int now , int l , int r , int k , int val){
    if(l == r) st[now].big = st[now].sml = val;
    else{
        if(k <= mid + 0) update(ls , l , mid + 0 , k , val);
        if(mid + 1 <= k) update(rs , mid + 1 , r , k , val);
        st[now] = pull(st[ls] , st[rs]);
    }
}
node query(int now , int l , int r , int ql , int qr){
    if(ql <= l && r <= qr) return st[now];
    else if(qr <= mid + 0) return query(ls , l , mid + 0 , ql , qr);
    else if(mid + 1 <= ql) return query(rs , mid + 1 , r , ql , qr);
    return pull(query(ls , l , mid + 0 , ql , qr) , query(rs , mid + 1 , r , ql , qr));
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
int32_t main(){
    IOS;
    while(cin >> n){
        init();
        REP(i , 2 , n + 1){
            int a , b , c;
            cin >> a >> b >> c;
            e[i][0] = a , e[i][1] = b , e[i][2] = c;
            v[a].pb(b);
            v[b].pb(a);
        }
        solveinit();
        cin >> m;
        REP(i , 1 , m + 1){
            int a , b;
            cin >> a >> b;
            query(a , b);
        }
    }
    return 0;
}
