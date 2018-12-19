#include <bits/stdc++.h>
using namespace std;

#define SZ(x) ((int)(x).size())

struct Dinic {
    static const int N = 1006;
    struct Edge {
        int to,cap,rev,ori;
        Edge(int _to,int _cap,int _rev,int _ori):to(_to),cap(_cap),rev(_rev),ori(_ori){}
    };
    vector<Edge> G[N];
    int add_edge(int from,int to,int cap) {
        G[from].push_back(Edge(to,cap,SZ(G[to]),cap));
        G[to].push_back(Edge(from,0,SZ(G[from])-1,0));
        return SZ(G[from]-1);
    }
    int n,s,t;
    void init(int _n,int _s,int _t) {
        n = _n; s = _s; t = _t;
        for (int i=0;i<=n;++i) {
            G[i].clear();
        }
    }
    int level[N],iter[N];
    void BFS() {
        memset(level,-1,sizeof(level));
        queue<int> que;
        que.push(s); level[s] = 1;
        while (!que.empty()) {
            int t=que.front();
            que.pop();
            for (Edge e:G[t]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[t] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    int dfs(int now,int flow) {
        if (now == t) return flow;
        for (int &i=iter[now];i<SZ(G[now]);++i) {
            Edge &e = G[now][i];
            if (e.cap > 0 && level[e.to] == level[now]+1) {
                int ret = dfs(e.to,min(flow,e.cap));
                if (ret > 0) {
                    e.cap -= ret;
                    G[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int flow(int _s,int _t) {
        s = _s;
        t = _t;
        int ret=0;
        while (true) {
            BFS();
            if (level[t] == -1) break;
            memset(iter,0,sizeof(iter));
            int tmp;
            while ((tmp = dfs(s,2147483647)) > 0) {
                ret += tmp;
            }
        }
        return ret;
    }
} dinic;

struct Gomory_Hu {
    static const int N = 1006;
    int id[N][N];
    int n;
    void init(int _n) {
        n = _n;
        dinic.init(n,n,n);
    }
    void add_edge(int a,int b
};

int main() {
    ;
}

