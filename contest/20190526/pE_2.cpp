#include <bits/stdc++.h>
using namespace std;

int main () {
    string c = "g++ pE_1.cpp -o sol";
    system(c.c_str());
    freopen("pE.cpp","w",stdout);
    int id=0;
    for (int r=2;r<=6;++r) {
        for (int c=2;c<=6;++c) {
            for (int m=1;m<=8;++m) {
                ++id;
                string cmd = "./sol " + to_string(r) + " " + to_string(c) + " " + to_string(m) + " > tmp" + to_string(++id);
                system(cmd.c_str());
                string file = "tmp" + to_string(id);
                freopen(file.c_str(),"r",stdin);
                int x; cin >> x;
                cout << "ans[" << r << "][" << c << "][" << m <<"] = " << x << ";" << endl;
                cerr << "r = " << r << " , c = " << c << " , x = " << x << endl;
            }
        }
    }
}

