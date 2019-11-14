int intersect(PII a , PII b , PII c , PII d){
    if(max(a.F , b.F) < min(c.F , d.F)) return 0;
    if(max(c.F , d.F) < min(a.F , b.F)) return 0;
    if(max(a.S , b.S) < min(c.S , d.S)) return 0;
    if(max(c.S , d.S) < min(a.S , b.S)) return 0;
    if(cross(b - a , c - a) * cross(b - a , d - a) == 1) return 0;
    if(cross(d - c , a - c) * cross(d - c , b - c) == 1) return 0;
    return 1;
}

