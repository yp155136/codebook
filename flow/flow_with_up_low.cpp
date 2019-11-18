/*
Maximum density subgraph ( \sum W_e + \sum W_v ) / |V|

Binary search on answer:
For a fixed D, construct a Max flow model as follow:
Let S be Sum of all weight( or inf)
1. from source to each node with cap = S
2. For each (u,v,w) in E, (u->v,cap=w), (v->u,cap=w)
3. For each node v, from v to sink with cap = S + 2 * D - deg[v] - 2 * (W of v)
where deg[v] = \sum weight of edge associated with v
If maxflow < S * |V|, D is an answer.

Requiring subgraph: all vertex can be reached from source with
edge whose cap > 0.
*/
struct Flow {
    static const int N = 8006;
    struct Edge {
        int to, cap, rev;
        Edge(int _to, int _cap, int _rev):to(_to), cap(_cap), rev(_rev){}
    };
    vector<Edge> G[N];
    int d[N];
    int S, T, s, t, n, nows, nowt;
    void init(int _n, int _s, int _t) {
        //vertex are numbered from 0 to n, and s and t the source/sink in the original graph
        S = _n+1, T= _n+2;
        s = _s, t = _t; n = _n;
        for (int i=0;n+3>=i;i++){
            G[i].clear();
            d[i] = 0;
        }
    }
    void add_edge(int from,int to,int low,int upp) {
        G[from].push_back(Edge(to,upp-low,SZ(G[to])));
        G[to].push_back(Edge(from,0,SZ(G[from])-1));
        d[from] -= low;
        d[to] += low;
    }
    void add_edge(int from,int to,int cap) {
        G[from].push_back(Edge(to,cap,SZ(G[to])));
        G[to].push_back(Edge(from,0,SZ(G[from])-1));
    }
    int iter[N],level[N];
    void BFS() {
        memset(level,-1,sizeof(level)); level[nows] = 1;
        queue<int> que; que.push(nows);
        while (!que.empty()) {
            int t=que.front(); que.pop();
            for (Edge e:G[t]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[t]+1;
                    que.push(e.to);
                }
            }
        }
    }
    int dfs(int now,int flow) {
        if (now == nowt) return flow;
        for (int &i=iter[now];SZ(G[now])>i;i++) {
            Edge &e = G[now][i];
            if (e.cap > 0 && level[e.to] == level[now]+1) {
                int ret = dfs(e.to,min(flow,e.cap));
                if (ret > 0) {
                    e.cap -= ret; G[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int flow() {
        int ret = 0;
        while (true) {
            BFS();
            if (level[nowt] == -1) break;
            memset(iter,0,sizeof(iter)); int tmp;
            while ((tmp = dfs(nows,1000000007)) > 0) {
                ret += tmp;
            }
        }
        return ret;
    }
    int get_ans() {
        nows = S,nowt = T;
        int base=0;
        for (int i=0;n>=i;i++) {
            if (d[i] > 0) base += d[i];
            if (d[i] > 0) add_edge(S,i,d[i]);
            if (d[i] < 0) add_edge(i,T,-d[i]);
        }
        add_edge(t,s,0,1000000007);
        if (flow() != base) return -1; //invalid flow
        nows = s,nowt = t;
        return flow();
    }
} flow;
