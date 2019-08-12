struct lt{
    ll p;
    int s;
    lt *ls, *rs;
    lt(ll _k) : p(_k), s(1), ls(0), rs(0){}
};
int ss(lt* &a){
    if(a == 0)    return 0;
    return a -> s;
}
lt* merge(lt* &a, lt* &b){
    if(a == 0 || b == 0)  return a == 0 ? b : a;
    if(a -> p > b -> p) swap(a, b);
    a -> rs=merge(a -> rs, b);
    if( ss(a -> rs) > ss(a -> ls) ) swap(a -> rs, a -> ls);
    a -> s = ss(a -> rs) + 1;
    return a;
}
void ins(lt* &a, ll _k){
    lt* tem = new lt(_k);
    a = merge(a,tem);
}
ll top(lt* &a){
//  if(a==0)    return -1;
    return a->p;
}
void pop(lt* &a){
//  if(a==0)    return;
    lt* tem=merge(a->ls,a->rs);
    delete a;
    a=tem;
}
