#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*262144;
typedef long double ld;
typedef complex<ld> cplx;
const ld PI = acos(-1);
const cplx I(0,1);
cplx omega[MAXN+1];
void pre_fft() {
	for (int i=0;i<=MAXN;i++) {
		omega[i] = exp(i*2*PI/MAXN*I);
	}
}
void fft(int n,cplx a[],bool inv=false) {
	int basic=MAXN/n;
	int theta=basic;
	for (int m=n;m>=2;m>>=1) {
		int mh=m>>1;
		for (int i=0;i<mh;i++) {
			cplx w=omega[inv?MAXN-(i*theta%MAXN):i*theta%MAXN];
			for (int j=i;j<n;j+=m) {
				int k=j+mh;
				cplx x=a[j]-a[k];
				a[j] += a[k];
				a[k] = w*x;
			}
		}
		theta = (theta*2)%MAXN;
	}
	int i=0;
	for (int j=1;j<n-1;j++) {
		for (int k=n>>1;k>(i^=k);k>>=1) ;
		if (j<i) swap(a[i],a[j]);
	}
	if (inv) {
		for (int i=0;i<n;i++) a[i]/=n;
	}
}
cplx a[MAXN],b[MAXN],c[MAXN];
//how to use : 
/*
pre_fft();
fft(n,a);
fft(n,b);
for (int i=0;n>i;i++) {
	c[i] = a[i]*b[i];
}
fft(n,c,1);
*/
