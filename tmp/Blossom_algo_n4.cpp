#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Blossom_n4 {
	//for more detail, see http://www.csie.ntnu.edu.tw/~u91029/Matching.html#5
	static const int MAX_N = 1e2 + 6;
	bool adj[MAX_N][MAX_N];  //save graph
	int n;  //total vertex
	void init(int n) {
		//vertex are numbered from 0 ~ n-1
		this->n = n;
		memset(adj,0,sizeof(adj));
	}
	void add_edge(int x,int y) {
		adj[x][y] = adj[y][x] = 1;
	}
	deque<int> p[MAX_N];  //p[i] --> alternating path from root to i
	int m[MAX_N]; //m[i] --> i matches m[i], if m[i] == i then i is no in graph
	int d[MAX_N]; 
	//d[i]==0 --> even point (distance from root is even), d[i]==-1 --> non-visit, d[i]==1-->odd point
	queue<int> que;
	#define SZ(x) ((int)(x).size())
	void label_path(int u,int v,int lca_id) {
		for (int i=lca_id+1;SZ(p[u])>i;i++) {
			int now=p[u][i];
			if (d[now] == 1) {
				//original odd point
				//can be changed to even point
				d[now] = 0;
				que.push(now);
				//change path from root
				p[now] = p[v];
				p[now].insert(p[now].end(),p[u].rbegin(),p[u].rend()-i);
			}
		}
	}
	bool BFS(int root) {
		for (int i=0;n>=i;i++) {
			p[i].clear();
		}
		memset(d,-1,sizeof(d));
		d[root] = 0;  //root is even point
		p[root].push_back(root);
		while (!que.empty()) que.pop();
		que.push(root);
		while (!que.empty()) {
			//only even points are in root
			int v=que.front();
			que.pop();
			for (int u=0;n>u;u++) {
				if (adj[v][u] && m[u] != u) {
					//the vertex exist and have an edge
					if (d[u] == -1) {
						//non-visited vertex
						if (m[u] == -1) {
							//find an unmatch point --> find an argument path
							for (int i=0;SZ(p[v])>i+1;i+=2) {
								m[p[v][i]] = p[v][i+1];
								m[p[v][i+1]] = p[v][i];
							}
							m[u] = v;
							m[v] = u;
							return true;
						}
						else {
							//extend the alternating tree
							int nxt = m[u];
							p[nxt] = p[v];
							p[nxt].push_back(u);
							p[nxt].push_back(nxt);
							d[u] = 1;
							d[nxt] = 0;
							que.push(nxt);
						}
					}
					else {
						//visited vertex
						if (d[u] == 1) {
							//odd points
							//only need to leave one path
							//so do nothing
							;
						}
						else if (d[u] == 0){
							//even point
							//we find a flower  -->  crossing edge from v to u
							//find lca first
							int lca_id=0;
							while (lca_id < SZ(p[u]) && lca_id<SZ(p[v]) && p[u][lca_id]==p[v][lca_id]) {
								lca_id++;
							}
							lca_id--;
							//label from lca_id --> u as even point
							label_path(u,v,lca_id);
							label_path(v,u,lca_id);
						}
					}
				}
			}
		}
		return false;
	}
	int matching() {
		memset(m,-1,sizeof(m));
		int ret=0;
		for (int i=0;n>i;i++) {
			if (m[i] == -1) {
				if (BFS(i)) {
					//successfully find an argument path
					ret++;
				}
				else {
					//fail to find an argument path --> delete this vertex
					m[i] = i;
				}
			}
		}
		return ret;
	}
} solver;


