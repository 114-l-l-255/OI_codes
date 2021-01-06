#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct line {
	int l, r;
	bool operator < (const line& sec) const {
		return r < sec.r;
	}
} lines[201];
int a[1000001];
int dp[201][201];
int main() {
//	freopen("apple.in", "r", stdin);
//	freopen("apple.out", "w", stdout);
	int n, m, h, k;
	int ansans = 0;
	scanf("%d %d %d %d", &n, &m, &h, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (a[i] == h) ansans++; 
	}
	sort(a, a + n);
	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		lines[i].l = max(1, lines[i].l);
		lines[i].r = max(1, lines[i].r);
		lines[i].l = lower_bound(a, a + n, l + h) - a;
		lines[i].r = upper_bound(a, a + n, r + h) - a - 1;
//		printf("%d %d\n", lines[i].l, lines[i].r);
	}
	sort(lines, lines + m);
	int ans = 0;
	memset(dp, 0xcf, sizeof dp);
	for (int i = 0; i < m; i++) {
		if (lines[i].l > lines[i].r) continue;
		dp[i][1] = lines[i].r - lines[i].l + 1;
		for (int kkk = 2; kkk <= k; kkk++) {
			dp[i][kkk] = lines[i].r - lines[i].l + 1;
			for (int j = 0; j < i; j++) {
				dp[i][kkk] = max(dp[i][kkk], dp[j][kkk - 1] + lines[i].r - max(lines[j].r + 1, lines[i].l) + 1);
			}
			ans = max(ans, dp[i][kkk]);
		}
	}
	printf("%d", ans + ansans);
	return 0;
}