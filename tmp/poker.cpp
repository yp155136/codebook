#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_set>
#include <cassert>
using namespace std;

typedef long long LL;
typedef pair<int,LL> pii;

struct Card {
	int cnt_suit[5];
	int cnt_hand[15];
	vector<pii> v;
	void init(vector<pii> _v) {
		//v=_v;
		v.clear();
		for(pii p:_v) v.push_back(p);
		memset(cnt_suit,0,sizeof(cnt_suit));
		memset(cnt_hand,0,sizeof(cnt_hand));
		for (pii p:v) {
			cnt_suit[p.second]++;
			cnt_hand[p.first]++;
		}
		cnt_hand[14] = cnt_hand[1];
	}
} card;

pii to_pii(string s) {
	pii ret;
	if (s[1] == 'A') ret.first = 1;
	else if (s[1] == 'T') ret.first = 10;
	else if (s[1] == 'J') ret.first = 11;
	else if (s[1] == 'Q') ret.first = 12;
	else if (s[1] == 'K') ret.first = 13;
	else ret.first = s[1]-'0';
	if (s[0] == 'c') ret.second = 1;
	else if (s[0] == 'd') ret.second = 2;
	else if (s[0] == 'h') ret.second = 3;
	else if (s[0] == 's') ret.second = 4;
	return ret;
}

LL straight(Card card) {
	for (int i=1;10>=i;i++) {
		if (card.cnt_hand[i] && card.cnt_hand[i+1] && card.cnt_hand[i+2] && card.cnt_hand[i+3] && card.cnt_hand[i+4]) {
			return i+4;
		}
	}
	return 0;
}

LL flush(Card card) {
	LL ret=0;
	for (int i=1;4>=i;i++) {
		if (card.cnt_suit[i] == 5) {
			ret=1;
		}
	}
	if (ret) {
		ret=0;
		for (int i=14;i>=2;i--) {
			if (card.cnt_hand[i] == 1) {
				ret *= 100;
				ret += i;
			}
		}
	}
	return ret;
}

LL four_of_a_kind(Card card) {
    int ret = 0;
	for (int i=2;14>=i;i++) {
		if (card.cnt_hand[i] == 4) {
			ret = i;
		}
	}
	if (ret == 0)return 0;
	for (int i=14;i>=2;i--)
    {
        if (card.cnt_hand[i] == 1)
        {
            ret *= 100;
            ret += i;
        }
    }
    return ret;
}

LL three_of_a_kind(Card card) {
	LL ret=0;
	int cnt=0;
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 3) {
			cnt++;
		}
	}
	if (cnt != 1) {
		return 0;
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 3) {
			ret *= 1000000;
			ret += (i*10000LL+i*100+i);
		}
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 1) {
			ret *= 100;
			ret += i;
		}
	}
	return ret;
}

LL two_pair(Card card) {
	LL ret=0;
	int cnt=0;
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 2) {
			cnt++;
		}
	}
	if (cnt != 2) {
		return 0;
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 2) {
			ret *= 10000LL;
			ret += (i*100+i);
		}
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 1) {
			ret *= 100;
			ret += i;
		}
	}
	return ret;
}

LL one_pair(Card card) {
	LL ret=0;
	int cnt=0;
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 2) {
			cnt++;
		}
	}
	if (cnt != 1) {
		return 0;
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 2) {
			ret *= 10000LL;
			ret += (i*100+i);
		}
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 1) {
			ret *= 100;
			ret += i;
		}
	}
	return ret;
}

LL high_card(Card card) {
	LL ret=0;
	int cnt=0;
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 1) {
			cnt++;
		}
	}
	if (cnt != 5) {
		return 0;
	}
	for (int i=14;i>=2;i--) {
		if (card.cnt_hand[i] == 1) {
			ret *= 100LL;
			ret += i;
		}
	}
	return ret;
}

pii get_level(Card card) {
	if (straight(card) && flush(card)) {
		return make_pair(9,straight(card));
	}
	else if (four_of_a_kind(card)) {
		return make_pair(8,four_of_a_kind(card));
	}
	else if (three_of_a_kind(card) && one_pair(card)) {
		return make_pair(7,three_of_a_kind(card) * 10000 + one_pair(card));
	}
	else if (flush(card)) {
		return make_pair(6,flush(card));
	}
	else if (straight(card)) {
		return make_pair(5,straight(card));
	}
	else if (three_of_a_kind(card)) {
		return make_pair(4,three_of_a_kind(card));
	}
	else if (two_pair(card)) {
		return make_pair(3,two_pair(card));
	}
	else if (one_pair(card)) {
		return make_pair(2,one_pair(card));
	}
	else if (high_card(card)) {
		return make_pair(1,high_card(card));
	}
}
