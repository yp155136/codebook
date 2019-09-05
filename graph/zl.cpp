struct ZL{
	//1 base edge and vertex
    static const int N=556,M=2660, MM = M * 10,inf=1e9; 
    //MM = M * log N
	struct bian{
	    int u,v,w,use,id;
	}b[M],a[MM];
	int n,m=0,ans,pre[N],id[N],vis[N],root,In[N],h[N],len,way[M];
	void init(int _n,int _root){
        for (int i = 0; i < MM; ++i) {
            a[i] = {0, 0, 0, 0, 0};
        }
		n=_n; m=0; b[0].w=1e9; root=_root;
	}
	void add(int u,int v,int w){
		b[++m]=(bian){u,v,w,0,m};
		a[m]=b[m];
	}
	int work(){
		len=m;
	    for (;;){
	        for (int i=1;i<=n;i++){pre[i]=0; In[i]=inf; id[i]=0; vis[i]=0; h[i]=0;}
	        for (int i=1;i<=m;i++)
	            if (b[i].u!=b[i].v&&b[i].w<In[b[i].v]){
	                pre[b[i].v]=b[i].u; In[b[i].v]=b[i].w; h[b[i].v]=b[i].id;
	            }
	        for (int i=1;i<=n;i++) if (pre[i]==0&&i!=root) return 0;
	        int cnt=0; In[root]=0;
	        for (int i=1;i<=n;i++){
	            if (i!=root) a[h[i]].use++; 
	            int now=i; ans+=In[i];
	            while (vis[now]==0&&now!=root){
	                vis[now]=i; now=pre[now];
	            }
	            if (now!=root&&vis[now]==i){
	                cnt++; int kk=now;
	                while (1){
	                    id[now]=cnt; now=pre[now];
	                    if (now==kk) break;
	                }
	            }
	        }
	        if (cnt==0) return 1;
	        for (int i=1;i<=n;i++) if (id[i]==0) id[i]=++cnt;
	        for (int i=1;i<=m;i++){
	            int k1=In[b[i].v]; int k2=b[i].v;
	            b[i].u=id[b[i].u]; b[i].v=id[b[i].v];       
	            if (b[i].u!=b[i].v){
	                b[i].w-=k1; a[++len].u=b[i].id; a[len].v=h[k2];
	                b[i].id=len;
	            }
	        }
	        n=cnt;
	        root=id[root];
	    }
	    return 1;
	}
	int getway(){
		for (int i=1;i<=m;i++) way[i]=0;
		for (int i=len;i>m;i--){
			a[a[i].u].use+=a[i].use; a[a[i].v].use-=a[i].use;
		}
		for (int i=1;i<=m;i++) way[i]=a[i].use;
        int ret = 0;
        for (int i = 1; i <= m; ++i){
            if (way[i] == 1) {
                ret += a[i].w;
            }
        }
        return ret;
	}
} zl;
//if zl.work() == 0, then it is not connected
//otherwise, use zl.getway() to check bian is selected or not
