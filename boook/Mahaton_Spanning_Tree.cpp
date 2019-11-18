#define edge pair<int , PII>
int n , sol[MAX];
PII x[MAX];
vector<edge> v;
class djs{
public:
    int x[MAX];
    void init(){ REP(i , 0 , MAX) x[i] = i; }
    int Find(int now){ return x[now] == now ? now : x[now] = Find(x[now]); }
    void Union(int a , int b){ x[Find(a)] = Find(b); }
    int operator[](int now){ return Find(now); }
} ds;
PII bit[MAX];
void update(int from , int val , int id){
    for(int i = from ; i < MAX ; i += i & -i)
        bit[i] = max(bit[i] , mp(val , id));
}
int query(int from){
    PII res = bit[from];
    for(int i = from ; i > 0 ; i -= i & -i)
        res = max(res , bit[i]);
    return res.B;
}
int cmp(int a , int b){
    return x[a] < x[b];
}
int DIS(int q , int w){
    return abs(x[q].A - x[w].A) + abs(x[q].B - x[w].B);
}
void BuildEdge(){
    vector<int> uni;
    REP(i , 0 , MAX) bit[i] = mp(-INF , -1);
    REP(i , 0 , n) sol[i] = i;
    REP(i , 0 , n) uni.pb(x[i].B - x[i].A);
    sort(ALL(uni));
    uni.resize(unique(ALL(uni)) - uni.begin());
    sort(sol , sol + n , cmp);
    REP(i , 0 , n){
        int now = sol[i];
        int tmp = x[sol[i]].B - x[sol[i]].A;
        int po = lower_bound(ALL(uni) , tmp) - uni.begin() + 1;
        int id = query(po);
        if(id >= 0) v.pb(mp(DIS(id , now) , mp(id , now)));
        update(po , x[now].A + x[now].B , now);
    }
}
void Build(){
    BuildEdge();
    REP(i , 0 , n) swap(x[i].A , x[i].B);
    BuildEdge();
    REP(i , 0 , n) x[i].A *= -1;
    BuildEdge();
    REP(i , 0 , n) swap(x[i].A , x[i].B);
    BuildEdge();
}
int solveKruskal(){
    ds.init();
    sort(ALL(v));
    int res = 0;
    REP(i , 0 , v.size()){
        int dis = v[i].A;
        PII tmp = v[i].B;
        if(ds[tmp.A] != ds[tmp.B]){
            ds.Union(tmp.A , tmp.B);
            res += dis;
        }
    }
    return res;
}
int32_t main(){
    IOS;
    cin >> n;
    REP(i , 0 , n) cin >> x[i].A >> x[i].B;
    Build();
    int ans = solveKruskal();
    cout << ans << endl;
    return 0;
}
