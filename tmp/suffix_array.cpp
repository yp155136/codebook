//## Suffix Array ##
//```cpp
struct SuffixArray {
  char s[maxn];
  int sa[maxn], rank[maxn], pri[maxn], c[maxn], n;
  void build_sa(int m) {
    n = strlen(s);
    s[n++] = 0;
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++) { c[rank[i] = s[i]]++; }
    for (int i = 1; i < m; i++) { c[i] += c[i - 1]; }
    for (int i = n - 1; i >= 0; i--) { sa[--c[rank[i]]] = i; }
    for (int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for (int i = n - k; i < n; i++) { pri[p++] = i; }
      for (int i = 0; i < n; i++) if (sa[i] >= k) { pri[p++] = sa[i] - k; }
      memset(c, 0, sizeof(c));
      for (int i = 0; i < n; i++) { c[rank[pri[i]]]++; }
      for (int i = 1; i < m; i++) { c[i] += c[i - 1]; }
      for (int i = n - 1; i >= 0; i--) { sa[--c[rank[pri[i]]]] = pri[i]; }
      swap(pri, rank);
      p = 1;
      rank[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        rank[sa[i]] = pri[sa[i - 1]] == pri[sa[i]] &&
          pri[sa[i - 1] + k] == pri[sa[i] + k] ? p - 1 : p++;
      }
      if (p >= n) { break; }
      m = p;
    }
  }
  int m;
  int cmp_suffix(char *pattern, int p) {
    return strncmp(pattern, s + sa[p], m);
  }
  int find(char *p) {
    m = strlen(p);
    if (cmp_suffix(p, 0) < 0) { return -1; }
    if (cmp_suffix(p, n - 1) > 0) { return -1; }
    int l = 0, r = n - 1;
    while (r >= l) {
      int mid = l + (r - l) / 2;
      int res = cmp_suffix(p, mid);
      if (!res) { return mid; }
      if (res < 0) { r = mid - 1; }
      else { l = mid + 1; }
    }
    return -1;
  }
  int height[maxn];
  void getheight() {
    int k = 0;
    for (int i = 1; i < n; i++) { rank[sa[i]] = i; }
    for (int i = 0; i < n - 1; i++) {
      if (k) { k--; }
      int j = sa[rank[i] - 1];
      while (s[i + k] == s[j + k]) { k++; }
      height[rank[i]] = k;
    }
  }
} SA;
//```
