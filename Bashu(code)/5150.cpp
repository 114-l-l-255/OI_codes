#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 200001;
unsigned long long a[MAXN];
int n;
unsigned long long check(unsigned long long tar) {
	int l = 1, r = 1;
	unsigned long long ans = 0;
	for (l = 1; l <= n;) {
		while (r != n && a[r + 1] - a[l] <= tar) r++;
//		printf("%d, %d\n", l, r);
		ans += (r - l);
		l++;
	}
	return ans;
}
unsigned long long BinSer(unsigned long long tarjet) {
	unsigned long long l = 0, r = 1e18;
	if (check(l) >= tarjet) return l;
	while (l + 1 < r) {
		unsigned long long mid = l + r >> 1;
//		printf("%llu, %llu, %llu\n", l, r, mid);
		if (check(mid) < tarjet) l = mid;
		else r = mid;
	}
	return r;
}
int main() {
//	freopen("mid.in", "r", stdin);
//	freopen("mid.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%llu", &a[i]);
	}
	sort(a + 1, a + 1 + n);
//	printf("%llu", check(50));
//	while(1);
	unsigned long long tarjet = ((unsigned long long)n * (n - 1)) >> 2;
//	printf("-------\n");
	unsigned long long ans1 = BinSer(tarjet);
	if (((((unsigned long long)n * (n - 1)) >> 1) & 1) == 0) {
//		printf("-------\n");
		unsigned long long ans2 = BinSer(tarjet + 1);
		printf("%llu", ans1 + ans2 >> 1);
	}
	else {
		printf("%llu", ans1);
	}
	return 0;
}