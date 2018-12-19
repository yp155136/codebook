#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*262144;
typedef long double ld;
#define ld double
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
int d[MAXN];

int main () {
	int T;
	scanf("%d",&T);
	while (T--) {
		int n;
		scanf("%d",&n);
		int tmp=MAXN/2;
		for (int i=0;tmp>=i;i++) {
			a[i]=cplx(0,0);
			b[i]=cplx(0,0);
		}
		cplx ala=cplx(1,0);
		int m=n;
		for (int i=1;n>=i;i++) {
			int x;
			scanf("%d",&x);
			d[i]=x;
		}
		int mn=0,mx=0;
		for (int i=1;n>=i;i++) {
			mx= max(mx,d[i]);
			mn=min(mn,d[i]);
		}
		int delta= -mn;
		for (int i=1;n>=i;i++) {
			d[i] += delta;
			int x=d[i];
			a[x] += cplx(ala);
			b[x] += cplx(ala);
		}
		n = 1;
		while ((mx - mn)*2>n) n*=2;
		pre_fft();
		fft(n,a);
		pre_fft();
		fft(n,b);
		for (int i=0;n>i;i++) {
			c[i] = a[i]*b[i];
		}
		pre_fft();
		fft(n,c,1);
		long long ans=0;
		ld eps = 1e-9;
		for (int i=1;m>=i;i++) {
			ans +=( real(c[ d[i]+delta] ) +eps);
		}
//		cout<<ans<<endl;
		printf("%lld\n",ans);
	}
}



