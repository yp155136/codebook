#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> pii;

int l[613456],r[613456],w[613456];

vector<pii> sagiri[613456];

int dp[812464];

const int INF = (1<<29);

struct Node
{
    Node *lc,*rc;
    int mn;
    Node():lc(NULL),rc(NULL),mn(INF){}
    void pull()
    {
        mn = min(lc->mn,rc->mn);
    }
};

Node* Build(int L,int R)
{
    Node* node = new Node();
    if (L==R) return node;
    int mid=(L+R)>>1;
    node->lc=Build(L,mid);
    node->rc=Build(mid+1,R);
    return node;
}

void modify(Node* node,int L,int R,int pos,int val)
{
    if (L==R)
    {
        node->mn = val;
        return;
    }
    int mid=(L+R)>>1;
    if (pos <= mid) modify(node->lc,L,mid,pos,val);
    else modify(node->rc,mid+1,R,pos,val);
    node->pull();
    return;
}

int query(Node* node,int L,int R,int l,int r)
{
    if (l>R || L>r) return INF;
    else if (l<=L && R<=r) return node->mn;
    int mid=(L+R)>>1;
    return min(query(node->lc,L,mid,l,r),query(node->rc,mid+1,R,l,r));
}

int main ()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        vector<int> v;
        for (int i=1;n>=i;i++)
        {
            scanf("%d %d %d",&l[i],&r[i],&w[i]);
            //++l[i];
            v.push_back(l[i]);
            v.push_back(r[i]);
        }
        sort(v.begin(),v.end());
        v.resize(unique(v.begin(),v.end()) - v.begin());
        for (int i=1;n>=i;i++)
        {
            l[i] = lower_bound(v.begin(),v.end(),l[i]) - v.begin() + 1;
            r[i] = lower_bound(v.begin(),v.end(),r[i]) - v.begin() + 1;
        }
        int nn = v.size();
        for (int i=1;n>=i;i++)
        {
            sagiri[ r[i] ].push_back( make_pair(l[i],w[i]) );
        }
        priority_queue<pii,vector<pii>,greater<pii> > pq;
        Node* root = Build(1,nn);
        for (int i=1;nn>=i;i++)
        {
            if (sagiri[i].size() == 0)
            {
                dp[i] = dp[i-1];
            }
            else
            {
                for (pii p:sagiri[i])
                {
                    int l = p.first;
                    int r = i;
                    int w = p.second;
                    while (pq.size() && pq.top().second <= l) pq.pop();
                    pq.push(make_pair(query(root,1,nn,l,r-1) + w,r));
                }
                dp[i] = pq.top().first;
            }
            modify(root,1,nn,i,dp[i]);
            //cout << "i = "<<i<<", dp = "<<dp[i]<<endl;
        }
        for (int i=1;n>=i;i++)
        {
            sagiri[ r[i] ].clear();
        }
        printf("%d\n",dp[nn]);
    }
}
