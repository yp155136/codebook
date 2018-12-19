struct SW {
    //find global min cut in O(V^3)
    //points are ZERO-BASE!!!
    static const int N = 506;
    int adj[N][N],wei[N],n;
    bool vis[N],del[N];
    void init(int _n) {
        n = _n;
        memset(adj,0,sizeof(adj));
        memset(del,0,sizeof(del));
    }
    void add_edge(int x,int y,int w) {
        adj[x][y] += w;
        adj[y][x] += w;
    }
    void search(int &s,int &t) {
        memset(wei,0,sizeof(wei));
        memset(vis,0,sizeof(vis));
        s = t = -1;
        while (true) {
            int mx=-1, mx_id=0;
            for (int i=0;i<n;++i) {
                if (!del[i] && !vis[i] && mx<wei[i]) {
                    mx_id = i;
                    mx = wei[i];
                }
            }
            if (mx == -1) break;
            vis[mx_id] = true;
            s = t;
            t = mx_id;
            for (int i=0;i<n;++i) {
                if (!vis[i] && !del[i]) {
                    wei[i] += adj[mx_id][i];
                }
            }
        }
    }
    int solve() {
        int ret = 2147483647; //INF
        for (int i=0;i<n-1;++i) {
            int x,y;
            search(x,y);
            ret = min(ret,wei[y]);
            del[y] = true;
            for (int i=0;i<n;++i) {
                adj[x][i] += adj[y][i];
                adj[i][x] += adj[y][i];
            }
        }
        return ret;
    }
} SW;
