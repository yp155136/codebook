#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5 + 5;
const int MM = 'A' + 'B';
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> pii;
#define eb emplace_back
#define S second
#define F first
vector<int> adj[MAX];
vector<int> rev[MAX];
int arr[MAX][6], n, m;
int cnt[MAX][6];
string s1, s2, s3;
void dfs(int now, int t) {
    // cout << now << ' ' << t << '\n';
    int tp = s3[t];
    int pp = (t + 5) % 6;
    int tr = s3[(t + 5) % 6];
    if(tr == arr[now][t]) {
        for(int i : rev[now]) {
            if(arr[i][pp])  continue; 
            arr[i][pp] = tr;
            dfs(i, pp);
        }
    }
    else {
        for(int i : rev[now]) {
            if(arr[i][pp])  continue;
            cnt[i][pp] ++ ;
            if(adj[i].size() == cnt[i][pp]) {
                arr[i][pp] = arr[now][t];
                dfs(i, pp);
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);   cin.tie(0);
    int T;
    cin >> T;
    while(T --) {
        memset(arr, 0, sizeof arr);
        memset(cnt, 0, sizeof cnt);
        cin >> n >> m;
        for(int i = 1; i <= n; ++ i ) {
            adj[i].clear();
            rev[i].clear();
        }
        for(int j = 0; j < m; ++ j) {
            int u, v;   cin >> u >> v;
            adj[u].eb(v);
            rev[v].eb(u);
        }
        cin >> s1 >> s2;
        s3 = s1;
        for(int i = 0; i < 6; ++ i) {
            if(s2[i] == '1'){
                if(s3[i] == 'A')    s3[i] = 'B';
                else                s3[i] = 'A';
            }
        }
        for(int i = 0; i < 6; ++ i) {
            for(int j = 1; j <= n; ++j ){
                if(adj[j].size() == 0) {
                    arr[j][i] = MM - s1[i];
                    dfs(j, i);
                }
            }
        }
        for(int i = 1; i <= n; ++ i) {
            if(arr[i][0])   cout << (char)arr[i][0];
            else            cout << 'D';
            // for(int j = 0; j < 6; ++ j) {
            //     cout << (char)arr[i][j] ;
            // }
        }
            cout << '\n';
    }

    return 0;
}
