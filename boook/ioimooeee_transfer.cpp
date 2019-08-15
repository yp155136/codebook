// 0 is 0, 1 can be 1 or 0
for (int i = 0; i < n; ++i)
    for (int j = 0; j < (1 << n); ++j)
        if ( j & (1 << i) ) 
            a[j] += a[ j ^ (1 << i) ];
