#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
 
__gnu_pbds::priority_queue<int> pq;
__gnu_pbds::priority_queue<int>::point_iterator idx[10];
idx[0] = pq.push(1);
 
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> TREE;
TREE name;
*name.find_by_order(0); // 找0 + 1小的元素
name.order_of_key(1);  //if(內部有編號i) return 編號
name.insert(2);
name.delete(3);
name.split(v, b); /// a 裡面 < v 的會被分到 b
name.join(another TREE); // 值域不能重疊
