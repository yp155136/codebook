pdd intersect(pdd p1, pdd p2, pdd q1, pdd q2) {
    //make sure that p1p2 is not parallel to q1q2
    return p1 + ((q1 - p1) ^ (q2 - q1)) / ((p2 - p1) ^ (q2 - q1)) * (p2 - p1);
}
