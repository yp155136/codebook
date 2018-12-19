#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int l[613456],r[613456],w[613456];
vector<pii> sagiri[613456];
int dp[812464];
const int INF = (1<<29);
//need a range min segment tree!!!
int main (){
    int T;
    scanf("%d",&T);
    while (T--) {
        int n;
        scanf("%d",&n);
        vector<int> v;
        for (int i=1;n>=i;i++) {
            scanf("%d %d %d",&l[i],&r[i],&w[i]);
            //++l[i];
            v.push_back(l[i]);
            v.push_back(r[i]);
        }
        sort(v.begin(),v.end());
        v.resize(unique(v.begin(),v.end()) - v.begin());
        for (int i=1;n>=i;i++){
            l[i] = lower_bound(v.begin(),v.end(),l[i]) - v.begin() + 1;
            r[i] = lower_bound(v.begin(),v.end(),r[i]) - v.begin() + 1;
        }
        int nn = v.size();
        for (int i=1;n>=i;i++) {
            sagiri[ r[i] ].push_back( make_pair(l[i],w[i]) );
        }
        priority_queue<pii,vector<pii>,greater<pii> > pq;
        Node* root = Build(1,nn);
        for (int i=1;nn>=i;i++){
            if (sagiri[i].size() == 0)  {
                dp[i] = dp[i-1];
            }
            else {
                for (pii p:sagiri[i]) {
                    int l = p.first;
                    int r = i;
                    int w = p.second;
                    while (pq.size() && pq.top().second <= l) pq.pop();
                    pq.push(make_pair(query(root,1,nn,l,r-1) + w,r));
                }
                dp[i] = pq.top().first;
            }
            modify(root,1,nn,i,dp[i]);
        }
        for (int i=1;n>=i;i++){
            sagiri[ r[i] ].clear();
        }
        printf("%d\n",dp[nn]);
    }
}
