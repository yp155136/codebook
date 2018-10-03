#include <bits/stdc++.h>
using namespace std;
//debug
#ifdef grief
#define debug(...) do{\
	fprintf(stderr , "%s - %d : (%s) = " , __PRETTY_FUNCTION__ , __LINE__ , #__VA_ARGS__ );\
	_DO(__VA_ARGS__);\
}while(0)
template<typename I> 				void _DO(I&&x){	cerr<<x<<endl;	}
template<typename I,typename...T>	void _DO(I&&x,T&&...tail){	cerr<<x<<" , ";	_DO(tail...);	}
template<typename _a,typename _b> 	ostream& operator << (ostream &_s,const pair<_a,_b> &_p)
{	return _s<<'('<<_p.first<<','<<_p.second<<')';	}
#define IOS
#else
#define debug(...)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#endif
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef priority_queue<pll,vector<pll>,greater<pll> > heap;
//macro
#define SZ(x) ((LL)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define stp setprecision(18)<<fixed
const LL INF=0x3f3f3f3f3f3f3f3f;
const int NF=0x3f3f3f3f;
const LL MAX=1e5+5,Mlg=__lg(MAX)+2;
const LL MOD=1e9+7;
// ready~ go!
// let's coding and have fun!
// I can't solve this problem!
int main(){
	IOS
	return 0;
}
