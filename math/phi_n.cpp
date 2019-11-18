#define MEM1(a) memset( (a) , 0 , sizeof( (a) ) );
const int N = 320000 + 6;
const int C = 10005;
const int D = 306;
LL pi_form[N];
LL phi_form[C][D];
LL p2_form[C][D];
LL p[N];
bool prime[N];
void init() {
    MEM1(phi_form);
    MEM1(p2_form);
    prime[0] = prime[1] = 1;
    int id=1;
    for (int i=2;N>i;i++) {
        if (!prime[i]) {
            for (LL j=i*1LL*i;N>j;j+=i) prime[j] = 1;
            p[id++] = i;
        }
        pi_form[i] = pi_form[i-1] + (!prime[i]);
    }
}
LL pi(LL m);
LL p2(LL m,LL n) {
    //cout<<"p2 = "<<p2_form[m][n]<<endl;
    if (m<C && n<D && p2_form[m][n] != -1) return p2_form[m][n];
    if (p[n] == 0) return 0;
    LL ret = 0, tmp=sqrt(m);
    for (LL i=n+1;p[i] <= tmp;i++) ret += pi(m/p[i]) - pi(p[i]) + 1;
    if (m < C && n < D) p2_form[m][n] = ret;
    return ret;
}
LL phi2(LL m,LL n) {
    if (m < C && n < D && phi_form[m][n] != -1) return phi_form[m][n];
    if (!n) return m;
    if (p[n] >= m) return 1;
    if (m<C && n<D) return phi_form[m][n] =  phi2(m,n-1) - phi2(m/p[n],n-1);
    return phi2(m,n-1) - phi2(m/p[n],n-1);
}
LL pi(LL m) {
    if (m < N) return pi_form[m];
    else {
        LL n=ceil(cbrt(m));
        return phi2(m,n) + n - 1 - p2(m,n);
    }
}
//init(); cin >> n; cout << pi(n); (n <= 10^11)
```
