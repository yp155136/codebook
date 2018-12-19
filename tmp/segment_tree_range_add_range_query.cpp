#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

struct Node {
    Node *lc,*rc;
    LL val,tag;
    Node() {
        lc=rc=NULL;
        val=tag=0;
    }
    void pull() {
        val = lc->val + rc->val;
    }
};

Node* Build(int L,int R) {
    Node* node = new Node();
    if (L==R) return node;
    int mid=(L+R)>>1;
    node->lc=Build(L,mid);
    node->rc=Build(mid+1,R);
    node->pull();
    return node;
}

void push(Node* node,int L,int R) {
    if (L == R) node->tag = 0;
    if (!node->tag) return;
    int mid= (L+R)>>1;
    node->lc->tag += node->tag;
    node->rc->tag += node->tag;
    node->lc->val += node->tag*(mid-L+1);
    node->rc->val += node->tag*(R-mid);
    node->tag = 0;
    return;
}

void modify(Node* node,int L,int R,int l,int r,LL val) {
    if (l>R || L>r) return;
    else if(l<=L && R<=r) {
        node->tag += val;
        node->val += (R-L+1)*val;
        return;
    }
    push(node,L,R);
    modify(node->lc,L,mid,l,r,val);
    modify(node->rc,mid+1,R,l,r,val);
    node->pull();
    return;
}

LL query(Node* node,int L,int R,int l,int r) {
    if(l>R || L>r) return 0;
    else if (l<=L && R<=r) return node->val;
    push(node,L,R);
    int mid=(L+R)>>1;
    return query(node->lc,L,mid,l,r) + query(node->rc,mid+1,R,l,r);
}
