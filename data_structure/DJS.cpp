struct DJS{
  int p[N], sz, rk[N];
  vector<pair<int*,int>> memo;
  vector<size_t> stk;
  void save(){
    stk.push_back(memo.size());
  }
  void undo(){
    while(memo.size() > stk.back()){
      *memo.back().first = memo.back().second;
      memo.pop_back();
    }
    stk.pop_back();
  }
  void assign(int *x, int v){
    memo.push_back({x, *x});
    *x=v;
  }
  void init(int n){
    for(int i=1; i<=n; i++) {p[i]=i; rk[i]=0;}
    sz=n; memo.clear(); stk.clear();
  }
  int f(int x){
    return x == p[x] ? x : f(p[x]);
  }
  void uni(int a, int b){
    int aa=f(a); int bb=f(b);
    if(aa == bb) return;
    assign(&sz, sz-1);
    if(rk[aa] > rk[bb]) swap(aa, bb);
    assign(&p[aa], bb);
    assign(&rk[bb], max(rk[bb], rk[aa]+1));
  }
} djs;
