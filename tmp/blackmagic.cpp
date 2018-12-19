//PBDS tree

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
tree<pair<int64_t, int>, null_type, less<pair<int64_t, int> >, rb_tree_tag, tree_order_statistics_node_update> st;
st.order_of_key(...), st.find_by_order(...);

//## PBDS Paring Heap ##

#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<int, cmp, pairing_heap_tag> heap;
hp.join(...), hp.modify(it, ...), hp.erase(it);


//## Rope ##

#include <ext/rope>
using namespace __gnu_cxx;
rope<char> *r[MAXN];
r[t] = new rope<char>(*r[t - 1]);
r[t]->insert(p, ch), r[t]->erase(p, cnt), r[v]->at(i);

//## Anti Stack Overflow ##

int size = 256 << 20; // 256MB
register long rsp asm("rsp");
char *_p = (char*)malloc(size) + size, *_bak = (char*)rsp;
__asm__("movq %0, %%rsp\n" :: "r"(_p));
__asm__("movq %0, %%rsp\n" :: "r"(_bak));


//## Pragma Optimization ##

#pragma GCC optimize("Ofast","no-stack-protector","no-math-errno")
#pragma GCC target("avx2","tune=native", "arch=core-avx2")
#pragma GCC ivdep


