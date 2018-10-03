## Graph Matching (tutte) ##
#define MAX 400
#define P 1000000007
typedef long long i64;
int mat[MAX][MAX];
i64 tutte[MAX][MAX];
inline int randInt(int n) {
  return ((rand() << 15) ^ rand()) % n;
}
int matRank(i64 a[MAX][MAX], int n, i64 p) {
  int i, j, k, cnt = 0, cur;
  i64 t;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      while (a[j][i]) {
        for (t = a[i][i] / a[j][i], k = 0; k < n; ++k) {
          a[i][k] = (a[i][k] - a[j][k] * t) % p;
          swap(a[i][k], a[j][k]);
        }
      }
    }
    for (cur = 0, j = i; j < n; ++j) {
      if (a[i][j]) { cur = 1; }
    }
    cnt += cur;
  }
  return cnt;
}
int maxMatch(const int mat[MAX][MAX], int n) {
  int i, j;
  memset(tutte, 0, sizeof(tutte));
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (mat[i][j]) { tutte[j][i] = -(tutte[i][j] = randInt(P)); }
    }
  }
  return matRank(tutte, n, P) >> 1;
}
