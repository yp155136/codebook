
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1002;
const LL INF = (1LL<<41);
const LL INF2 = (1LL<<30);

LL adj[N][N];
LL dp[N][N];  //dp[i][j] --> from point 0 to point j threw i roads

int main()
{
    int n;
    scanf("%d",&n);
    for (int i=0;n+1>=i;i++)
    {
        for (int j=0;n+1>=j;j++)
        {
            dp[i][j] = INF;
        }
    }
    for (int i=1;n>=i;i++)
    {
        for (int j=1;n>=j;j++)
        {
            scanf("%lld",&adj[i][j]);
            if (!adj[i][j]) adj[i][j] = INF;
        }
    }
    for (int i=0;n>=i;i++)
    {
        adj[0][i] = 0;
        adj[i][0] = INF;
        if (i) dp[1][i] = 0;
    }
    for (int i=2;n+1>=i;i++)
    {
        //dp[i][j] --> i roads from 0 to j
        for (int j=0;n>=j;j++)
        {
            for (int k=0;n>=k;k++)
            {
                dp[i][j] = min(dp[i][j],dp[i-1][k] + adj[k][j]);
            }
        }
    }
    LL ansup = INF2, ansdown = 1;
    for (int i=1;n>=i;i++)
    {
        //go threw all possible i's
        LL tmpup = 0,tmpdown = 1;
        if (dp[n+1][i] == INF) continue;
        for (int j=1;n>=j;j++)
        {
            if (dp[j][i] == INF) continue;
            LL up = dp[n+1][i] - dp[j][i];
            LL down = n - j + 1;
            //up/down > tmpup/tmpdown
            if (up >= 0)
            {
                if (up * tmpdown > down * tmpup)
                {
                    tmpup = up;
                    tmpdown = down;
                }
            }
        }
        if (tmpup == 0) continue;
        //ansup/ansdown > tmpup / tmpdown
        if (ansup * tmpdown > ansdown * tmpup)
        {
            ansup = tmpup;
            ansdown = tmpdown;
        }
    }
    LL gcd = __gcd(ansup,ansdown);
    ansup /= gcd;
    ansdown /= gcd;
    if (ansup == INF2) puts("-1 -1");
    else printf("%lld %lld\n",ansup,ansdown);
}

//adj[i][j] --> cost from i to j

