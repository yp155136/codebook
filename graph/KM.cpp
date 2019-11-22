const int INF = 0x3f3f3f3f;
const int maxn = 610;

int n, w[maxn][maxn], lx[maxn], ly[maxn], slk[maxn];
int s[maxn], t[maxn], good[maxn];

int match(int now) {
    s[now] = 1;
    for (int to = 1; to <= n; to ++) {
        if(t[to]) continue;
        if(lx[now] + ly[to] == w[now][to]) {
            t[to] = 1;
            if(good[to] == 0 || match(good[to]))
                return good[to] = now, 1;
        }
        else slk[to] = min(slk[to], lx[now] + ly[to] - w[now][to]);
    }
    return 0;
}
void update() {
    int val = INF;
    for (int i = 1; i <= n; i ++) 
        if(t[i] == 0) val = min(val, slk[i]);
    for (int i = 1; i <= n; i ++) {
        if(s[i]) lx[i] -= val;
        if(t[i]) ly[i] += val;
    }
}
void run_km() {
    for (int i = 1; i <= n; i ++) {
        lx[i] = w[i][1];
        for (int j = 1; j <= n; j ++)
            lx[i] = max(lx[i], w[i][j]);
    }
    for (int i = 1; i <= n; i ++)
        ly[i] = 0, good[i] = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) slk[j] = INF;
        while(1) {
            for (int j = 1; j <= n; j ++)
                s[j] = t[j] = 0;
            if(match(i)) break;
            else update();
        }
    }
}
/* how_to_use:
1. put edge in w[i][j]
2. run_km
3. match: (good[i], i)
*/
