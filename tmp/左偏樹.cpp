
int merge(int x, int y) {
  if (T[x].v > T[y].v || (T[x].v == T[y].v && x > y)) swap(x, y);
  if (!x) return y;
  int &l = T[x].l, &r = T[x].r;
  r = merge(r, y);
  if (T[l].dis < T[r].dis) swap(l, r);
  T[x].dis = T[r].dis + 1;
  return x;
}

