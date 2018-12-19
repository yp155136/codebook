#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2e7 + 6;

bool p[N];

int main ()
{
    p[0] = p[1] = 1;
    for (int i=2;N>i;i++)
    {
        if (!p[i])
        {
            for (LL j=i*1LL*i;N>j;j+=i)
            {
                p[j] = 1;
            }
        }
    }
    int x;
    while (scanf("%d",&x) != EOF)
    {
        if (x < N)
        {
            if (p[x]) puts("獶借计");
            else puts("借计");
        }
        else
        {
            LL tmp=sqrt(x);
            if (!(x&1)) puts("獶借计");
            else {
                bool check=false;
                for (int i=3;i*1LL*i<x;i+=2)
                {
                    if (x%i ==0)
                    {
                        check=true;
                        break;
                    }
                }
                if (check) puts("獶借计");
                else puts("借计");
            }
        }
    }
}
