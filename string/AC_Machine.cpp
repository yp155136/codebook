#include <bits/stdc++.h>
using namespace std;

struct AC_Automata {
    static const int N = 2e4 + 6;
    static const int SIGMA = 26;
    int ch[N][SIGMA], val[N], sz;
    int last[N],fail[N];
    int que[N],qs,qe, cnt[N];
    void init() {
        sz = 1;
        memset(ch[0],0,sizeof(ch[0]));
        qs = qe  = 0;
        memset(cnt,0,sizeof(cnt)); memset(val,0,sizeof(val)); memset(last,0,sizeof(last));
    }
    int idx(char c) {
        return c-'a';
    }
    int insert(string s,int v) {
        int now=0;
        int n=s.size();
        for (int i=0;n>i;i++) {
            int c=idx(s[i]);
            if (!ch[now][c]) {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[now][c] = sz++;
            }
            now = ch[now][c];
        }
        val[now] = v;
        return now;
    }
    void print(int j) {
        if (j) {
            //now we match string v[j]
            print(last[j]);  //may match multiple strings
        }
    }
    void getFail() {
        qs=0,qe=0;
        fail[0]=0;
        for (int c=0;SIGMA >c;c++) {
            int now=ch[0][c];
            if (now) {
                fail[now] = 0;
                que[qe++] = now;
                last[now] = 0;
            }
        }
        while (qs != qe) {
            int t=que[qs++];
            for (int c=0;SIGMA > c;c++) {
                int now=ch[t][c];
                if (!now) continue;
                que[qe++] = now;
                int v=fail[t];
                while (v && !ch[v][c]) v=fail[v];
                fail[now] = ch[v][c];
                last[now] = val[ fail[now] ]? fail[now]:last[ fail[now] ];
            }
        }
    }
    void Find(string s) {
        getFail();
        int n=s.size();
        int now=0;
        for (int i=0;n>i;i++) {
            int c=idx(s[i]);
            while (now && !ch[now][c]) now = fail[now];
            now = ch[now][c];
            cnt[now]++;
        }
        for (int i=qe-1;i>=0;i--) {
            cnt[ fail[que[i]] ] += cnt[ que[i] ];
        }
    }
    void AC_evolution() {
        for (qs=1;qs!=qe;) {
            int now=que[qs++];
            for (int i=0;SIGMA>i;i++) {
                if (ch[now][i] == 0) ch[now][i] = ch[fail[now]][i];
            }
        }
    }
} ac;

const int N = 156;
string s[N];
int ed[N];

ac.init();
ac.insert(s[i],i);
ac.Find();
ac.cnt[ ac.insert(s[i],i) ];

