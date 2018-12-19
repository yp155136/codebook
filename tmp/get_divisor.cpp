#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <set>
#include <queue>
using namespace std;

#define SZ(x) ((int)(x).size())
typedef pair<int,int> pii;
const int MAX_N = 1e6 +6;
int prime[MAX_N];

void build() {
	prime[0] = prime[1] = 1;
	for (int i=2;MAX_N>i;i++) {
		if (prime[i] == 0) {
			prime[i]=i;
			for (long long j=i*1LL*i;MAX_N>j;j+=i) {
				prime[j] = i;
			}
		}
	}
}

vector<pii> get_prime_divisor(int x) {
	vector<pii> ret;
	while (x!=1) {
		pii tmp;
		tmp.first = prime[x];
		int cnt=0;
		int pp=prime[x];
		while (x%pp==0) {
			x/=pp;
			cnt++;
		}
		tmp.second = cnt;
		ret.emplace_back(tmp);
	}
	return ret;
}

vector<int> get_divisor(int x) {
	vector<pii> prime_divisor=get_prime_divisor(x);
	int sz=SZ(prime_divisor);
	queue<pii> que;
	que.push({1,0});
	vector<int> ret;
	while (!que.empty()) {
		pii p=que.front();
		que.pop();
		if (p.second == sz) {
			ret.emplace_back(p.first);
			continue;
		}
		int t=1;
		for (int i=0;prime_divisor[p.second].second>=i;i++) {
			que.push(make_pair(p.first*t,p.second+1));
			t*=prime_divisor[p.second].first;
		}
	}
	return ret;
}

int main () {
	build();
	vector<int> v = get_divisor(325089);
	for (int i:v) cout << i << endl;
}
