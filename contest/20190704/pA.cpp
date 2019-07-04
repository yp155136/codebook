#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main () {
    int n;
    int cases = 0;
    while (scanf("%d", &n) != EOF) {
        printf("Case #%d: ",++cases);
        if (n == 1) puts("0");
        else printf("%d\n", (int)(log(2) / log(10) * n));
    }
}

