#include <cstdio>
#include <algorithm>
#define nit long long
using namespace std;
const nit MAXN = 1000001;
nit column[MAXN], row[MAXN];
nit s1[MAXN], s2[MAXN];
nit abs_(nit a) {
	return a < 0 ? -a : a;
}
int main() {
	nit n, m, t;
	scanf("%lld %lld %lld", &n, &m, &t);
	for (nit i = 0; i < t; i++) {
		nit x, y;
		scanf("%lld %lld", &x, &y);
		row[x]++;
		column[y]++;
	}
	bool flg1 = ((t % n) == 0);
	bool flg2 = ((t % m) == 0);
	if (!(flg1 || flg2)) {
		printf("impossible");
	}
	else {
		nit ans = 0;
		if (flg1) {
			for (nit i = 1; i <= n; i++) {
				s1[i] = s1[i - 1] + row[i] - t / n;
			}
			sort(s1 + 1, s1 + n + 1);
			nit mid = (n >> 1) + 1;
			for (nit i = 1; i <= n; i++) {
				ans += abs_(s1[i] - s1[mid]);
			}
		}
		if (flg2) {
			for (nit i = 1; i <= m; i++) {
				s2[i] = s2[i - 1] + column[i] - t / m;
			}
			sort(s2 + 1, s2 + m + 1);
			nit mid = (m >> 1) + 1;
			for (nit i = 1; i <= m; i++) {
				ans += abs_(s2[i] - s2[mid]);
			}
		}
		if (flg1 && !flg2) printf("row ");
		if (!flg1 && flg2) printf("column ");
		if (flg1 && flg2) printf("both ");
		printf("%lld", ans);
	}
	return 0;
}