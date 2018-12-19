#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
const int N = 100006;

LL x[N],y[N],z[N];

#define _2(x) (x)*(x)

ULL get_dis(int i,int j)
{
    ULL ret = _2(x[i] - x[j]) + _2(y[i]-y[j]);
    ret += _2(z[i]-z[j]);
    return ret;
}

ULL mn_dis;

bool update(int i,int j)
{
    if (get_dis(i,j) < mn_dis)
    {
        mn_dis = get_dis(i,j);
        return true;
    }
    return false;
    //mn_dis = min(mn_dis,get_dis(i,j));
}

#define SZ(x) ((int)(x).size())

const int C = 200;

bool cmp1(const int &a,const int &b)
{
    return x[a] < x[b];
}

bool cmp2(const int &a,const int &b)
{
    return y[a] < y[b];
}

bool cmp3(const int &a,const int &b)
{
    return z[a] < z[b];
}

const int D = 120;
const int E = 30;

void solve_2(vector<int> v)
{
    if (SZ(v) <= D)
    {
        for (int i=0;SZ(v)>i;i++)
        {
            for (int j=i+1;SZ(v)>j;j++)
            {
                update(v[i],v[j]);
            }
        }
        return;
    }
    vector<int> lv,rv;
    int mid = SZ(v)/2;
    for (int i=0;mid>=i;i++) lv.push_back(v[i]);
    for (int i=mid+1;SZ(v)>i;i++) rv.push_back(v[i]);
    solve_2(lv);
    solve_2(rv);
    vector<int> ret;
    for (int i=mid;i>=0;i--)
    {
        if (_2(x[ v[mid] ] - x[ v[i] ]) + _2(y[ v[mid] ] - y[ v[i] ]) <= mn_dis) ret.push_back(v[i]);
    }
    for (int i=mid+1;SZ(ret)>i;i++)
    {
        if (_2(x[ v[mid+1] ] - x[ v[i] ]) + _2(y[ v[mid+1] ] - y[ v[i] ]) <= mn_dis) ret.push_back(v[i]);
    }
    sort(ret.begin(),ret.end(),cmp3);
    for (int i=0;SZ(ret)>i;i++)
    {
        for (int j=i+1;min(SZ(ret),(i+E))>j;j++)
        {
            update(ret[i],ret[j]);
        }
    }
    //consider (y,z) only, such that distance is smaller or equal to min_dis
}

void solve_3(vector<int> v)
{
    if (SZ(v) <= C)
    {
        for (int i=0;SZ(v)>i;i++)
        {
            for (int j=i+1;SZ(v)>j;j++)
            {
                update(v[i],v[j]);
            }
        }
        return;
    }
    vector<int> lv,rv;
    int mid = SZ(v)/2;
    for (int i=0;SZ(v)>i;i++)
    {
        if (i <= mid) lv.push_back(v[i]);
        else rv.push_back(v[i]);
    }
    solve_3(lv);
    solve_3(rv);
    vector<int> ret;
    for (int i=mid;i>=0;i--)
    {
        if (_2(x[ v[mid] ] - x[ v[i] ]) <= mn_dis) ret.push_back(v[i]);
        else break;
    }
    for (int i=mid+1;SZ(v)>i;i++)
    {
        if (_2(x[ v[i] ] - x[ v[mid+1] ]) <= mn_dis) ret.push_back(v[i]);
        else break;
    }
    sort(ret.begin(),ret.end(),cmp2);
    solve_2(ret);
}

int main ()
{
    mn_dis = (1LL<<62);
    mn_dis *= 2;
    mn_dis += (1LL<<62);
    int n;
    scanf("%d",&n);
    vector<int> v;
    for (int i=1;n>=i;i++)
    {
        v.push_back(i);
        scanf("%lld %lld %lld",&x[i],&y[i],&z[i]);
    }
    sort(v.begin(),v.end(),cmp1);
    solve_3(v);
    printf("%llu\n",mn_dis);
}
