## Gauss Elimination ##
```cpp
typedef double Matrix[maxn][maxn];
void gauss_elimination(Matrix A, int n) {
  int i, j, k, r;
  for (i = 0; i < n; i++) {
    r = i;
    for (j = i + 1; j < n; j++)
      if (fabs(A[j][i]) > fabs(A[r][i])) { r = j; }
    if (r != i) for (j = 0; j <= n; j++) { swap(A[r][j], A[i][j]); }
#define High_precision
#ifndef High_precision
    for (k = i + 1; k < n; k++) {
      DB f = A[k][i] / A[i][i];
      for (j = i; j <= n; j++) { A[k][j] -= f * A[i][j]; }
    }
#else
    for (j = n; j >= i; j--)
      for (k = i + 1; k < n; k++) {
        A[k][j] -= A[k][i] / A[i][i] * A[i][j];
      }
#endif
  }
  for (i = n - 1; i >= 0; i--) {
    for (j = i + 1; j < n; j++) { A[i][n] -= A[j][n] * A[i][j]; }
    A[i][n] /= A[i][j];
  }
}
```
