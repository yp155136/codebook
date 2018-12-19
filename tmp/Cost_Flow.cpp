#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

struct CostFlow {
	static const int MAX_N = 2e3 + 6;
	struct Edge {
		int to,cap,rev,cost;
	};
	int s,t,n;
	vector<Edge> edg[MAX_N];
	void init(int _n,int _s,int _t) {
		n=_n;
		s=_s;
		t=_t;
		for (int i=0;n>=i;i++) {
			edg[i].clear();
		}
	}
	#define SZ(x) ((int)(x).size())
	void add_edge(int from,int to,int cap,int cost) {
		edg[from].push_back({to,cap,SZ(edg[to]),cost});
		edg[to].push_back({from,0,SZ(edg[from])-1,-cost});
	}
	static const int INF = 1e9 + 7;
	int dis[MAX_N];
	int pre[MAX_N];
	int pre_id[MAX_N];
	bool in_que[MAX_N];
	pii flow() {
		int flow=0,cost=0;
		while (true) {
			for (int i=0;n>=i;i++) {
				dis[i] = INF;
				in_que[i] = false;
			}
			queue<int> que;
			que.push(s);
			dis[s] = 0;
			while (!que.empty()) {
				int t=que.front();
				que.pop();
				in_que[t] = false;
				int id=0;
				for (Edge e:edg[t]) {
					if (e.cap > 0 && dis[e.to] > dis[t] + e.cost) {
						dis[e.to] = dis[t] + e.cost;
						pre[e.to] = t;
						pre_id[e.to] = id;
						if (!in_que[e.to]) {
							que.push(e.to);
							in_que[e.to] = true;
						}
					}
					id++;
				}
			}
			if (dis[t] == INF) break;
			int mn_flow = INF;
			for (int i=t;i!=s; i=pre[i]) {
				mn_flow = min(mn_flow,edg[pre[i]][pre_id[i]].cap);
			}
			flow += mn_flow;
			for (int i=t;i!=s; i=pre[i]) {
				edg[pre[i]][pre_id[i]].cap -= mn_flow;
				edg[i][edg[pre[i]][pre_id[i]].rev].cap += mn_flow;
			}
			cost += mn_flow * dis[t];
		}
		return make_pair(flow,cost);
	}
} Flow;

int main () {
	;
}

