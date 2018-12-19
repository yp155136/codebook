#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#pragma GCC diagnostic ignored "-W"

#include <bits/stdc++.h>
mt19937 rng(0x5EED);
int randint(int lb, int ub)
{ return uniform_int_distribution<int>(lb, ub)(rng); }

#define SECs (clock() / CLOCKS_PER_SEC)

struct KeyHasher {
	size_t operator()(const Key& k) const {
		return k.first + k.second * 100000;
	}
};
typedef unordered_map<Key,int,KeyHasher> map_t;

/*
int __builtin_clz (unsigned int x):
Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

Built-in Function: int __builtin_popcount (unsigned int x):
Returns the number of 1-bits in x.
*/

/*increase stack*/

const int size = 256 << 20;
register long rsp asm("rsp");
char *p = (char*)malloc(size) + size, *bak = (char*)rsp;
__asm__("movq %0, %%rsp\n"::"r"(p));
// main
__asm__("movq %0, %%rsp\n"::"r"(bak));

/*
# Pick's theorem
$A=i+\frac{b}{2}-1$

# Laplacian matrix
$L = D - A$

# Extended Catalan number
$\frac{1}{(k-1)n+1} {kn\choose n}$
*/