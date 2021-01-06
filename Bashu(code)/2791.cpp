#include <cstdio>
#include <algorithm>
#define nit long long
using namespace std;
const nit MAXN = 1000001;
nit a[MAXN], s2[MAXN];
nit abs_(nit _a) {
	return _a < 0 ? -_a : _a;
}
int main() {
	nit n;
	scanf("%lld", &n);
	nit t = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		t += a[i];
	} 
	nit ans = 0;
	for (nit i = 1; i <= n; i++) {
		s2[i] = s2[i - 1] + a[i] - t / n;
	}
	sort(s2 + 1, s2 + n + 1);
	nit mid = (n >> 1) + 1;
	for (nit i = 1; i <= n; i++) {
		ans += abs_(s2[i] - s2[mid]);
	}
	printf("%lld", ans);
	return 0;
}