static inline char getRawChar() {
  static char buf[1 << 16], *p = buf, *end = buf;
  if (p == end) {
    if ((end = buf + fread_unlocked(buf, 1, 1 << 16, stdin)) == buf) return '\0';
    p = buf;
  }
  return *p++;
}
while (c = getRawChar() && (unsigned)(c - '0') > 10U) n = n * 10 + (c - '0');

