#include <cstdio>
#include <algorithm>
#pragma GCC optimize(3)
#define mod 1000000007
using namespace std;
const int MAXN = 301;
int dp[MAXN << 1][MAXN][MAXN];
int inv[MAXN << 1];
inline int fstpow(int x) {
	return x > mod ? x - mod : x;
}
int main() {
	inv[1] = 1;
	for (int i = 2; i <= 600; i++) {
		inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
	}
	int n, m;
	scanf("%d %d", &n, &m);
//	n = 1000000, m = 300;
	dp[0][0][m] = 1;
	register int C = 1;
	register int ans = 0;
	int kkk = min((m << 1), n);
	for (register int j = 0; j <= m; j++)
		for (register int k = 0; k <= m; k++) {
			if (dp[0][j][k] == 0) continue;
			if (j != m) if (k) dp[1][j + 1][k - 1] = fstpow(dp[1][j + 1][k - 1] + (long long)dp[0][j][k] * k % mod);
			if (k) dp[1][j][k - 1] = fstpow(dp[1][j][k - 1] + (long long)dp[0][j][k] * k % mod);
			if (j) dp[1][j - 1][k] = fstpow(dp[1][j - 1][k] + dp[0][j][k]);
		}
	for (register int j = 1; j <= m; j++)
		for (register int k = 0; k <= m; k++) {
			if (dp[1][j][k] == 0) continue;
			if (j != m) if (k) dp[2][j + 1][k - 1] = fstpow(dp[2][j + 1][k - 1] + (long long)dp[1][j][k] * k % mod);
			if (k) dp[2][j][k - 1] = fstpow(dp[2][j][k - 1] + (long long)dp[1][j][k] * k % mod);
			if (j) dp[2][j - 1][k] = fstpow(dp[2][j - 1][k] + dp[1][j][k]);
		}
	for (register int j = 0; j <= m; j++) ans = fstpow(ans + (long long)dp[1][1][j] * C % mod);
	for (register int i = 2; i < kkk; i++) {
		for (register int j = 1; j <= m; j++)
			for (register int k = 0; k <= m; k++) {
				if (dp[i][j][k] == 0) continue;
				if (j != m) if (k) dp[i + 1][j + 1][k - 1] = fstpow(dp[i + 1][j + 1][k - 1] + (long long)dp[i][j][k] * k % mod);
				if (k) dp[i + 1][j][k - 1] = fstpow(dp[i + 1][j][k - 1] + (long long)dp[i][j][k] * k % mod);
				if (j) dp[i + 1][j - 1][k] = fstpow(dp[i + 1][j - 1][k] + dp[i][j][k]);
			}
		C = (long long)C * (n - i + 1) % mod, C = (long long)C * inv[i - 1] % mod;
		for (register int j = 0; j <= m; j++) ans = fstpow(ans + (long long)dp[i][1][j] * C % mod);
	}
	C = (long long)C * (n - kkk + 1) % mod, C = (long long)C * inv[kkk - 1] % mod;
	for (register int j = 0; j <= m; j++) ans = fstpow(ans + (long long)dp[kkk][1][j] * C % mod);
	printf("%d", ans);
	return 0;
}