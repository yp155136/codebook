#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> piii;

struct Sparse_Table {
	static const int MAX_N = 2e5 + 6;
	static const int MAX_P = __lg(MAX_N)+1;
	int st[MAX_P][MAX_N];
	int lg2[MAX_N];
	int pow2[MAX_P];
	int n;
	//starting from 1 ~ n
	vector<int> a;
	void init(int _n,vector<int> &_a) {
		n=_n;
		for (int i:_a) a.push_back(i);
		lg2[1] = 0;
		for (int i=2;MAX_N>i;i++) lg2[i] = lg2[i/2]+1;
		pow2[0]=1;
		for (int i=1;MAX_P>i;i++) pow2[i] = pow2[i-1] * 2;
		for (int i=1;n>=i;i++) {
			st[0][i] = a[i];
		}
		for (int i=1;MAX_P>i;i++) {
			for (int j=1;n>=j;j++) {
				int r=j+pow2[i-1];
				if (r>n) r=n;
				st[i][j] = min(st[i-1][j],st[i-1][r]);
			}
		}
	}
	int query(int l,int r) {
		int dis=(r-l+1);
		return min(st[lg2[dis]][l],st[lg2[dis]][r-pow2[lg2[dis]]+1]);
	}
	
}
