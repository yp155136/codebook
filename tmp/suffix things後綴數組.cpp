#include <iostream>
#include <stdio.h>
#include <cstring>
#include <numeric>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 1e5 + 6;

bool not_equ(int *ra,int a,int b,int k,int n) {
	return ra[a]!=ra[b] || a+k>=n || b+k>=n || ra[a+k]!=ra[b+k];
}

void radix(int *box,int *key,int *it,int *ot,int m,int n) {
	fill_n(box,m,0);
	for(int i=0;n>i;i++) box[key[i]]++;
	partial_sum(box,box+m,box);
	for (int i=n-1;i>=0;i--) {
		ot[--box[key[it[i]]]] = it[i];
	}
}

void make_sa(int *sa,int *ra,const char *s,int n) {
	static int box[MAX_N],tp[MAX_N];
	copy_n(s,n,ra);
	int k=1,m=256;
	do {
		iota(tp,tp+k,n-k);
		iota(sa+k,sa+n,0);
		radix(box,ra+k,sa+k,tp+k,m,n-k);
		radix(box,ra+0,tp+0,sa+0,m,n-0);
		tp[sa[0]]=0,m=1;
		for(int i=1;n>i;i++) {
			m += not_equ(ra,sa[i],sa[i-1],k,n);
			tp[sa[i]]=m-1;
		}
		copy_n(tp,n,ra);
		k *= 2;
	} while (k<n && m!=n);
}

void make_hei(int* hei,int *sa,int *ra,const char *s,int n) {
	for(int j=0,k=0;n>j;j++) {
		if (ra[j]) {
			for (;s[j+k] == s[sa[ra[j]-1] + k];k++);
		}
		hei[ra[j]] = k;
		k = max(0,k-1);
	}
}

char s[MAX_N];
int ra[MAX_N],sa[MAX_N],hei[MAX_N];
