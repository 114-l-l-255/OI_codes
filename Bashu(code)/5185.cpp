#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
struct Fcuk {
	int l, r;
	bool operator < (const Fcuk& sec) const {
		return l > sec.l;
	}
} fcuk[MAXN];
int aa[MAXN];
int is_tao[MAXN];
bool tong[MAXN];
int n, m, nn;
int main() {
//	freopen("force.in", "r", stdin);
//	freopen("force.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &fcuk[i].l, &fcuk[i].r);
		aa[i * 2 - 1] = fcuk[i].l;
		aa[i * 2] = fcuk[i].r;
	}
	sort(aa + 1, aa + 1 + m + m);
	nn = unique(aa + 1, aa + 1 + m + m) - aa;
	for (int i = 1; i <= m; i++) {
		fcuk[i].l = lower_bound(aa + 1, aa + 1 + nn, fcuk[i].l) - aa;
		fcuk[i].r = lower_bound(aa + 1, aa + 1 + nn, fcuk[i].r) - aa;
//		printf("%d %d\n", fcuk[i].l, fcuk[i].r);
	}
//	sort(fcuk + 1, fcuk + m + 1);
	for (int i = 1; i <= m; i++) {
		for (int j = fcuk[i].l; j <= fcuk[i].r; j++) {
			is_tao[j] = i;
		}
	}
	for (int i = 1; i <= 1000; i++) {
		tong[is_tao[i]] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		ans += tong[i];
	}
	printf("%lld\n", 1ll << (long long)ans);
//	printf("%d\n", ans);
	return 0;
}