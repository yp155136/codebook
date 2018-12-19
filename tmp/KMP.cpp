
int fail[MAX_N];

void build(string b) {
    int len=b.size();
    int pos;
    pos = fail[0] = -1;
    for (int i=1;len > i;i++) {
        while (pos != -1 && b[pos + 1] != b[i]) {
            pos = fail[pos];
        }
        if (b[pos+1] == b[i]) pos++;
        fail[i] = pos;
    }
}

int match(string a,string b) {
    int lena=a.size(),lenb=b.size();
    int pos=-1;
    int cnt=0;
    for (int i=0;i<lena;i++) {
        while (pos != -1 && b[pos+1] != a[i]) {
            pos = fail[pos];
        }
        if (b[pos + 1] == a[i]) pos++;
        if (pos == lenb - 1) {
            cnt++;
            pos = fail[pos];
        }
    }
    return cnt;
}
