#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e4 + 6;
const int MAX_M = 1e6 + 6;

int cnt[MAX_M];
int s[MAX_N];

struct Query {
    int L,R,Lid,Rid,T,id;
    void give_val(int _L,int _R,int _Lid,int _Rid,int _T,int _id) {
        L = _L; R = _R; Lid = _Lid;
        Rid = _Rid; T = _T; id = _id;
    }
    bool operator<(const Query &q2) {
        if (Lid != q2.Lid) return Lid < q2.Lid;
        if (Rid != q2.Rid) return Rid < q2.Rid;
        return T < q2.T;
    }
} query[MAX_N];
struct Modify {
    int pos,ori_val,after_val;
    void give_val(int _pos,int _ori_val,int _after_val) {
        pos = _pos;
        ori_val = _ori_val;
        after_val = _after_val;
    }
} modify[MAX_N];
int ans[MAX_N];
int cur_ans;
void add(int x) {}
void sub(int x) {}
void addTime(int T,int L,int R) {
    if (L <= modify[T].pos && modify[T].pos <= R) {
        sub(s[modify[T].pos]);
        add(modify[T].after_val);
    }
    s[modify[T].pos] = modify[T].after_val;
}
void subTime(int T,int L,int R) {
    if (L <= modify[T].pos && modify[T].pos <= R) {
        sub(s[modify[T].pos]);
        add(modify[T].ori_val);
    }
    s[modify[T].pos] = modify[T].ori_val;
}
    
int T=-1;
int qid=0;
int B = pow(max(n,m),2.0/3.0);
if (B<=0) B=1;
sort(query+1,query+qid+1);
int L=1,R=0;
for (int i=1;qid >= i;i++) {
    if (query[i].L > query[i].R) {
        ans[query[i].id] = 0;
        continue;
    }
    while (query[i].R > R) add(s[++R]);
    while (query[i].L < L) add(s[--L]);
    while (query[i].R < R) sub(s[R--]);
    while (query[i].L > L) sub(s[L++]);
    while (query[i].T > T) addTime(++T,L,R);
    while (query[i].T < T) subTime(T--,L,R);
    ans[query[i].id] = cur_ans;
}

