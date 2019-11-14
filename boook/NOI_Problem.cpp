int n , m , x[MAX];
class N{
public: int tag , sml , sum , none;
} b[MAX * 4];
void Pull(int now , int l , int r){
    if(l == r){
        if(b[now].tag){
            b[now].sum = b[now].tag;
            b[now].none = 0;
            b[now].sml = b[now].tag;
        }
        else{
            b[now].sum = 0;
            b[now].none = 1;
            b[now].sml = INF;
        }
    }
    else {
        b[now].sml = min(b[ls].sml , b[rs].sml);
        if(b[now].tag) b[now].sml = min(b[now].sml , b[now].tag);

        b[now].sum = b[ls].sum + b[rs].sum;
        b[now].none = b[ls].none + b[rs].none;
        if(b[now].tag) b[now].sum += b[now].tag * b[now].none , b[now].none = 0;
    }
}
void take_tag(int now , int l , int r , int val){
    if(b[now].tag && b[now].tag < val) b[now].tag = 0;
    if(l != r && b[ls].sml < val) take_tag(ls , l , mid , val);
    if(l != r && b[rs].sml < val) take_tag(rs , mid + 1 , r , val);
    Pull(now , l , r);
}
void Build(int now , int l , int r){
    b[now].none = 0;
    if(l == r) b[now].tag = b[now].sml = b[now].sum = x[l];
    else {
        Build(ls , l , mid) , Build(rs , mid + 1 , r);
        Pull(now , l , r);
    }
}
void update(int now , int l , int r , int ql , int qr , int val){
    if(b[now].tag >= val) return ;
    if(ql <= l && r <= qr){
        take_tag(now , l , r , val);
        b[now].tag = val;
        Pull(now , l , r);
    }
    else{
        if(qr <= mid) update(ls , l , mid , ql , qr , val);
        else if(mid + 1 <= ql) update(rs , mid + 1 , r , ql , qr , val);
        else update(ls , l , mid , ql , qr , val) , update(rs , mid + 1 , r , ql , qr , val);
        Pull(now , l , r);
    }
}
PII query(int now , int l , int r , int ql , int qr){
    if(ql <= l && r <= qr) return mp(b[now].sum , b[now].none);
    else {
        PII ans = mp(0 , 0);
        if(qr <= mid) ans = query(ls , l , mid , ql , qr);
        else if(mid + 1 <= ql) ans = query(rs , mid + 1 , r , ql , qr);
        else {
            PII a = query(ls , l , mid , ql , qr);
            PII b = query(rs , mid + 1 , r , ql , qr);
            ans = mp(a.A + b.A , a.B + b.B);
        }
        if(b[now].tag != 0) ans.A += ans.B * b[now].tag , ans.B = 0;
        return ans;
    }
}
REP(i , 1 , n + 1) cin >> x[i];
Build(1 , 1 , n);
update(1 , 1 , n , l , r , v);
cout << query(1 , 1 , n , l , r).A << endl;
