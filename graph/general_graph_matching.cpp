const int N = 100006, E = (2e5) * 2;
struct Graph{
    //1-index
    int to[E],bro[E],head[N],e;
    int lnk[N],vis[N],stp,n;
    int per[N];
    void init( int _n ){
        //remember to set every array to 0
        stp = 0; e = 1; n = _n;
        for( int i = 1 ; i <= n ; i ++ )
            head[i] = lnk[i] = vis[i] = 0, per[i] = i;
        //random_shuffle(per+1, per+n+1);
    }
    void add_edge(int u,int v){
        u=per[u], v=per[v];
        to[e]=v,bro[e]=head[u],head[u]=e++;
        to[e]=u,bro[e]=head[v],head[v]=e++;
    }
    bool dfs(int x){
        vis[x]=stp;
        for(int i=head[x];i;i=bro[i]){
            int v=to[i];
            if(!lnk[v]){
                lnk[x]=v,lnk[v]=x;
                return true;
            }else if(vis[lnk[v]]<stp){
                int w=lnk[v];
                lnk[x]=v,lnk[v]=x,lnk[w]=0;
                if(dfs(w)){
                    return true;
                }
                lnk[w]=v,lnk[v]=w,lnk[x]=0;
            }
        }
        return false;
    }
    int solve(){
        int ans = 0;
        for(int i=1;i<=n;i++)
            if(!lnk[i]){
                stp++; ans += dfs(i);
            }
        return ans;
    }
} graph;
