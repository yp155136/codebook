
## Suffix Automation ##
```cpp
const int maxnode = 1000000 + 5;
const int SIGMA_SIZE = 26;
struct Node {
  Node *fail, *ch[SIGMA_SIZE];
  int Max;
  Node() {Max = 0, fail = 0; memset(ch, 0, sizeof ch);}
} node[maxnode], *root, *last;
struct SuffixAutomaton {
  int size;
  inline int idx(char c) {return c - 'a';}
  inline void init() {size = 0; last = root = &node[0];}
  inline void add(char c) {
    c = idx(c);
    Node *p = last;
    Node *np = &node[++size];
    np->Max = p->Max + 1;
    while (p && !p->ch[c]) { p->ch[c] = np, p = p->fail; }
    if (!p) { np->fail = root; }
    else {
      Node *q = p->ch[c];
      if (q->Max == p->Max + 1) { np->fail = q; }
      else {
        Node *nq = &node[++size];
        nq->Max = p->Max + 1;
        memcpy(nq->ch, q->ch, sizeof(q->ch));
        nq->fail = q->fail;
        q->fail = np->fail = nq;
        while (p && p->ch[c] == q) { p->ch[c] = nq, p = p->fail; }
      }
    }
    last = np;
  }
} SAM;
```
