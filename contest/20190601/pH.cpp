#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (1ll<<60);
/*
struct Node {
    Node *lc,*rc;
    ll sum,tag,mn;
    Node():lc(NULL),rc(NULL),tag(0),mn(INF),sum(0){}
    void pull() {
        sum = lc->sum + rc->sum;
        mn = min(lc->mn,rc->mn);
    }
};

Node* Build(int L,int R) {
    Node* node = new Node();
    if (L == R) {
        //blablabla
        ;
        return node;
    }
    int mid = (L+R)>>1;
    0node->lc = Build(L,mid);
    node->rc = Build(mid+1,R);
    node->pull();
    return node;
}

void push(Node* node,int L,int R) {
    if (L == R) node->tag = 0;
    if (node->tag == 0) return;
    node->lc->tag += node->tag;
    node->rc->tag += node->tag;
    node->lc->mn += node->tag;
    node->rc->mn += node->tag;
    node->tag = 0;
    return;
}

void modify1(Node* node,int L,int R,int l,int r,ll val) {
    if (l>R || L>r) return;
    else if (l <= L && R <= r) {
        node->tag += val;
        node->
    }
}
*/

const int N = 100006;

struct BIT {
    ll a[N];
    int n;
    void init(int _n) {
        n = _n+3;
        for (int i=0;i <= n;++i) {
            a[i] = 0;
        }
    }
    void update(int pos,ll val) {
        for (int i = pos;i < n; i += i&(-i)) {
            a[i] += val;
        }
    }
    ll query(int pos) {
        if (pos <= 0) return 0;
        ll ret = 0;
        for (int i=pos; i > 0; i-=i&(-i)) {
            ret += a[i];
        }
        return ret;
    }
    ll Q(int L,int R) {
        return query(R) - query(L-1);
    }
} bit,bit2;

int a[N];
ll ch[N];

void add(int pos,int val) {
    if (ch[pos] > 0) bit.update(pos,-ch[pos]);
    bit2.update(pos,-ch[pos]);
    ch[pos] += val;
    if (ch[pos] > 0) bit.update(pos,ch[pos]);
    bit2.update(pos,ch[pos]);
}

int main () {
    int T; scanf("%d",&T);
    while (T--) {
        int n, q; scanf("%d%d",&n,&q);
        bit.init(n);
        bit2.init(n);
        for (int i=1;i<=n;++i) {
            scanf("%d",&a[i]);
            ch[i] = a[i] - a[i-1];
            if (ch[i] >= 0) {
                bit.update(i,ch[i]);
            }
            bit2.update(i,ch[i]);
        }
        while (q--) {
            int t; scanf("%d",&t);
            if (t == 1) {
                int l,r,k; scanf("%d%d%d",&l,&r,&k);
                add(l,k);
                if (r != n) add(r+1,-k);
            }
            else {
                int L,R; scanf("%d%d",&L,&R);
                printf("%lld\n",bit2.query(L) + bit.Q(L+1,R));
            }
        }
    }
}

