#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXD = 15;
long long dp[MAXD][2][2];
int n, a[MAXD * 2];
bool vis[MAXD][2][2];
long long dfs(int depth, int flg1, int flg2) {
	if (vis[depth][flg1][flg2]) return dp[depth][flg1][flg2];
	if (depth == n - depth + 1) {
		if (flg1 && flg2) return a[depth];
		else if (flg1 == 0) return 10;
		else if (flg1) return a[depth] + 1;
	}
	if (depth > n - depth + 1) {
		if (flg1 && flg2) return 0;
		else return 1;
	}
	vis[depth][flg1][flg2] = 1;
	int up = flg1 ? a[n - depth + 1] : 9;
	long long ans = 0;
	for (int i = 0; i <= up; i++) {
		for (int j = 0; j <= 9; j++) {
			if (i == j || (depth == 1 && i == 0)) continue;
			bool nflg2;
			if (j > a[depth]) nflg2 = 1;
			else if (j < a[depth]) nflg2 = 0;
			else nflg2 = flg2;
			ans += dfs(depth + 1, flg1 && (i == a[n - depth + 1]), nflg2);
		}
	}
	return dp[depth][flg1][flg2] = ans;
}
long long solution(long long x) {
	memset(vis, 0, sizeof vis);
	long long xx = x;
	long long ans = 0;
	int D = 0;
	while (xx) {
		a[++D] = xx % 10;
		xx /= 10;
	}
	n = D;
	ans += dfs(1, 1, 0);
	for (int i = 1; i <= D; i++) {
		a[i] = 9;
	}
	for (n = n - 1; n >= 1; n--) {
		memset(vis, 0, sizeof vis);
		ans += dfs(1, 1, 0);
	}
	return ans;
}
int main() {
	long long a, b;
	scanf("%lld %lld", &a, &b);
	printf("%lld", solution(b) - solution(a - 1));
	return 0;
}