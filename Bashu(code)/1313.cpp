#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
int a[MAXN];
int _abs(int a) { return a < 0 ? -a : a; }
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	int mid = n >> 1;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += _abs(a[i] - a[mid]);
	}
	printf("%lld", ans);
	return 0;
}