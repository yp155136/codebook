//## Computational Geometry Misc. ##

#define DB double
const DB PI = acos(-1);
const DB eps = 1e-10;
int dcmp(DB x) {
  if (fabs(x) < eps) { return 0; }
  return x < 0 ? -1 : 1;
}
struct Point {
  DB x, y;
  Point(DB x = 0, DB y = 0): x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);}
Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);}
Vector operator * (Vector A, DB p) {return Vector(A.x * p, A.y * p);}
Vector operator / (Vector A, DB p) {return Vector(A.x / p, A.y / p);}
bool operator < (const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator ==(const Point &a, const Point &b) {
  return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
/// 內積 : 長度 夾角
DB Dot(Vector A, Vector B) {return A.x * B.x + A.y * B.y;}
DB Length(Vector A) {return sqrt(Dot(A, A));}
DB Angle(Vector A, Vector B) {return acos(Dot(A, B) / (Length(A) * Length(B)));}
/// 外積 : 面積
DB Cross(Vector A, Vector B) {return A.x * B.y - B.x * A.y;}
DB Area2(Point A, Point B, Point C) {return Cross(B - A, C - A);}
/// 繞起點逆時針旋轉a度
/// x'=xcosa-ysina , y'=xsina+ycosa
Vector Rotate(Vector A, DB rad) {
  return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
/// 左轉90度->單位法向量
Vector Normal(Vector A) {DB L = Length(A); return Vector(-A.y / L, A.x / L);}
/// 直線交點
/// set two lines are P+tv & Q+tw and Vector u=P-Q ,
/// the parameter of intersection on line 1 is t1 and t2 as on line 2
/// we can solve for t1=Cross(w,u)/Cross(v,w) t2=Cross(v,u)/Cross(v,w)
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
  Vector u = P - Q;
  DB t = Cross(w, u) / Cross(v, w);
  return P + v * t;
}
/// 點P到直線AB距離
DB DistanceToLine(Point P, Point A, Point B) {
  Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2) / Length(v1));
}
/// 點P到線段AB距離
/// set Q the projection point on line AB
/// consider 1.Q on Segment AB 2.Q on ray AB 3.Q on ray BA
DB DistanceToSegment(Point P, Point A, Point B) {
  if (A == B) { return Length(P - A); }
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if (dcmp(Dot(v1, v2)) < 0) { return Length(v2); }
  else if (dcmp(Dot(v1, v3)) < 0) { return Length(v3); }
  else { return fabs(Cross(v1, v2) / Length(v1)); }
}
/// 點P在直線AB上投影
/// set Q=A+t0*v v=B-A, we have Dot(AB,QP)=0
/// so Dot(v,P-(A+t0*v)=0 solve for Dot(v,AP)-t0*Dot(v,v)=0
/// so t0=Dot(v,AP)/Dot(v,v)
Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B - A;
  return A + v * (Dot(v, P - A) / Dot(v, v));
}
/// 線段相交判斷
/// define "Proper intersection" only one intersection point and is not the Endpoints
/// of both Segments
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
  DB c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
  DB c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
/// 點在線段上判斷
bool OnSegment(Point p, Point a1, Point a2) {
  return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
/// 多邊形面積(凹凸皆可)
DB PolygonArea(Point *p, int n) {
  DB area = 0;
  for (int i = 1; i < n - 1; i++) { area += Cross(p[i] - p[0], p[i + 1] - p[0]); }
  return area / 2;
}
///!!!!!Another way to implement Vector!!!!!///
///  #include<complex>
///  using namespace std;
///  typedef complex<DB> Point;
///  typedef Point Vector;
///  real(p)->x imag(p)->y conj(a+bi)-> a-bi
///  double Dot(Vector A,Vector B) {return real(conj(A)*B);}
///  double Cross(Vector A,Vector B) {return imag(conj(A)*B);}
///  Vector Rotate(Vector A, DB rad) {return A*exp(Point(0,rad));}

/// 凸包(Andrew's algorithm)
/// 點陣列p 個數n 輸出點陣列ch 回傳凸包頂點數
/// 輸入不可有重複點
int ConvexHull(Point *p, int n, Point *ch) {
  sort(p, p + n);
  int m = 0;
  for (int i = 0; i < n; i++) {
    while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) { m--; }
    ch[m++] = p[i];
  }
  int k = m;
  for (int i = n - 2; i >= 0; i--) {
    while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) { m--; }
    ch[m++] = p[i];
  }
  if (n > 1) { m--; }
  return m;
}


