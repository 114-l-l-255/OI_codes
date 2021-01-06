#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 10001;
int x[MAXN], y[MAXN];
int main() {
	int n, ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &x[i], &y[i]);
	}
	sort(x, x + n);
	for (int i = 0; i < n; ++i) x[i] -= i;
	sort(x, x + n);
	sort(y, y + n);
	for (int i = 0; i < n; ++i) {
		ans += abs(x[i] - x[n / 2]);
		ans += abs(y[i] - y[n / 2]);
	}
	printf("%d", ans);
	return 0;
}