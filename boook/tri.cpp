PII p[MAX];
int n , idx[MAX] , pos[MAX];
long long wnt;
vector<PII> v;
inline PII operator + (PII x , PII y){ return mp(x.A + y.A , x.B + y.B); }
inline PII operator - (PII x , PII y){ return mp(x.A - y.A , x.B - y.B); }
inline long long cross(PII x , PII y){ return 1ll * x.A * y.B - 1ll * x.B * y.A; }
inline long long calcArea(PII x , PII y , PII z){
    long long val = abs(cross(y - x , z - x));
    return val;
}
inline int cmp1(PII x , PII y){
    x = p[x.B] - p[x.A];
    y = p[y.B] - p[y.A];
    return cross(x , y) > 0;
}
int32_t main(){
    cin >> n >> wnt , wnt += wnt;
    REP(i , 1 , n + 1) cin >> p[i].A >> p[i].B;
    sort(p + 1 , p + 1 + n);
    REP(i , 1 , n + 1) idx[i] = i , pos[i] = i;
    REP(i , 1 , n + 1) REP(j , i + 1 , n + 1) v.pb(mp(i , j));
    sort(ALL(v) , cmp1);
    for(auto line : v){
        int fr = pos[line.A] , ba = pos[line.B] , now;
        if(fr > ba) swap(fr , ba);
        now = fr;
        RREP(i , 10 , 0){
            int to = now - (1 << i);
            if(to >= 1 && calcArea(p[idx[fr]] , p[idx[ba]] , p[idx[to]]) <= wnt) now = to;
        }
        now = ba;
        RREP(i , 10 , 0){
            int to = now + (1 << i);
            if(to <= n && calcArea(p[idx[fr]] , p[idx[ba]] , p[idx[to]]) <= wnt) now = to;
        }
        swap(idx[fr] , idx[ba]) , swap(pos[line.A] , pos[line.B]);
    }
    cout << "No" << endl;
    return 0;
}