/// 定義有向直線
struct Line {
  Point P;
  Vector v;
  DB ang;
  Line() {}
  Line(Point P, Vector v): P(P), v(v) {ang = atan2(v.y, v.x);}
  bool operator < (const Line &rhs) const {
    return ang < rhs.ang;
  }
};
/// 半平面交
/// 運用排序、掃描、deque，時間複雜度為O(nlogn)
bool OnLeft(Line L, Point p) {
  return Cross(L.v, p - L.P) > 0;
}
Point GetIntersection(Line a, Line b) {
  Vector u = a.P - b.P;
  DB t = Cross(b.v, u) / Cross(a.v, b.v);
  return a.P + a.v * t;
}
int HalfplaneIntersection(Line *L, int n, Point *poly) {
  sort(L, L + n); /// sort by angle
  int first, last; /// deque pointer
  Point *p = new Point[n]; /// p[i]:intersection of q[i]&q[i+1]
  Line *q = new Line[n]; /// deque
  q[first = last = 0] = L[0]; /// start with L[0]
  for (int i = 1; i < n; i++) {
    while (first < last && !OnLeft(L[i], p[last - 1])) { last--; }
    while (first < last && !OnLeft(L[i], p[first])) { first++; }
    q[++last] = L[i];
    if (dcmp(Cross(q[last].v,
          q[last - 1].v)) == 0) { /// Parallel and in the same direction
      last--;
      if (OnLeft(q[last], L[i].P)) { q[last] = L[i]; }
    }
    if (first < last) { p[last - 1] = GetIntersection(q[last - 1], q[last]); }
  }
  while (first < last && !OnLeft(q[first], p[last - 1])) { last--; } /// delete unwanted plane
  if (last - first <= 1) { return 0; } /// empty set
  p[last] = GetIntersection(q[last], q[first]);
  ///deque->output
  int m = 0;
  for (int i = first; i <= last; i++) { poly[m++] = p[i]; }
  return m;
}

// ## Rotating Caliper ## for area

for (int i = 0; i < n; i++) { cin >> p[i].x >> p[i].y; }
n = convex(n);
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
for (int i = 1; i < n; i++) {
  if (cmp(hull[i].y - hull[p1].y) < 0) { p1 = i; }
  if (cmp(hull[i].y - hull[p2].y) > 0) { p2 = i; }
  if (cmp(hull[i].x - hull[p3].x) < 0) { p3 = i; }
  if (cmp(hull[i].x - hull[p4].x) > 0) { p4 = i; }
}
Vect orig = { 1, 0 }, v1 = { 1, 0 }, v2 = { 0, 1 };
double ansArea = 1E30, ansLen = 1E30;
while (cmp(cross(orig, v1)) >= 0) {
  double d1 = distToLine(hull[p1], hull[p2], hull[p2] + v1),
         d2 = distToLine(hull[p3], hull[p4], hull[p4] + v2);
  ansArea = min(ansArea, d1 * d2);
  ansLen = min(ansLen, 2 * (d1 + d2));
  double minAng = turnAngle(v1, hull[p1 + 1] - hull[p1]);
  minAng = min(minAng, turnAngle(ZERO - v1, hull[p2 + 1] - hull[p2]));
  minAng = min(minAng, turnAngle(ZERO - v2, hull[p3 + 1] - hull[p3]));
  minAng = min(minAng, turnAngle(v2, hull[p4 + 1] - hull[p4]));
  v1 = rotate(v1, minAng), v2 = rotate(v2, minAng);
  if (cmp(angle(v1, hull[p1 + 1] - hull[p1])) == 0) { p1 = (p1 + 1) % n; }
  if (cmp(angle(ZERO - v1, hull[p2 + 1] - hull[p2])) == 0) { p2 = (p2 + 1) % n; }
  if (cmp(angle(ZERO - v2, hull[p3 + 1] - hull[p3])) == 0) { p3 = (p3 + 1) % n; }
  if (cmp(angle(v2, hull[p4 + 1] - hull[p4])) == 0) { p4 = (p4 + 1) % n; }
}

