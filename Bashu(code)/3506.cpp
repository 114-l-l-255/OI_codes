#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include <cmath>
#include <iomanip>
#include <queue>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f
#define M 50005
struct node {
	ll w;
	ll s;
} cow[100006];
bool cmp(node a, node b) {
	return a.s + a.w < b.s + b.w;
}
int main() {
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> cow[i].w >> cow[i].s;
	if (n == 1) {
		cout << -cow[0].s << endl;
		return 0;
	}
	sort(cow, cow + n, cmp);
	ll t = 0, res = -inf;
	for (int i = 0; i < n; i++) {
		if (t - cow[i].s > res) res = t - cow[i].s;
		t += cow[i].w;
	}
	cout << res << endl;
	return 0;
}