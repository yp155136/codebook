struct Circle_and_Segment_Intersection {
    const ld eps = 1e-9;
    vector<pdd> solve(pdd p1, pdd p2, pdd cen, ld r) {
        //please notice that p1 != p2
        //condiser p = p2 + (p1 - p2) * t, 0 <= t <= 1
        vector<pdd> ret;
        p1 = p1 - cen; p2 = p2 - cen;
        ld a = (p1 - p2) * (p1 - p2);
        ld b = 2 * (p2 * (p1 - p2));
        ld c = p2 * p2 - r * r;
        ld bb4ac = b * b - 4 * a * c;
        if (bb4ac < -eps) return ret; //no intersection
        vector<ld> ts;
        if ( (bb4ac) <= eps) {
            ts.push_back(-b / 2 / a);
        }
        else {
            ts.push_back( (-b + sqrt(bb4ac)) / (a * 2) );
            ts.push_back( (-b - sqrt(bb4ac)) / (a * 2) );
        }
        sort(ts.begin(), ts.end());
        for (ld t: ts) {
            if (-eps <= t && t <= 1 + eps) {
                t = max(t, 0.0);
                t = min(t, 1.0);
                pdd pt = p2 + t * (p1 - p2);
                pt = pt + cen;
                ret.push_back(pt);
            }
        }
        return ret;
    }
} solver;

double f(ld a, ld b) {
    ld ret = b - a;
    while (ret <= -pi - eps) ret += 2 * pi;
    while (ret >= pi + eps) ret -= 2 * pi;
    return ret;
}

ld solve_small(pdd cen, ld r, pdd p1, pdd p2) {
    p1 = p1 - cen, p2 = p2 - cen;
    cen = {0, 0};
    vector<pdd> inter = solver.solve(p1, p2, cen, r);
    ld ret = 0.0;
    if ((int)inter.size() == 0) {
        if (in_cir(cen, r, p1)) {
            ret = (p1 ^ p2) / 2;
        }
        else {
            ret = (r * r * f(atan2(p1.Y, p1.X), atan2(p2.Y, p2.X))) / 2 ;
        }
    }
    else if ( (int)inter.size() == 1) {
        if (!in_cir(cen, r, p1) && !in_cir(cen, r, p2)) {
            //outside cut
            ret = (r * r * f(atan2(p1.Y, p1.X), atan2(p2.Y, p2.X))) / 2;
        }
        else if (!in_cir(cen, r, p1)) {
            pdd _p1 = inter[0];
            ret +=  ((_p1 ^ p2) / 2);
            ret +=  (r * r * f(atan2(p1.Y, p1.X), atan2(_p1.Y, _p1.X))) / 2;
        }
        else if (!in_cir(cen, r, p2)) {
            pdd _p2 = inter[0];
            ret +=  ((p1 ^ _p2) / 2);
            ret +=  (r * r * f(atan2(_p2.Y, _p2.X), atan2(p2.Y, p2.X))) / 2;
        }
    }
    else if ( (int)inter.size() == 2) {
        pdd _p2 = inter[0], _p1 = inter[1];
        ret +=  ((_p1 ^ _p2) / 2);
        ret +=  (r * r * f(atan2(_p2.Y, _p2.X), atan2(p2.Y, p2.X))) / 2;
        ret +=  (r * r * f(atan2(p1.Y, p1.X), atan2(_p1.Y, _p1.X))) / 2;
    }
    return ret;
}

ld solve(pdd cen, ld r, vector<pdd> pts) {
    ld ret = 0;
    for (int i = 0; i < (int)pts.size(); ++i) {
        ret += solve_small(cen, r, pts[i], pts[(i + 1) % int(pts.size())]);
    }
    ret = max(ret, -ret);
    return ret;
}

