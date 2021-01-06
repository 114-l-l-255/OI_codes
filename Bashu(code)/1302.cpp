#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
int a[MAXN], b[MAXN], c[MAXN], aa[MAXN];
int peo[MAXN];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		aa[i] = a[i];
	}
	sort(aa + 1, aa + 1 + n);
	unique(aa + 1, aa + 1 + n);
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(aa + 1, aa + 1 + n, a[i]) - aa;
		peo[a[i]]++;
	}
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
		int kkk = lower_bound(aa + 1, aa + 1 + n, b[i]) - aa;
		if (aa[kkk] != b[i]) b[i] = 0;
		else b[i] = kkk;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &c[i]);
		int kkk = lower_bound(aa + 1, aa + 1 + n, c[i]) - aa;
		if (aa[kkk] != c[i]) c[i] = 0;
		else c[i] = kkk;
	}
	int ans1 = 0, ans2 = 0, ans = 0;
	for (int i = 1; i <= m; i++) {
		if (ans == 0) ans = i;
		else {
			int res1 = peo[b[i]];
			int res2 = peo[c[i]];
			if (res1 > ans1 || (res1 == ans1 && res2 > ans2)) {
				ans1 = res1;
				ans2 = res2;
				ans = i;
			}
		}
	}
	printf("%d", ans);
	return 0;
}