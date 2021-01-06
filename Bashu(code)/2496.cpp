#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 5003;
int a[MAXN][MAXN], pre[MAXN][MAXN];
int main() {
	int n, R;
	scanf("%d %d", &n, &R);
	for (int i = 0; i < n; i++) {
		int x, y, c;
		scanf("%d %d %d", &x, &y, &c);
		x++, y++;
		a[x][y] += c;
	}
	for (int i = 1; i <= 5001; i++) {
		for (int j = 1; j <= 5001; j++) {
			pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + a[i][j];
		}
	}
	int ans = 0;
	for (int i = R; i <= 5001; i++) {
		for (int j = R; j <= 5001; j++) {
			ans = max(ans, pre[i][j] - pre[i - R][j] - pre[i][j - R] + pre[i - R][j - R]);
		}
	}
	if (R > 5001) ans = max(ans, pre[5001][5001]);
	printf("%d", ans);
	return 0;
}