#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;

#define LL   long long
#define ld   long double
#define pii  pair<int,int>
#define pLL  pair<LL,LL>
#define vint vector<int>
#define vLL  vector<LL>
#define vpii vector<pii>

#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define F first
#define S second
#define MP make_pair
#define PB push_back

#define Si(x) scanf("%d",&(x));
#define Sii(x,y) scanf("%d %d",&(x),&(y));
#define Siii(x,y,z) scanf("%d %d %d",&(x),&(y),&(z));
#define Siiii(x,y,z,w) scanf("%d %d %d %d",&(x),&(y),&(z),&(w));
#define Siiiii(x,y,z,w,a) scanf("%d %d %d %d %d",&(x),&(y),&(z),&(w),&(a));
#define Siiiiii(x,y,z,w,a,b) scanf("%d %d %d %d %d %d",&(x),&(y),&(z),&(w),&(a),&(b));
#define SL(x) scanf("%lld",&(x));
#define SLL(x,y) scanf("%lld %lld",&(x),&(y));
#define SLLL(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z));
#define SLLLL(x,y,z,w) scanf("%lld %lld %lld %lld",&(x),&(y),&(z),&(w));
#define SLLLLL(x,y,z,w,a) scanf("%lld %lld %lld %lld %lld",&(x),&(y),&(z),&(w),&(a));
#define SLLLLLL(x,y,z,w,a,b) scanf("%lld %lld %lld %lld %lld %lld",&(x),&(y),&(z),&(w),&(a),&(b));

#define Pi(x) printf("%d\n",(x));
#define Pii(x,y) printf("%d %d\n",(x),(y));
#define Piii(x,y,z) printf("%d %d %d\n",(x),(y),(z));
#define Piiii(x,y,z,w) printf("%d %d %d %d\n",(x),(y),(z),(w));
#define Piiiii(a,b,c,d,e) printf("%d %d %d %d %d\n",(a),(b),(c),(d),(e));
#define Piiiiii(a,b,c,d,e,f) printf("%d %d %d %d %d %d\n",(a),(b),(c),(d),(e),(f));
#define PL(x) printf("%lld\n",(x)*1LL);
#define PLL(x,y) printf("%lld %lld\n",(x)*1LL,(y)*1LL);
#define PLLL(x,y,z) printf("%lld %lld %lld\n",(x)*1LL,(y)*1LL,(z)*1LL);
#define PLLLL(x,y,z,w) printf("%lld %lld %lld %lld\n",(x)*1LL,(y)*1LL,(z)*1LL,(w)*1LL);
#define PLLLLL(a,b,c,d,e) printf("%lld %lld %lld %lld %lld\n",(a),(b),(c),(d),(e));
#define PLLLLLL(a,b,c,d,e,f) printf("%lld %lld %lld %lld %lld %lld\n",(a),(b),(c),(d),(e),(f));

#define Pi1(x) printf("%d",  (x));
#define PL1(x) printf("%lld",(x));
#define Pspace putchar(' ');
#define Pendl  puts("");

#define MEM0(x) memset( (x), 0, sizeof( (x) ) )
#define MEM1(x) memset( (x),-1, sizeof( (x) ) )
#define REP1(i,n)  for (int i = 1; (n) >= i ; ++i)
#define REP0(i,n)  for (int i = 0; (n) >  i ; ++i)

int myRnd() {
    return abs(  ((rand()<<15) | rand()) );
}

int myRnd(int L,int R) {
    return abs(( (rand()<<15)|rand() ) ) % (R-L+1) + L;
}

void Parr(int *arr,int L,int R) {
    for (int i=L;R>=i;i++) {
        printf("%d%c",arr[i]," \n"[i==R]);
    }
}

void Pvec(vint v) {
    for (int i=0;SZ(v)>i;i++) {
        printf("%d%c",v[i]," \n"[i==SZ(v)-1]);
    }
}

const int N = 5e5 + 6;

bool can[N];

struct Second_MST {
    static const int N = 5e5 + 6;
    static const int P = 20; //P = lg N
    static const int INF = 1e9 + 7;
    vpii G[N];
    struct Edge {
        int a,b,c;  //cost = c
        Edge(){}
        Edge(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
        bool operator<(const Edge &e1) {
            return c<e1.c;
        }
    };
    struct DisjointSet {
        int p[N];
        int sz[N];
        void init(int n) {
            for (int i=0;n>=i;i++) {
                p[i] = i;
                sz[i] = 1;
            }
        }
        int Find(int x) {
            return p[x] == x?x:p[x]=Find(p[x]);
        }
        void Union(int x,int y) {
            x=Find(x);
            y=Find(y);
            if (x==y) return;
            if (sz[x] > sz[y]) swap(x,y);
            p[x] = y;
            sz[y] += sz[x];
        }
    } djs;
    vector<Edge> edg;
    int n,m;
    int type[N]; //1 --> on original MST, 2 --> can on MST
    void init(int n,int m) {
        this->n = n;
        this->m = m;
        REP0(i,n+1)
        {
            G[i].clear();
        }
        edg.clear();
        MEM0(type);
    }
    void add_edge(int a,int b,int c) {
        edg.PB(Edge(a,b,c));
    }
    LL ret_MST;
    LL Kruskal() {
        LL ret=0;
        djs.init(n);
        sort(ALL(edg));
        int eid=-1;
        for (Edge e:edg) {
            eid++;
            if (djs.Find(e.a) == djs.Find(e.b)) {
                continue;
            }
            ret += e.c;
            djs.Union(e.a,e.b);
            G[e.a].PB({e.b,e.c});
            G[e.b].PB({e.a,e.c});
            type[eid] = 1;
        }
        this->ret_MST = ret;
        return ret;
    };
    pii lca[P][N];
    int pin[N],pout[N];
    int pid;
    void dfs(int v,int par,int cost) {
        lca[0][v] = {par,cost};
        pin[v] = pid++;
        for (pii p:G[v]) {
            if (p.F != par) dfs(p.F,v,p.S);
        }
        pout[v] = pid++;
    }
    bool is_anc(int son,int par) {
        return pin[par] <= pin[son] && pout[son] <= pout[par];
    }
    int get_path(int son,int par) {
        if (son == par) return 0;
        int ret=0;
        for (int i=P-1;i>=0;i--) {
            if (!is_anc(par,lca[i][son].F)) {
                ret = max(ret,lca[i][son].S);
                son = lca[i][son].F;
            }
        }
        return max(ret,lca[0][son].S);
    }
    int get_lca(int u,int v) {
        if (is_anc(u,v)) return v;
        if (is_anc(v,u)) return u;
        for (int i=P-1;i>=0;i--) {
            if (!is_anc(v,lca[i][u].F)) {
                u = lca[i][u].F;
            }
        }
        return lca[0][u].F;
    }
    LL get_second_MST() {
        Kruskal();
        pid=0;
        dfs(1,1,INF);
        REP1(i,P-1)
        {
            REP1(j,n)
            {
                lca[i][j] ={lca[ i-1 ][ lca[i-1][j].F ].F,max(lca[i-1][j].S, lca[ i-1 ][ lca[i-1][j].F ].S )};
            }
        }
        LL ret = ret_MST + INF;
        int eid=-1;
        for (Edge e:edg) {
            eid++;
            if (type[eid] == 1) continue;
            int lca=get_lca(e.a,e.b);
            LL mx = max(get_path(e.a,lca),get_path(e.b,lca));
            if (mx == e.c) {
                type[eid] = 2;
            }
            ret = min(ret,ret_MST - mx + e.c);
        }
        return ret;
    }
} solver;

int main () {
    ;
}
