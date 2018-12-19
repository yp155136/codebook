#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 100006;

int lc[N],rc[N];
int val[N];

bool used[N];

struct Sagiri
{
    int b,e,cost;
    Sagiri(){}
    Sagiri(int _b,int _e,int _cost) : b(_b),e(_e),cost(_cost){}
};

bool operator<(const Sagiri &s1,const Sagiri &s2)
{
    return s1.cost > s2.cost;
}

bool operator>(const Sagiri &s1,const Sagiri &s2)
{
    return s1.cost < s2.cost;
}

int dis[N];

int main ()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for (int i=1;n>=i;i++)
    {
        lc[i] = i-1;
        rc[i] = i+1;
    }
    priority_queue<Sagiri,vector<Sagiri> > pq;
    for (int i=1;n>=i;i++)
    {
        scanf("%d",&val[i]);
        //dis[i] --> i and i-1
        dis[i] = val[i] - val[i-1];
        if (i > 1)
        {
            int _ = val[i] - val[i-1];
            pq.push(Sagiri(i-1,i,_));
        }
    }
    int ans=0;
    while (!pq.empty() && k)
    {
        Sagiri s = pq.top();
        pq.pop();
        if (used[s.b] || used[s.e]) continue;
        //cout << "s = ( " << s.b << " , " << s.e << " , " <<s.cost << " ) " <<endl;
        --k;
        ans += s.cost;
        used[s.b] = used[s.e] = true;
        int bb = lc[s.b],ee = rc[s.e];
        rc[bb] = ee;
        lc[ee] = bb;
        dis[ee] = dis[ee] + dis[s.b] - dis[s.e];
        if (bb >= 1 && ee <= n && (!used[bb] && !used[ee]))
        {
            pq.push(Sagiri(bb,ee,dis[ee]));
        }
    }
    printf("%d\n",ans);
}
