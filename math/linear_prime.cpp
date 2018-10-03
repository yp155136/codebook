int dv[MAX] , p[MAX] , po = 0;
void getprime(){
    REP(i , 2 , MAX){
        if(dv[i] == 0) dv[i] = i , p[po ++] = i;
        REP(j , 0 , po){
            if(i * p[j] >= MAX) break;
            dv[i * p[j]] = p[j];
            if(i % p[j] == 0) break;
        }
    }
}
