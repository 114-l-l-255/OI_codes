#include <cstdio>
const int MAXN = 3101;
long long dp[MAXN][MAXN];
short way[MAXN][MAXN];
int main() {
	dp[1][1] = 1;
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	for (int i = 0; i < t; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if (a == n && b == m) continue;
		if (a + 1 == c && b == d) {
			if (way[a][b] != 1 && way[a][b] != 0)
				way[a][b] = 3;
			else
				way[a][b] = 1;
		}
		else if (b + 1 == d && a == c) {
			if (way[a][b] != 2 && way[a][b] != 0)
				way[a][b] = 3;
			else
				way[a][b] = 2;
		}
		else {
			way[a][b] = 3;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (way[i][j]) {
				if (way[i][j] == 1) {
					dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % 1000000007;
				}
				if (way[i][j] == 2) {
					dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % 1000000007;
				}
				if (way[i][j] == 3) {
					continue;
				}
			}
			else {
				if (i != n) {
					dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % 1000000007;
				}
				if (j != m) {
					dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % 1000000007;
				}
			}
		}
	}
	printf("%lld", dp[n][m]);
	return 0;
}