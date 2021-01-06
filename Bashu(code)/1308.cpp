#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int MAXN = 21;
const int MAXN2 = 262145;
int in[MAXN2], dp[MAXN2][MAXN], mp[MAXN][MAXN];
queue<int> que;
signed main() {
	for (int i = 1; i <= 262144; i++) {
		in[i] = in[i >> 1] + (i & 1);
	}
	memset(dp, 0x3f, sizeof dp);
	int n;
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lld", &mp[i][j]);
		}
	}
	for (int i = 0; i < n - 2; i++) {
		dp[1 << i][i] = mp[0][i + 1];
		in[1 << i]--;
		que.push(1 << i);
	}
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = 0; i < n - 2; i++) {
			if (u & (1 << i)) continue;
			for (int j = 0; j < n - 2; j++) {
				if (u & (1 << j)) {
					dp[u | (1 << i)][i] = min(dp[u | (1 << i)][i], dp[u][j] + mp[j + 1][i + 1]);
				}
			}
			in[u | (1 << i)]--;
			if (in[u | (1 << i)] == 1) que.push(u | (1 << i));
		}
	}
	int ans = 0x3fffffffffffffffll;
	for (int j = 0; j < n - 2; j++) {
		ans = min(ans, dp[(1 << (n - 2)) - 1][j] + mp[j + 1][n - 1]);
	}
	printf("%lld", ans);
	return 0;
}