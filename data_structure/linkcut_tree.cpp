struct SplayNode {
    static SplayNode HOLE;
    SplayNode *ch[2], *par;
    bool rev;
    SplayNode(): par(&HOLE), rev(false) { ch[0] = ch[1] = &HOLE; }
    bool isRoot() {
        return (par->ch[0] != this && par->ch[1] != this);
    }
    void push() {
        if (rev) {
            if (ch[0]) ch[0]->rev ^= 1;
            if (ch[1]) ch[1]->rev ^= 1;
            swap(ch[0], ch[1]);
            rev ^= 1;
        }
    }
    void pushFromRoot() {
        if (!isRoot()) par->pushFromRoot();
        push();
    }
    void pull() {
        if (ch[0]) ch[0]->d = d + ch[0]->parLen;
        if (ch[1]) ch[1]->d = d + ch[1]->parLen;
    }
    void rotate() {
        SplayNode *p = par, *gp = p->par;
        bool dir = (p->ch[1] == this);
        par = gp;
        if (!p->isRoot()) gp->ch[gp->ch[1] == p] = this;
        p->ch[dir] = ch[dir ^ 1];
        p->ch[dir]->par = p;
        p->par = this;
        ch[dir ^ 1] = p;
        p->pull(), pull();
    }
    void splay() {
        pushFromRoot();
        while (!isRoot()) {
            if (!par->isRoot()) {
                SplayNode *gp = par->par;
                if ((gp->ch[0] == par) == (par->ch[0] == this)) rotate();
                else par->rotate();
            }
            rotate();
        }
    }
} SplayNode::HOLE;
namespace LCT {
    SplayNode *access(SplayNode *x) {
        SplayNode *last = &SplayNode::HOLE;
        while (x != &SplayNode::HOLE) {
            x->splay();
            x->ch[1] = last;
            x->pull();
            last = x;
            x = x->par;
        }
        return last;
    }
    void makeRoot(SplayNode *x) {
        access(x);
        x->splay();
        x->rev ^= 1;
    }
    void link(SplayNode *x, SplayNode *y) {
        makeRoot(x);
        x->par = y;
    }
    void cut(SplayNode *x, SplayNode *y) {
        makeRoot(x);
        access(y);
        y->splay();
        y->ch[0] = &SplayNode::HOLE;
        x->par = &SplayNode::HOLE;
    }
    void cutParent(SplayNode *x) {
        access(x);
        x->splay();
        x->ch[0]->par = &SplayNode::HOLE;
        x->ch[0] = &SplayNode::HOLE;
    }
    SplayNode *findRoot(SplayNode *x) {
        x = access(x);
        while (x->ch[0] != &SplayNode::HOLE) x = x->ch[0];
        x->splay();
        return x;
    }
    SplayNode *query(SplayNode *x, SplayNode *y) {
        makeRoot(x);
        return access(y);
    }
    SplayNode *queryLca(SplayNode *x, SplayNode *y) {
        access(x);
        auto lca = access(y);
        x->splay();
        return lca->data + lca->ch[1]->sum + (x == lca ? 0 : x->sum);
    }
    void modify(SplayNode *x, int data) {
        x->splay();
        x->data = data;
        x->pull();
    }
}
