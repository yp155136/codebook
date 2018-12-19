#include <bits/stdc++.h>
using namespace std;

const int N = 1000006;

double x[N],y[N];

double ans;

void update(int i,int j)
{
    ans = min(ans,sqrt(pow(x[i]+0LL-x[j],2) + pow(y[i]+0LL-y[j],2)) );
}

#define SZ(x) ((int)(x).size())

void solve(vector<int> v)
{
    if (SZ(v) <= 100)
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
    int mid=SZ(v)/2;
    vector<int> lc,rc;
    for (int i=0;SZ(v)>i;i++)
    {
        if (i <= mid) lc.push_back(v[i]);
        else rc.push_back(v[i]);
    }
    solve(lc);
    solve(rc);
    vector<int> vv;
    for (int i:lc)
    {
        if (abs(x[i]-x[ v[mid] ]) <= ans+1e-9) vv.push_back(i);
    }
    for (int i:rc)
    {
        if (abs(x[i]-x[ v[mid+1] ]) <= ans + 1e-9) vv.push_back(i);
    }
    sort(vv.begin(),vv.end(),[](const int &a,const int &b)
         {
             return y[a]<y[b];
         });
    for (int i=0;SZ(v)>i;i++)
    {
        int cnt=10;
        for (int j=i+1;SZ(v)>j;j++)
        {
            --cnt;
            update(v[i],v[j]);
            if (!cnt) break;
        }
    }
}

int main ()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n)
    {
        if (!n) break;
        vector<int> v;
        for (int i=1;n>=i;i++)
        {
            cin >> x[i] >> y[i];
            v.push_back(i);
        }
        sort(v.begin(),v.end(),[](const int &a,const int &b)
             {
                 return x[a] < x[b];
             });
        ans = 1e100;
        solve(v);
        cout << fixed << setprecision(3) << ans << endl;

    }
}
