#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 100001;
int a[MAXN];
int g[3];
int dp[MAXN][3];
int read() {
	int num = 0, v = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') v = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * v;
}
signed main() {
	int T = read();
	while (T--) {
		int n = read();
		for (register int i = 1; i <= n; i++) {
			a[i] = read();
		}
//		for (int i = 1; i <= n; i++) {
//			printf("%lld\n", a[i]);
//		}
//		memset(dp, -0x3f, sizeof dp);
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= 2; j++) {
				dp[i][j] = -0x3fffffffffffffffll;
			}
		}
		dp[0][0] = 0;
		g[0] = g[2] = 1;
		g[1] = -1;
		for (register int i = 1; i <= n; i++) {
			for (register int j = 0; j <= 2; j++) {
//				dp[i][j] = -0x3fffffffffffffffll;
				int val = g[j] * a[i];
				if (j > 0 && a[i - 1] < 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + val);
				dp[i][j] = max(dp[i][j], dp[i - 1][j] + val);
				if (j < 2) dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] + val);
			}
		}
		printf("%lld\n", max(max(dp[n][0], dp[n][1]), dp[n][2]));
	}
	return 0;
}