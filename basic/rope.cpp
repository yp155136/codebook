#include <ext/rope>
using namespace __gnu_cxx;

rope<int> *p[N],*sz[N];  //use merge by size
int pp[N],szz[N];

int ret = p[ver]->at(x);
p[ver]->replace(x,ret);
p[0] = new rope<int>(pp,pp+n+1);
