//maximum clique

#include <iostream>
#include <stdio.h>
#include <bitset>
#include <cstring>
using namespace std;

struct maximum_clique {
	static const int MAX_N = 81;
	typedef bitset<MAX_N> bst;
	bst N[MAX_N];
	bst empty;
	int n;
	int ans;
	void init(int _n) {
		//point from 0 ~ n-1
		n=_n;
		for (int i=0;MAX_N>i;i++) {
			N[i] = empty;
		}
	}
	void add_edge(int a,int b) {
		N[a][b] = N[b][a] = 1;
	}
	void sagiri(bst R,bst P,bst X) {
		if (P==empty && X==empty) {
			ans = max(ans,(int)R.count());
			return;
		}
		bst tmp=P|X;
		int u;
		if ((R|P|X).count() <= ans) return;
		for (u=0;n>u;u++) {
			if (tmp[u]) break;
		}
		bst now = P&~N[u];  //P-N[u]
		for (int v=0;n>v;v++) {
			if (now[v]) {
				R[v] = true;
				sagiri(R,P&N[v],X&N[v]);
				R[v] = false;
				P[v] = false;
				X[v] = true;
			}
		}
	}
	int solve() {
		ans=0;
		bst R=empty,P,X=empty;
		P.flip();
		sagiri(R,P,X);
		return ans;
	}
} solver;

int main () {
	int n,m;
	cin >> n >> m;
	solver.init(n);
	for (int i=0;m>i;i++) {
		int a,b;
		cin >> a >> b;
		solver.add_edge(a,b);
	}
	cout<<solver.solve()<<endl;
}

