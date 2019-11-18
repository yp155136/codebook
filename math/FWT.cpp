void FWT(ll a[],int n){ 
    for(int d = 1 ;d < n; d <<= 1)  // d = half of block size 
        for(int i = 0; i < n; i += d + d) // every block 
            for(int j = i; j < i + d; j++){   //processing 
                ll x = a[j], y = a[j + d]; 
                a[j] = x + y;   a[j + d] = x - y; //FWT XOR
                a[j] = x + y; //FWT AND
                a[j + d] = y + x; //FWT OR
                a[j] = (x + y) / 2;   a[j + d] = (x - y) / 2; //IFWT XOR
                a[j] = x - y; //IFWT AND
                a[j + d] = y - x; //IFWT OR
            }
}
