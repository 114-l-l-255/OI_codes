#include <cstdio>
#include <algorithm>
using namespace std;
int n, f;
double a[100001], l, r, pre[100001], b[100001], tmp, ans;
int main() {
	scanf("%d %d", &n, &f);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &a[i]);
	l = -1e6;
	r = 1e6;
	while (r - l > 1e-5) {
		double mid = (l + r) / 2;
		for (int i = 1; i <= n; i++)
			b[i] = a[i] - mid;
		for (int i = 1; i <= n; i++)
			pre[i] = pre[i - 1] + b[i];
		ans = -1e10;
		tmp = 1e10;
		for (int i = f; i <= n; i++) {
			tmp = min(tmp, pre[i - f]);
			ans = max(ans, pre[i] - tmp);
		}
		if (ans >= 0)
			l = mid;
		else
			r = mid;
	}
	printf("%d", (int)(r * 1000));
	return 0;
}