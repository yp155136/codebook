#include <bits/stdc++.h>
using namespace std;

int dp[9][(1<<12)];
const int INF = 40000;

int count_bit(int x) {
    int ret=0;
    while (x) {
        if (x&1) ++ret;
        x>>=1;
    }
    return ret;
}

int mp[11][11];
int dx[8] = {1,1,1,0,0,-1,-1,-1};
int dy[8] = {1,0,-1,1,-1,1,0,-1};

bool okay(int mask,int k,int r,int c,int m,int ii) {
    if (ii == 0) return true;
    memset(mp,-1,sizeof(mp));
    int _ = (mask)|(k<<(2*c));
    for (int i=0;i<3*c;++i) {
        if ((1<<i)&_) {
            int tar = i;
            mp[tar/c+1][tar%c+1] = 1; //mine
        }
        else {
            mp[i/c+1][i%c+1] = 0;
        }
    }
    /*if (ii == 1 && mask == 56) {
        for (int i=0;i<10;++i) {
            for (int j=0;j<10;++j) {
                cout << mp[i][j] << " \n"[j==9];
            }
        }
        exit(0);
    }*/
    int L = 2 , R = 2;
    if (ii <= 1) {
        for (int i=1;i<=c;++i) mp[1][i] = -1;
    }
    if (ii == r-1) {
        for (int i=1;i<=c;++i) mp[3][i] = -1;
    }
    for (int i=L;i<=R;++i) {
        for (int j=1;j<=c;++j) {
            bool okay = false;
            if (mp[i][j] != 1) continue;
            for (int k=0;k<8;++k) {
                int ti = i + dx[k];
                int tj = j + dy[k];
                if (mp[ti][tj] == 0) okay = true;
            }
            if (!okay) return false;
        }
    }
    for (int i=L;i<=R;++i) {
        for (int j=1;j<=c;++j) {
            bool okay = false;
            if (mp[i][j] != 0) continue;
            int cnt=0;
            for (int k=0;k<8;++k) {
                int ti = i + dx[k];
                int tj = j + dy[k];
                if (mp[ti][tj] == 1) ++cnt;
            }
            if (cnt > m) return false;
        }
    }
    return true;
}

int main (int argc,char ** argv) {
    int r = atoi(argv[1]),c = atoi(argv[2]),m = atoi(argv[3]);
    ++r;
    for (int i=0;i<9;++i) {
        for (int j=0;j<(1<<12);++j) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    for (int i=0;i<r;++i) {
        for (int mask=0;mask<(1<<(2*c));++mask) {
            for (int k=0;k<(1<<c);++k) {
                //if (i == 2 && mask == 14 && k == 3) cout << okay(mask,k,r,c,m,i) << endl;
                if (okay(mask,k,r,c,m,i)) {
                    dp[i+1][mask/(1<<c)+k*(1<<c)] = max(dp[i][mask]+count_bit(k),dp[i+1][mask/(1<<c)+k*(1<<c)]);
                }
            }
            //cout << "i = " << i << " , mask = " << mask << " , dp = " << dp[i][mask] << endl;
            
        }
    }
    int ans=0;
    for (int i=0;i<(1<<c);++i) {
        //cout << "i = " << r << " , mask = " << i << " , dp = " << dp[r][i] << endl;
        ans = max(ans,dp[r][i]);
    }
    cout << ans << endl;
}