//旋轉卡尺 (距離版)

sort(p,p+n);

int ans=0;
int szu=0,szd=0; //上凸包，下凸包
for (int x=0;n>x;x++) {
  while (szd>1 && cross(d[szd-2]-d[szd-1],d[szd-1]-p[x]) <= 0) szd--;
  while (szu>1 && cross(u[szu-2]-u[szu-1],u[szu-1]-p[x]) >= 0) szu--;
  u[szu++]=p[x];
  d[szd++]=p[x];
}
if (szu>=2) d[szd]=u[szu-2];

for (int i=0,j=szu-1;i<szu && j>0;) {
  ans = max(ans,dis(d[i],u[j]));

  if (cross(d[i]-d[i+1],u[j]-u[j-1]) <= 0) i++;
  else j--;
}
printf("%d\n",ans);

//minimum enclosing circle

typedef long double ld;
const ld eps = 1e-9;

struct P
{
    ld x,y;
    P(){}
    P(ld _x,ld _y) : x(_x),y(_y){}
    void scan()
    {
        cin >> x >> y;
    }
};

P operator+(const P &p1,const P &p2)
{
    return P(p1.x+p2.x,p1.y+p2.y);
}

P operator-(const P &p1,const P &p2)
{
    return P(p1.x-p2.x,p1.y-p2.y);
}

P operator*(const ld &d,const P &p1)
{
    return P(p1.x*d,p1.y*d);
}

P operator*(const P &p1,const ld &d)
{
    return P(p1.x*d,p1.y*d);
}

ld dot(const P &p1,const P &p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

ld cross(const P &p1,const P &p2)
{
    return p1.x*p2.y - p1.y*p2.x;
}

ld dis(const P &p1,const P &p2)
{
    return sqrt(dot(p1-p2,p1-p2));
}

P Rotate(P p)
{
    return P(-p.y,p.x);
}

struct Line
{
    P x,v; //point x which has vector v
    Line() {}
    Line(P _x,P _v) : x(_x),v(_v){}
};

P inter(const Line &l1,const Line &l2)
{
    P p1=l1.x,p2=l1.x+l1.v;
    P q1=l2.x,q2=l2.x+l2.v;
    return p1 + (p2-p1)*(cross(q2-q1,p1-q1)/cross(p2-p1,q2-q1));
}

struct Circle
{
    P p;
    ld r;
    Circle() : p(P()),r(0) {}
    Circle(P _p,ld _r) : p(_p),r(_r) {}
};

bool in_cir(Circle c,P p)
{
    return dis(c.p,p) < c.r + eps;
}

const int N = 100006;

P p[N];
P a[N];

int n,m;

Circle min_cir_cover()
{
    //circles are stored in a[1], a[2], ....., a[n]
    random_shuffle(a+1,a+n+1);
    Circle ans = Circle(P(0,0),0);
    for (int i=1;n>=i;++i)
    {
        if (!in_cir(ans,a[i]))
        {
            ans = Circle(a[i],0);
            for (int j=1;i>j;++j)
            {
                if (!in_cir(ans,a[j]))
                {
                    ans = Circle( (a[i] + a[j])*0.5,dis(a[i],a[j])*0.5 );
                    for (int k=1;j>k;++k)
                    {
                        if (!in_cir(ans,a[k]))
                        {
                            //get circle cover a_i, a_j, a_k
                            Line l1 = Line( (a[i]+a[j])*0.5,Rotate(a[i]-a[j]) );
                            Line l2 = Line( (a[i]+a[k])*0.5,Rotate(a[i]-a[k]) );
                            P tmp = inter(l1,l2);
                            ans = Circle(tmp,dis(tmp,a[i]));
                        }
                    }
                }
            }
        }
    }
    return ans;
}
