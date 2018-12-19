#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
using namespace std;

typedef long long Meruru;
const int MAX_N = 1e5 + 6;
const int MAX_P = 18;

struct Edge {
	int to,weight;
};

Edge MP(int _to,int _weight) {
	return Edge{_to,_weight};
}

vector<Edge> edg[MAX_N];
Meruru dis[MAX_P][MAX_N];
bool visit[MAX_N];
int sz[MAX_N];
int mx[MAX_N];

struct Cen {
	Meruru minus;
	Meruru val;
	int p;
	int sz;
	int depth;
} cen[MAX_N];

Cen MP_cen(int _p,int _depth) {
	return Cen{0,0,_p,0,_depth};
}

vector<int> v;

void get_cen(int id) {
	visit[id]=1;
	v.push_back(id);
	sz[id]=1;
	mx[id]=0;
	for (Edge i:edg[id]) {
		if (!visit[i.to]) {
			get_cen(i.to);
			mx[id] = max(mx[id],sz[i.to]);
			sz[id] += sz[i.to];
		}
	}
}

void get_dis(int id,int cen_depth,Meruru weight) {
	dis[cen_depth][id] = weight;
	visit[id]=1;
	for (Edge i:edg[id]) {
		if (!visit[i.to]) {
			get_dis(i.to,cen_depth,weight+i.weight);
		}
	}
}

void dfs(int id,int cen_depth,int p) {
	get_cen(id);
	int nn=v.size();
	int ccen=-1;
	for (int i:v) {
		if (max(nn-sz[i],mx[i]) <= nn/2) {
			ccen=i;
		}
		visit[i]=0;
	}
	get_dis(ccen,cen_depth,0);
	for (int i:v) {
		visit[i]=0;
	}
	v.clear();
	visit[ccen]=1;
	cen[ccen] = MP_cen(p,cen_depth);
	for (Edge i:edg[ccen]) {
		if (!visit[i.to]) {
			dfs(i.to,cen_depth+1,ccen);
		}
	}
}

void add(int id) {
	int p=id;
	while (p!=-1) {
		cen[p].val += dis[cen[p].depth][id];
		cen[p].sz++;
		cen[p].minus += dis[cen[p].depth-1][id];
		p=cen[p].p;
	}
}

Meruru query(int id) {
	int p=id;
	Meruru ret=0;
	int szz=0;
	while (p!=-1) {
		ret += (cen[p].val - cen[p].minus);
		ret += (cen[p].sz - szz)*dis[cen[p].depth][id];
		szz = cen[p].sz;
		p=cen[p].p;
	}
	return ret;
}

int main () {
	int n,q;
	scanf("%d %d",&n,&q);
	for (int i=1;n>i;i++) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		a++;
		b++;
		edg[a].push_back(MP(b,c));
		edg[b].push_back(MP(a,c));
	}
	dfs(1,1,-1);
	memset(visit,0,sizeof(visit));
	while (q--) {
		int a,b;
		scanf("%d %d",&a,&b);
		b++;
		if (a==1 && !visit[b]) {
			add(b);
			visit[b]=1;
		}
		else if (a==2)printf("%lld\n",query(b));
	}
}
