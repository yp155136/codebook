#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

const int MAX_N = 1e5 + 6;

void make_Z(int *z,const char *s) {   //or make_Z(int *z,string s) 
	int len=strlen(s);
	z[0]=0;
	int L,R;
	L=R=0;
	for (int i=1;len>i;i++) {
		if (i>R) z[i] = 0;
		else {
			int ip=i-L;
			if(i + z[ip] < z[L]) z[i] = z[ip];
			else z[i] = R-i+1;
		}
		while (i+z[i]<len && s[i+z[i]] == s[z[i]]) z[i]++;
		if (i+z[i]-1>R) {
			L=i;
			R=i+z[i]-1;
		}
	}
}
