#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 6;
const int MAX_M = 3e5 + 6;
struct Node {
	int lc,rc;
	int val;
	void give_val(int _lc,int _rc,int _val) {
		lc=_lc;rc=_rc;val = _val;
	}
} node[530*MAX_N];
int bit_root[MAX_N],root[MAX_N];
int node_cnt;
int getNode(int id) {
	int ret = ++node_cnt;
	node[ret] = node[id];
	return ret;
}
void pull(int id) {
	node[id].val = node[node[id].lc].val + node[node[id].rc].val;
}
void init(int id,int L,int R) {
	if (L==R) {
		node[id].give_val(0,0,0); return;
	}
	node[id].give_val(++node_cnt,++node_cnt,0);
	int mid=(L+R)>>1;
	init(node[id].lc,L,mid);
	init(node[id].rc,mid+1,R);
	return;
}
void modify(int old_id,int new_id,int L,int R,int pos,int val) {
	if (L==R) {
		node[new_id].val += val;return;
	}
	int mid=(L+R)>>1;
	if (pos <= mid) {
		node[new_id].lc = getNode(node[old_id].lc);
		modify(node[old_id].lc,node[new_id].lc,L,mid,pos,val);
	}
	else {
		node[new_id].rc = getNode(node[old_id].rc);
		modify(node[old_id].rc,node[new_id].rc,mid+1,R,pos,val);
	}
	pull(new_id);
	return;
}
int query(int id,int L,int R,int l,int r) {
	if (l<=L && R<=r) return node[id].val;
	int mid=(L+R)>>1;
	if (mid + 1 > r) return query(node[id].lc,L,mid,l,r);
	else if (l > mid) return query(node[id].rc,mid+1,R,l,r);
	return query(node[id].lc,L,mid,l,r) + query(node[id].rc,mid+1,R,l,r);
}
set<int> st[MAX_M];
int last[MAX_N];
int s[MAX_N];
int n,q;
typedef long long LL;
void modify_bit(int L,int R,int pos,int val) {
	for (int i=L;n>=i;i+=(i&(-i))) {
		modify(bit_root[i],bit_root[i],1,n,pos,val);
	}
	if (R==n) return;
	for (int i=R+1;n>=i;i+=(i&(-i))) {
		modify(bit_root[i],bit_root[i],1,n,pos,-val);
	}
}
int query_bit(int C,int L,int R) {
	int ret=0;
	for (int i=C;i>0;i-=(i&(-i))){
		ret += query(bit_root[i],1,n,L,R);
	}
	return ret;
}
int main (){
	int k,m;
	scanf("%d %d %d %d",&n,&q,&m,&k);
	node_cnt = 0; root[0] = ++node_cnt;	init(root[0],1,n);
	map<int,int> mp;
	for (int i=1;n>=i;i++) {
		bit_root[i] = getNode(root[0]);
	}
	int id=1;
	for (int i=1;n>=i;i++) {
		int x; scanf("%d",&x);
		int ret=0; auto iter=mp.find(x);
		if (iter == mp.end()) {
			mp.insert(make_pair(x,id));
			ret=id; id++;
		}
		else {
			ret=iter->second;
		}
		root[i] = getNode(root[i-1]);
		if (last[ret] == 0) {
			modify(root[i-1],root[i],1,n,i,1);
		}
		else {
			modify(root[i-1],root[i],1,n,i,1);
			modify(root[i],root[i],1,n,last[ret],-1);
		}
		last[ret] = i; st[ret].insert(i); s[i] = ret;
	}
	int pre_ans=0;
	for (int i=1;q>=i;i++) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		if (a==0) {
			//one base !!! query(b,c)
			pre_ans = query(root[c],1,n,b,c);
			pre_ans += query_bit(c,b,c);
			printf("%d\n",pre_ans);
		}
		else {
			//one base!!! a[b] = c
			c = (LL(pre_ans)*c%m)*k;
			if (mp[c] == s[b]) continue;
			int del=s[b]; auto iter=st[del].find(b);
			int ed = n+1; ++iter;
			if (iter != st[del].end()) ed = *(iter);
			//b ~ ed - 1
			modify_bit(b,ed-1,b,-1);
			iter--;
			if (iter != st[del].begin()) {
				int start=*(--iter);
				modify_bit(b,ed-1,start,1);
			}
			st[del].erase(st[del].find(b));
			//finish delete
			
			//now let's add
			int ret=0;
			auto iter3=mp.find(c);
			if (iter3 == mp.end()) {
				mp.insert(make_pair(c,id));
				ret=id;
				id++;
			}
			else if (iter3->second == 0) {
				mp[c] = id;
				ret=id;
				id++;
			}
			else {
				ret=iter3->second;
			}
			auto iter4 = st[ret].insert(b).first;
			ed = n+1;
			++iter4;
			if (iter4 != st[ret].end()) {
				ed = *(iter4);
			}
			--iter4;
			modify_bit(b,ed-1,b,1);
			if (iter4 != st[ret].begin()) {
				int start = *(--iter4);
				modify_bit(b,ed-1,start,-1);
			}
			s[b] = ret;
			st[ret].insert(b);
		}
	}
}

