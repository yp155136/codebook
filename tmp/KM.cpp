int N, now_time;
__int128 slack[MAX_N];
ll X[MAX_N] , Y[MAX_N];
__int128 W[MAX_N][MAX_N];
int mx[MAX_N] , my[MAX_N];
int vx[MAX_N] , vy[MAX_N];
__int128 lx[MAX_N] , ly[MAX_N];
bool dfs(int x) {
 vx[x] = now_time;
 REP1(y , 1 , N) {
  if(vy[y] == now_time) continue;
  __int128 t = lx[x] + ly[y] - W[x][y];
  if(t == 0) {
   vy[y] = now_time;
   if(!my[y] || dfs(my[y])) {
    mx[x] = y;
    my[y] = x;
    return 1;
   }
  }
  else slack[y] = min(slack[y] , t);
 }
 return 0;
}
inline void modify() {
 __int128 t = INF128;
 REP1(y , 1 , N) if(vy[y] != now_time) t = min(t , slack[y]);
 REP1(x , 1 ,N) if(vx[x] == now_time) lx[x] -= t;
 REP1(y , 1 , N) if(vy[y] == now_time) ly[y] += t;
}
inline pair<bool,__int128> km() {
 REP1(x , 1 , N) {
  lx[x] = -INF128;
  REP1(y , 1 , N) lx[x] = max(lx[x] , W[x][y]);
 }
 REP1(y , 1 , N) ly[y] = 0;
 now_time = 0;
 REP1(x , 1 , N) vx[x] = 0 , mx[x] = 0;
 REP1(y , 1 , N) vy[y] = 0 , my[y] = 0;
 REP1(x , 1 , N) {
  while(1) {
   now_time++;
   REP1(y , 1 , N) slack[y] = INF128;
   if(dfs(x)) break;
   else modify();
  }
 }
 __int128 ans = 0;
 REP1(x , 1 , N) {
  if(W[x][mx[x]] == -INF128) return MP(0 , __int128(0));
  else ans -= W[x][mx[x]];
 }
 return MP(1 , ans);
}
