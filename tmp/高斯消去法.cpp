#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
using namespace std;

const double eps = 1e-9;

bool is_0(double x) {
	return abs(x)<=eps;
}

bool is_1(double x) {
	return abs(x-1)<=eps;
}

double a[1006][36];
int m,n;

void sagiri() {
	int nn=min(n,m);
	for (int i=0;nn>i;i++) {
		int pivot=i;
		for (int ii=i;nn>ii;ii++) {
			if (!is_0(a[ii][i])) {
				for (int j=0;m>=j;j++) {
					swap(a[ii][j],a[i][j]);
				}
				break;
			}
		}
		assert(!is_0(a[i][i]));
		double val=a[i][i];
		for (int j=i;m>=j;j++) {
			a[i][j] /= val;
		}
		for (int ii=0;n>ii;ii++) {
			if (i != ii) {
				double val2=a[ii][i]/a[i][i];
				for (int j=0;m>=j;j++) {
					a[ii][j] -= val2*a[i][j];
				}
			}
		}
		assert(is_1(a[i][i]));
	}
}

int main () {
	//m --> 未知數
	//n --> 運算式數量
	//in usual, n==m 
	cin >> m >> n;
	for (int i=0;n>i;i++) {
		for (int j=0;m>j;j++) {
			cin >> a[i][j];
		}
	}
	for (int i=0;n>i;i++) {
		cin >>a[i][m];
	}
	sagiri();
	for (int i=0;min(n,m)>i;i++) {
		if (i) cout<<' ';
		cout<<int(a[i][m]+2*eps);
	}
	cout<<endl;
}

