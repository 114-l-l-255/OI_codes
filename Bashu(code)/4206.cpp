#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
long long sum[MAXN];
long long dp[MAXN][MAXN];
int a[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i];
	}
	dp[n + 1][0] = 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= m; j++) {
			if (j >= a[i]) dp[i][j] = (dp[i + 1][j] + dp[i + 1][j - a[i]]) % 1000000007;
			else dp[i][j] = dp[i + 1][j];
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= sum[i - 1]; j--) {
			dp[i + 1][j] = dp[i + 1][j - sum[i - 1]];
		}
		for (int j = 0; j < min(sum[i - 1], m * 1ll + 1); j++) {
			dp[i + 1][j] = 0;
		}
		for (int j = m; j >= m - a[i] + 1; j--) {
			ans += dp[i + 1][j];
			ans %= 1000000007;
		}
	}
	if (sum[n] > m) printf("%lld", ans);
	else printf("1");
	return 0;
}