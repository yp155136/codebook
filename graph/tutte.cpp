int mxmat(const int mat[MAX][MAX], int n) {
    ll tutte[n][n];
    memset(tutte, 0, sizeof(tutte));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (mat[i][j]) tutte[j][i] = -(tutte[i][j] = rdi());
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j)
            while (tutte[j][i]) {
                ll t = tutte[i][i] / tutte[j][i];
                for (int k = 0; k < n; ++k) {
                    tutte[i][k] = (tutte[i][k] - tutte[j][k] * t) % MOD;
                    swap(tutte[i][k], tutte[j][k]);
                }
            }
        if(tutte[i][i]) cnt++;
    }
    return cnt>>1;
}
