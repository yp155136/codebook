#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main () {
	cout<<"assume that v : 1 1 2 3 3 3 5 5 6 7 8 8 9\n";
	vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(3);
	v.push_back(5);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(8);
	v.push_back(9);
	for (int i=0;10>=i;i++) {
		int tmp=i;
		cout<<"i = "<<i<<" , lower_bound = "<<lower_bound(v.begin(),v.end(),tmp)-v.begin()<<" , ";
		tmp=i;
		cout<<"upper_bound = "<<upper_bound(v.begin(),v.end(),tmp) - v.begin()<<endl;
	}
}
