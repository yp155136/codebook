pii operator*(const pii &p1, const pii &p2) {
    return {subb(mull(p1.F, p2.F) - mull(p1.S, p2.S)), 
            subb(addd(mull(p1.F, p2.S) + mull(p1.S, p2.F)) - mull(p1.S, p2.S))};
}
pii cal1(pii p) {
    return {subb(-p.S), subb(p.F - p.S)};
}
pii cal2(pii p) {
    return {subb(p.S - p.F), subb(-p.F)};
}
//C is the size of a
void DFT(vector<pii> &a) {
    for (int mid = 1; mid < C; mid *= 3) {
        for (int j = 0; j < C; j += mid * 3) {
            for (int k = 0; k < mid; ++k) {
                pii x = a[j + k], y = a[j + k + mid], z = a[j + k + (mid << 1)];
                a[j + k] = x + y + z;
                a[j + k + mid] = x + cal1(y) + cal2(z);
                a[j + k + (mid << 1)] = x + cal2(y) + cal1(z);
            }
        }
    }
}
const int invn = ppow(C, mod - 2);
void IDFT(vector<pii> &a) {
    for (int mid = 1; mid < C; mid *= 3) {
        for (int j = 0; j < C; j += mid * 3) {
            for (int k = 0; k < mid; ++k) {
                pii x = a[j + k], y = a[j + k + mid],
                    z = a[j + k + (mid << 1)];
                a[j + k] = x + y + z;
                a[j + k + mid] = x + cal2(y) + cal1(z);
                a[j + k + (mid << 1)] = x + cal1(y) + cal2(z);
            }
        }
    }
    for (int i = 0; i < C; ++i) {
        a[i].F = mull(a[i].F, invn);
    }
}
void ff(vector<pii> &a, vector<pii> b) {
    DFT(a); DFT(b);
    for (int i = 0; i < C; ++i) {
        a[i] = a[i] * b[i];
    }
    IDFT(a);
}
