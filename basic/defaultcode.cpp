#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#pragma GCC diagnostic ignored "-W"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub)
{ return uniform_int_distribution<int>(lb, ub)(rng); }

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
(i, factor number of i)
10080      72,   50400      108
110880     144,  221760     168
332640     192,  498960     200
554400     216,  665280     224
720720     240,  1081080    256
2162160    320,  3603600    360
4324320    384,  6486480    400
7207200    432,  8648640    448
10810800   480,  21621600   576
32432400   600,  43243200   672
61261200   720,  73513440   768
110270160  800,  245044800  1008
367567200  1152, 551350800  1200
698377680  1280, 735134400  1344
1102701600 1440, 1396755360 1536
*/
