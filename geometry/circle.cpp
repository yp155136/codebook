//Note that this code will crash if circle A and B are the same
typedef pair<double, double> pdd;
pdd rtcw(pdd p){return pdd(p.Y, -p.X); }
vector<pdd> circlesintersect(pdd A, pdd B, double r1, double r2){
    vector<pdd> ret;
    double d = dis(A, B);
    if(d > r1 + r2 || d + min(r1, r2) < max(r1, r2))
        return ret;
    double x = (d * d + r1 * r1 - r2 * r2) / (2 * d);
    double y = sqrt(r1 * r1 - x * x);
    pdd v = (B - A) / d;
    ret.eb(A + v * x + rtcw(v) * y);
    if(y > 0)
        ret.eb(A + v * x - rtcw(v) * y);
    return ret;
}
