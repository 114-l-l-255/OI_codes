#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
int n, k;
long long lenth;
struct tree {
	long long val;
	long long h;
};
priority_queue<tree>q;
bool operator < (tree a, tree b) {
	if (a.val != b.val) return a.val > b.val;
	else return a.h > b.h;
}
inline long long max(long long a, long long b) {
	if (a > b) return a;
	else return b;
}
int main() {
	scanf("%d %d", &n, &k);
	long long remain = 0;
	for (int i = 1; i <= n; i++) {
		tree a;
		scanf("%lld", &a.val);
		a.h = 1;
		q.push(a);
	}
	int extra = 0;
	if ((n - 1) % (k - 1)) extra = k - 1 - (n - 1) % (k - 1);
	for (int i = 1; i <= extra; i++) {
		tree a;
		a.val = 0;
		a.h = 1;
		q.push(a);
	}
	remain += n + extra;
	while (remain != 1) {
		tree a;
		long long cnt = 1, maxh = 0, tmp = 0;
		while (cnt <= k) {
			a = q.top();
			q.pop();
			maxh = max(maxh, a.h);
			tmp += a.val;
			cnt++;
		}
		a.h = maxh + 1;
		a.val = tmp;
		lenth += tmp;
		q.push(a);
		remain = remain - k + 1;
	}
	tree a = q.top();
	printf("%lld\n%lld", lenth, a.h - 1);
	return 0;
}