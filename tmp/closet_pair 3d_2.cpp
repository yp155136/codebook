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

bool cmp4(const int &a,const int &b)
{
    return _2(y[a]) + _2(z[a]) < _2(y[b]) + _2(z[b]);
}

const int C = 153;
const int F = 7;

int v[N];
int ret[N];

void solve_3(int L,int R)
{
    if (R-L+1 <= C)
    {
        for (int i=L;R>=i;i++)
        {
            for (int j=i+1;R>=j;j++)
            {
                update(v[i],v[j]);
            }
        }
        return;
    }
    int mid = (L+R)>>1;
    solve_3(L,mid);
    solve_3(mid+1,R);
    //vector<int> ret;
    int sz=0;
    for (int i=mid;i>=L;i--)
    {
        if (_2(x[ v[mid] ] - x[ v[i] ]) <= mn_dis) ret[sz++] = v[i]; //ret.push_back(v[i]);
        else break;
    }
    for (int i=mid+1;R>=i;i++)
    {
        if (_2(x[ v[i] ] - x[ v[mid+1] ]) <= mn_dis) ret[sz++] = v[i];  //ret.push_back(v[i]);
        else break;
    }
    sort(ret,ret+sz,cmp4);
    //sort(ret.begin(),ret.end(),cmp4);
    for (int i=0;sz>i;i++)
    {
        for (int j=i+1;min(sz,i + F) >j;j++)
        {
            update(ret[i],ret[j]);
        }
    }
    //sort(ret.begin(),ret.end(),cmp2);
    //solve_2(ret);
}

inline LL rit(){
    LL f=0,key=1;
    char c;
    do{
        c=getchar_unlocked();
        if(c=='-') key=-1;
    }while(c<'0' || c>'9');
    do{
        f=f*10+c-'0';
        c=getchar_unlocked();
    }while(c>='0' && c<='9');
    return f*key;
}

int main ()
{
    mn_dis = (1LL<<62);
    mn_dis *= 2;
    mn_dis += (1LL<<62);
    int n;
    n = rit();
    for (int i=1;n>=i;i++)
    {
        v[i] = i;
        x[i] = rit();
        y[i] = rit();
        z[i] = rit();
    }
    sort(v+1,v+n+1,cmp1);
    solve_3(1,n);
    printf("%llu\n",mn_dis);
}
