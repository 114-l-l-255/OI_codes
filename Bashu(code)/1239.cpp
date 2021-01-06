#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1e6 + 5;
typedef long long ll;
int a[MAXN];
int left1[MAXN], right1[MAXN];
int left2[MAXN], right2[MAXN];
int d[MAXN];
int n;
int lowbit(int x) {
	return x & -x;
}
void add(int pos, int x) {
	while (pos <= n) {
		d[pos] += x;
		pos += lowbit(pos);
	}
	return;
}
int sum(int pos) {
	ll ret = 0;
	while (pos > 0) {
		ret += d[pos];
		pos -= lowbit(pos);
	}
	return ret;
}
void mem() {
	for (int i = 1; i <= n; i++) {
		d[i] = 0;
	}
	return;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		left1[i] = sum(a[i] - 1);
		left2[i] = sum(n) - sum(a[i]);
		add(a[i], 1);
	}
	mem();
	for (int i = n; i >= 1; i--) {
		right1[i] = sum(a[i] - 1);
		right2[i] = sum(n) - sum(a[i]);
		add(a[i], 1);
	}
	ll ret1 = 0ll, ret2 = 0ll;
	for (int i = 1; i <= n; i++) {
		ret1 += (ll)left1[i] * (ll)right1[i];
		ret2 += (ll)left2[i] * (ll)right2[i];
	}
	printf("%lld %lld", ret2, ret1);
	return 0;
}