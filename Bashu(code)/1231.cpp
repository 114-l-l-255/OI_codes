#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN = 1000006;
typedef long long ll;
int a[MAXN];
int left1[MAXN], right1[MAXN];
int d[MAXN];
int n;
int lowbit(int x) {
	return x & -x;
}
void add(int pos, int x) {
	while (pos <= 500006) {
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
	for (int i = 0; i <= 500006; i++) {
		d[i] = 0;
	}
	return;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		left1[i] = sum(a[i] + 1);
		add(a[i] + 2, 1);
	}
	mem();
	for (int i = n; i >= 1; i--) { 
		right1[i] = sum(a[i] + 1);
		add(a[i] + 2, 1);
	}
	ll ret1 = 0ll;
	for (int i = 1; i <= n; i++) {
		ret1 += (ll)left1[i] * (ll)right1[i];
	}
	printf("%lld", ret1);
	return 0;
}