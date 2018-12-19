#include <bits/stdc++.h>
using namespace std;

const int N = 50006;

#define F first
#define S second

vector<int> G[N];
int pin[N],pout[N],stamp,sz[N],head[N],p[N];

int prego(int now,int par)
{
    head[now] = now;
    p[now] = par;
    sz[now] = 0;
    for (int son:G[now])
    {
        if (son == par) continue;
        sz[now] += prego(son,now);
    }
    return ++sz[now];
}

void go(int now,int par)
{
    pin[now] = ++stamp;
    sort(G[now].begin(),G[now].end(),
     [&](const int &a,const int &b)
     {
         return sz[a] > sz[b];
     });
    bool first = true;
    for (int son:G[now])
    {
        if (son == par) continue;
        go(son,now);
        if (first) head[son] = head[now];
        first = false;
    }
    pout[now] = ++stamp;
}

void HLD(int root)
{
    prego(root,root);
    go(root,root);
}

typedef pair<int,int> pii;

vector<pii> get_path(int u,int v)
{
    //u must be an ancestor of v
    //cout << "u = " << u << " , v = " << v << endl;
    vector<pii> ret;
    while (pin[u] < pin[ head[v] ])
    {
        ret.push_back(make_pair(pin[ head[v] ] , pin[v]));
        v = p[ head[v] ];
    }
    ret.push_back(make_pair( pin[u],pin[v] ));
    return ret;
}

const int P = 19;

int lca[P][N];

void build_lca_form(int n)
{
    for (int i=1;n>=i;i++)
    {
        lca[0][i] = p[i];
    }
    for (int i=1;P>i;i++)
    {
        for (int j=1;n>=j;j++)
        {
            lca[i][j] = lca[i-1][ lca[i-1][j] ];
        }
    }
}

bool is_anc(int par,int son)
{
    return pin[par] <= pin[son] && pout[son] <= pout[par];
}

int get_lca(int x,int y)
{
    if (is_anc(x,y)) return x;
    if (is_anc(y,x)) return y;
    for (int i=P-1;i>=0;i--)
    {
        if (!is_anc(lca[i][y],x))
        {
            y = lca[i][y];
        }
    }
    return p[y];
}

int cha[2*N],a[2*N];

void solve()
{
    stamp = 0;
    HLD(1);
    build_lca_form(n);
}
