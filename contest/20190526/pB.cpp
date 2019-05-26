#include <bits/stdc++.h>
using namespace std;

typedef long double D;
typedef pair<D,D> pdd;
const D eps = 1e-9;
#define F first
#define S second

struct Circle {
    D x,y,r; pdd cen; int S;
    Circle(){}
    Circle(D _x,D _y,D _r,int _s):x(_x),y(_y),r(_r),cen({_x,_y}),S(_s){};
} cir[106];

struct Cir_inter_type {
    int type;
    vector<pdd> pts;
    Cir_inter_type(){}
    Cir_inter_type(int _type,vector<pdd> _pts):type(_type),pts(_pts){}
};

D get_dis(pdd a,pdd b) {
    return sqrt((long double)((a.F-b.F)*(a.F-b.F) + (a.S-b.S)*(a.S-b.S)));
}

bool eq(D a,D b) {
    long double x = a-b;
    return fabs(x) <= eps;
}

bool les(D a,D b) {
    return !eq(a,b) && a<b;
}

bool leq(D a,D b) {
    return les(a,b) || eq(a,b);
}

Cir_inter_type circle_inter(Circle a,Circle b) {
    Cir_inter_type ret;
    D dis = get_dis(a.cen,b.cen);
    if (eq(a.r + b.r,dis)) {
        D x = a.x + (b.x-a.x)*(a.r)/(a.r+b.r);
        D y = a.y + (b.y-a.y)*(a.r)/(a.r+b.r);
        vector<pdd> pts;
        pts.push_back(make_pair(x,y));
        ret = Cir_inter_type(1,pts);
    }
    else if (eq(max(a.r,b.r),min(a.r,b.r) + dis)) {
        if (a.r < b.r) swap(a,b);
        D x = a.x + (b.x - a.x)*a.r/(a.r - b.r);
        D y = a.y + (b.y - a.y)*a.r/(a.r - b.r);
        vector<pdd> pts;
        pts.push_back(make_pair(x,y));
        ret = Cir_inter_type(2,pts);
    }
    else if (les(a.r+b.r,dis)) {
        vector<pdd> pts;
        ret = Cir_inter_type(3,pts);
    }
    else if (les( min(a.r,b.r)+dis,max(a.r,b.r) )) {
        vector<pdd> pts;
        if (les(b.r,a.r)) {
            ret = Cir_inter_type(4,pts);
        }
        else if (les(a.r,b.r)){
            ret = Cir_inter_type(5,pts);
        }
    }
    else if (les(dis,a.r+b.r)) {
        D c1 = 2*(b.x - a.x)*b.r;
        D c2 = 2*(b.y - a.y)*b.r;
        D c3 = a.r*a.r - b.r*b.r - (b.x-a.x)*(b.x-a.x) - (b.y-a.y)*(b.y-a.y);
        D aa = c1*c1 + c2*c2;
        D bb = -2 * c2 * c3;
        D cc = c3*c3 - c1*c1;
        D sin1 = (-bb + sqrtl(bb*bb-4*aa*cc))/(2*aa);
        D sin2 = (-bb - sqrtl(bb*bb-4*aa*cc))/(2*aa);
        D aaa = c1*c1 + c2*c2;
        D bbb = -2*c1*c3;
        D ccc = c3*c3 - c2*c2;
        D cos1 = (-bbb + sqrtl(bbb*bbb-4*aaa*ccc))/(2*aaa);
        D cos2 = (-bbb - sqrtl(bbb*bbb-4*aaa*ccc))/(2*aaa);
        vector<pdd> pts;
        if (eq(sin1*sin1 + cos1*cos1,1.)) {
            pts.push_back(make_pair(b.x + b.r*cos1,b.y + b.r*sin1));
            pts.push_back(make_pair(b.x + b.r*cos2,b.y + b.r*sin2));
        }
        else {
            pts.push_back(make_pair(b.x + b.r*cos1,b.y + b.r*sin2));
            pts.push_back(make_pair(b.x + b.r*cos2,b.y + b.r*sin1));
        }
        ret = Cir_inter_type(6,pts);
    }
    ret.pts.push_back(a.cen);
    ret.pts.push_back(b.cen);
    return ret;
}

int main () {
    int T; cin >> T;
    while (T--) {
        int n,m; cin >> n >> m;
        //D ang = 0/180 * acos(-1);
        long double ang = 71.22/180 * 3.1415926535897932384626433;
        for (int i=1;i<=n;++i) {
            int x,y,z,w; cin >> x >> y >> z >> w;
            D xx = x * cos(ang) - y * sin(ang);
            D yy = x * sin(ang) + y * cos(ang);
            D zz = z;
            //D zz = z - 1e-7;
            cir[i] = Circle(xx,yy,zz,w);
        }
        long long ans = 0;
        for (int i=1;i<=n;++i) {
            for (int j=i;j<=n;++j) {
                Cir_inter_type ret = circle_inter(cir[i],cir[j]);
                for (pdd p:ret.pts) {
                    //cout << fixed << setprecision(12) << "p = " << p.F << " , " << p.S << endl;
                    priority_queue<int> pq;
                    for (int k=1;k<=n;++k) {
                        if (leq(get_dis(p,cir[k].cen),cir[k].r)) {
                            pq.push(cir[k].S);
                        }
                    }
                    int cnt = m;
                    long long tmp=0;
                    while (cnt-- && !pq.empty()) {
                        tmp += pq.top();
                        pq.pop();
                    }
                    ans = max(ans,tmp);
                }
            }
        }
        cout << ans << endl;
    }
}

