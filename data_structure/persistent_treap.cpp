#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 6;
const int MAX_M = 1e6 + 6;
const int MAX_P = 3e7;

struct Treap {
    static Treap mem[MAX_P];
    Treap *lc,*rc;
    char c; int sz;
    Treap(){}
    Treap(char _c) : lc(NULL),rc(NULL),sz(1),c(_c){}
} Treap::mem[MAX_P], *ptr=Treap::mem ;
int Sz(Treap* t) {
    return t?t->sz:0;
}
void pull(Treap* t) {
    if (!t) return;
    t->sz = Sz(t->lc) + Sz(t->rc) + 1;
}
Treap* merge(Treap* a,Treap* b) {
    if (!a || !b) return a?a:b;
    Treap* ret;
    if (myRnd() % (Sz(a) + Sz(b)) < Sz(a)) {
        ret = new (ptr++) Treap(*a);
        ret->rc = merge(a->rc,b);
    }
    else {
        ret = new(ptr++) Treap(*b);
        ret->lc=merge(a,b->lc);
    }
    pull(ret);
    return ret;
}
void split(Treap* t,int k,Treap* &a,Treap* &b) {
    if (!t) a=b=NULL;
    else if (Sz(t->lc) + 1 <= k) {
        a = new(ptr++) Treap(*t);
        split(t->rc,k-Sz(t->lc)-1,a->rc,b);
        pull(a);
    }
    else {
        b=new(ptr++) Treap(*t);
        split(t->lc,k,a,b->lc);
        pull(b);
    }
}
int d;
char buf[MAX_M];
Treap* ver[MAX_N];

ptr = Treap::mem;
v_cnt++;
ver[v_cnt] = ver[v_cnt-1];
split(ver[v_cnt],p,tl,tr);
tl = merge(tl,new(ptr++)Treap(buf[j]));
