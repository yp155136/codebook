struct FWT{
    int n , a[FWT_MAX] , b[FWT_MAX];
    void Fwt(int x[FWT_MAX] , int l , int r){
        if(l == r) return;
        int m = ((l + r) >> 1) + 1;
        Fwt(x , l , m - 1) , Fwt(x , m , r);
        REP(i , 0 , m - l){
            int q = x[l + i] , w = x[m + i];
            x[l + i] = (q + w) % FWT_MOD; // and
            x[m + i] = w % FWT_MOD; // and
 
            x[l + i] = (q + w) % FWT_MOD;//xor
            x[m + i] = (q - w + FWT_MOD) % FWT_MOD;//xor
 
            x[l + i] = q % FWT_MOD;//or
            x[m + i] = (q + w) % FWT_MOD;//or
        }
    }
     void IFwt(int x[FWT_MAX] , int l , int r){
        if(l == r) return;
        int m = ((l + r) >> 1) + 1;
        REP(i , 0 , m - l){
            int q = x[l + i] , w = x[m + i];
            x[l + i] = (q - w + FWT_MOD) % FWT_MOD;//and
            x[m + i] = w % FWT_MOD;//and
 
            x[l + i] = (q + w) * FWT_INV2 % FWT_MOD;//xor
            x[m + i] = (q - w + FWT_MOD) * FWT_INV2 % FWT_MOD;//xor
 
            x[l + i] = q % FWT_MOD;//or
            x[m + i] = (w - q + FWT_MOD) % FWT_MOD;//or
        }
        IFwt(x , l , m - 1) , IFwt(x , m , r);
    }
    void solve(){
        Fwt(a , 0 , n - 1);
        Fwt(b , 0 , n - 1);
        REP(i , 0 , n) a[i] = a[i] * b[i] % FWT_MOD;
        IFwt(a , 0 , n - 1);
    }
};
