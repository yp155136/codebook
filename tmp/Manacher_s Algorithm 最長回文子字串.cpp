#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

void longest_palindromic_substring(int *z,char *s) {  //remember z = 4*size
	//s has already put something like '$'
	int n=strlen(s);
	int L=0,R=0;
	z[0]=1;
	for (int i=1;n>i;i++) {
		z[i] = (R>i) ? min(z[2*L-i],R-i) : 1;
		while (i-z[i] >= 0 && i+z[i]<n && s[i-z[i]]==s[i+z[i]]) z[i]++;
		if (i+z[i] > R) L=i,R=i+z[i];
	}
}

