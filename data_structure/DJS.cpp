struct DJS{
    int p[N], rk[N];
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
    //assign(&a, b); //a = b
} djs;
