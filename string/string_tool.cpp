const KMP_SIZE = ;
struct KMP{
    string s;
    int f[KMP_SIZE] , pos;
    void solve(){
        f[0] = pos = -1;
        REP(i , 1 , s.size()){
            while(pos != -1 && s[pos + 1] != s[i]) pos = f[pos];
            if(s[pos + 1] == s[i]) pos ++;
            f[i] = pos;
        }
    }
};
const int ZVALUE_SIZE = ;
struct Z_VALUE{
    string s;
    int l = 0 , r = 0 , z[ZVALUE_SIZE];
    void solve(){
        REP(i , 0 , s.size()){
            z[i] = max(min(z[i - l] , r - i) , 0LL);
            while(i + z[i] < s.size() && s[z[i]] == s[i + z[i]]){
                l = i , r = i + z[i];
                z[i] ++;
            }
        }
    }
};
const int PALINDROME_MAX = 2 * ;
struct Palindrome{
    string s , ss; // ss = input
    int z[PALINDROME_MAX];
    void solve(){
        s.resize(ss.size() + ss.size() + 1 , '.');
        REP(i , 0 , ss.size()) s[i + i + 1] = ss[i];
        int l = 0 , r = 0;
        REP(i , 0 , s.size()){
            z[i] = max(min(z[l + l - i] , r - i) , 1);
            while(i - z[i] >= 0 && i + z[i] < s.size() && s[i - z[i]] == s[i + z[i]]){
                l = i , r = i + z[i];
                z[i] ++;
            }
        }
    }
};
