#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

string f(string s) {
	if ('1'<=s[0] && s[0] <= '9') {
		string ret="  ";
		ret[0]=s[0];
		ret[1]=s[1];
		return ret;
	}
	return s;
}

//DONG¡BNAN¡BXI¡BBEI¡BZHONG¡BFA¡BBAI

const int MAX_N = 34;

string card[MAX_N] = {
	"1T","2T","3T","4T","5T","6T","7T","8T","9T",
	"1S","2S","3S","4S","5S","6S","7S","8S","9S",
	"1W","2W","3W","4W","5W","6W","7W","8W","9W",
	"DONG","NAN","XI","BEI","ZHONG","FA","BAI"
};

map<string,int> mp;

bool solve(vector<string> v) {
	sort(v.begin(),v.end());
	if (v.size() == 3) {
		int _0 = mp[v[0]],_1=mp[v[1]],_2=mp[v[2]];
		if (_0 == _1 && _1==_2) return true;
		else if (_0+1 == _1 && _1+1==_2) {
			if (0<=_0 && _2<=8 || 9<=_0 && _2<=17 || 18<=_0 && _2<=26) return true;
			else return false;
		}
		return false;
	}
	//use pong first
	int sz=v.size();
	set<string> st;
	for (int i=0;sz-2>i;i++) {
		if (v[i] == v[i+1] && v[i+1] == v[i+2] && st.find(v[i]) == st.end()) {
			vector<string> nxt=v;
			nxt.erase(nxt.begin()+(i+2));
			nxt.erase(nxt.begin()+(i+1));
			nxt.erase(nxt.begin()+(i));
			st.insert(v[i]);
			if (solve(nxt)) return true;
		}
	}
	//use eat then
	int cnt[MAX_N];
	memset(cnt,0,sizeof(cnt));
	for (int i=0;sz>i;i++) {
		cnt[mp[v[i]]] = i;
	}
	for (int i=0;0+6>=i;i++) {
		if (cnt[i] &&cnt[i+1] && cnt[i+2]) {
			vector<string> nxt=v;
			nxt.erase(nxt.begin()+(cnt[i+2]));
			nxt.erase(nxt.begin()+(cnt[i+1]));
			nxt.erase(nxt.begin()+cnt[i]);
			if (solve(nxt)) return true;
		}
	}
	for (int i=9;9+6>=i;i++) {
		if (cnt[i] &&cnt[i+1] && cnt[i+2]) {
			vector<string> nxt=v;
			nxt.erase(nxt.begin()+(cnt[i+2]));
			nxt.erase(nxt.begin()+(cnt[i+1]));
			nxt.erase(nxt.begin()+cnt[i]);
			if (solve(nxt)) return true;
		}
	}
	for (int i=18;18+6>=i;i++) {
		if (cnt[i] &&cnt[i+1] && cnt[i+2]) {
			vector<string> nxt=v;
			nxt.erase(nxt.begin()+(cnt[i+2]));
			nxt.erase(nxt.begin()+(cnt[i+1]));
			nxt.erase(nxt.begin()+cnt[i]);
			if (solve(nxt)) return true;
		}
	}
	return false;
}

bool can(vector<string> v) {
//	cout<<"can sz = "<<v.size()<<endl;
	// find two the same
	int sz=v.size();
	sort(v.begin(),v.end());
	for (int i=0;sz-1>i;i++) {
		if (v[i] == v[i+1]) {
			vector<string> nxt=v;
			nxt.erase(nxt.begin()+(i+1));
			nxt.erase(nxt.begin()+(i));
			if (solve(nxt)) return true;
		}
	}
	return false;
}

int main () {
	int cases=1;
	vector<string> v;
	string s;
	for (int i=0;34>i;i++) {
		mp[card[i]] = i;
		mp[f(card[i])] = i;
	}
	while (cin >> s) {
		if (s=="0") break;
		v.clear();
		v.push_back(f(s));
		int last=12;
		while (last--) {
			cin >> s;
			v.push_back(f(s));
		}
		int cnt[MAX_N];
		memset(cnt,0,sizeof(cnt));
		for (auto i:v) {
			cnt[mp[i]]++;
		}
		vector<string> ans;
		for (int i=0;34>i;i++) {
			if (cnt[i] == 4) continue;
			vector<string> tmp;
			tmp = v;
			tmp.push_back(f(card[i]));
			if (can(tmp)) ans.push_back(card[i]);
		}
		cout<<"Case "<<cases++<<":";
		if (ans.size() == 0) cout<<" Not ready\n";
		else {
			for (auto i:ans) {
				cout<<" "<<i;
			}
			cout<<endl;
		}
	}
}
