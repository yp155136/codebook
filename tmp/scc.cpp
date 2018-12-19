
struct SCC {
	static const int MAX_N = 5e4 +6;
	vector<int> edg[MAX_N];
	vector<int> rev_edg[MAX_N];
	int n;
	vector<int> vv[MAX_N];
	void init(int _n) {
		n=_n;

		for(int i=0;n>=i;i++){
			edg[i].clear();
			rev_edg[i].clear();
			v[i].clear();
			vv[i].clear();
		}
	}
	void add_edge(int from,int to) {
		edg[from].push_back(to);
		rev_edg[to].push_back(from);
	}
	bool visit[MAX_N];
	int get_stamp[MAX_N];
	int in_scc[MAX_N];
	int stamp;
	void dfs1(int id) {
		visit[id]=1;
		for (int i:rev_edg[id]) {
			if (!visit[i]) dfs1(i);
		}
		get_stamp[++stamp] = id;
	}
	void dfs2(int id,int scc) {
		visit[id]=1;
		for (int i:edg[id]) {
			if (!visit[i]) dfs2(i,scc);
		}
		in_scc[id] = scc;
		vv[scc].push_back(id);
	}
	void make_scc() {
		memset(visit,0,sizeof(visit));
		stamp=0;
		for (int i=1;n>=i;i++) {
			if (!visit[i]) dfs1(i);
		}
		memset(visit,0,sizeof(visit));
		int scc=0;
		for (int i=n;i>=1;i--) {
			if (!visit[get_stamp[i]]) {
				dfs2(get_stamp[i],++scc);
			}
		}
	}
	vector<int> v[MAX_N];
	int deg[MAX_N];
	int _1,_2;
	int meruru[MAX_N];
	int gett(int x) {
		return x>n/2?x-n/2:x;
	}
	bool dfs3(int id) {
		visit[id]=1;
		bool ret=true;
		for (int x:vv[id]) {
			if (meruru[gett(x)] == -1) {
				meruru[gett(x)] = (x>n/2?0:1);
			}
			else if (meruru[gett(x)] == 0 && x<=n/2) return false;
			else if (meruru[gett(x)] == 1 && x>n) return false;
		}
		for (int j:v[id]) {
			if (!visit[j]) ret&=dfs3(j);
		}
		return ret&(id != _2);
	}
	bool judge() {
		make_scc();
		for (int i=1;n/2>=i;i++) {
			if (in_scc[i] == in_scc[i+n/2]) return false;
		}
		_1 = in_scc[1],_2=in_scc[1+n/2];
		memset(visit,0,sizeof(visit));
		for (int i=1;n>=i;i++) {
			for (int j:edg[i]) {
				if (in_scc[i] != in_scc[j]) {
					v[in_scc[i]].push_back(in_scc[j]);
				}
			}
		}
		memset(meruru,-1,sizeof(meruru));
		meruru[1] = 1;
		return dfs3(_1);
	}
} scc;
