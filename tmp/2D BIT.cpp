#include <iostream>
#include <cstring>
using namespace std;

struct BIT_2D {
    static const int MAX_N = 2506;
    int bit[MAX_N][MAX_N];
    int n,m;
    void init(int n,int m) {
        this->n = n;
        this->m = m;
        memset(bit,0,sizeof(bit));
    }
    void add(int x,int y,int w) {
        for (int i=1;x>=i;i+=i&(-i)) {
            for (int j=1;y>=j;j+=(j&(-j))) {
                bit[i][j] += w;
            }
        }
    }
    int qry(int x,int y) {
        int ret=0;
        for (int i=x;i>=1;i-=i&(-i)) {
            for (int j=y;j>=1;j-=j&(-j)) {
                ret += bit[i][j];
            }
        }
        return ret;
    }
};
