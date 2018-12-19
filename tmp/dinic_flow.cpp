#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define SZ(x) ((int)(x).size())

struct Dinic_Flow {
	static const int MAX_N = 8e3 + 6;
	static const int INF = 1e9 +7;
	int n,s,t;
	struct Edge {
		int to,cap,rev;
	};
	vector<Edge> edg[MAX_N];
	void init(int _n,int _s,int _t) {
		for (int i=0;_n>=i;i++) {
			edg[i].clear();
		}
		n=_n;
		s=_s;
		t=_t;
	}
	void add_edge(int from,int to,int cap) {
		edg[from].push_back({to,cap,SZ(edg[to])});
		edg[to].push_back({from,0,SZ(edg[from])-1});
	}
	int level[MAX_N],iter[MAX_N];
	void bfs(int s) {
		queue<int> que;
		que.push(s);
		memset(level,-1,sizeof(level));
		level[s] = 0;
		while (!que.empty()) {
			int t=que.front();
			que.pop();
			for (Edge e:edg[t]) {
				if (e.cap > 0 && level[e.to]==-1) {
					level[e.to] = level[t] + 1;
					que.push(e.to);
				}
			}
		}
	}
	int dfs(int id,int flow) {
		if (id==t) return flow;
		int ret=0;
		for (int &i=iter[id];SZ(edg[id])>i;i++) {
			Edge &e=edg[id][i];
			if (e.cap > 0 && level[e.to] == level[id] + 1) {
				int ret=dfs(e.to,min(flow,e.cap));
				if (ret>0) {
					e.cap -= ret;
					edg[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	int flow() {
		int ret=0;
		while(true) {
			bfs(s);
			if (level[t] == -1) return ret;
			int tmp=0;
			memset(iter,0,sizeof(iter));
			while ((tmp=dfs(s,INF)) > 0) {
				ret += tmp;
			}
		}
		return ret;
	}
};

int main () {
	;
}
