#include <cstdio>
using namespace std;
const int MAXN = 1001, MAXM = 205;
int f[2][MAXM][MAXM], c[MAXM][MAXM], p[MAXN], m, n;
int min(int x, int y) {
	return x < y ? x : y;
}
int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &c[i][j]);
	int k, tmp = 1;
	while (~scanf("%d", &k)) p[tmp++] = k;
	n = tmp - 1;
	for (int i = 0; i <= 1; i++) {
		for (int x = 1; x <= m; x++) {
			for (int y = 1; y <= m; y++) {
				f[i][x][y] = 0x3f3f3f3f;
			}
		}
	}
	p[0] = 3, f[0][1][2] = 0;
	for (int i_ = 0; i_ < n; i_++) {
		int i = i_ & 1;
		for (int x = 1; x <= m; x++)
			for (int y = 1; y <= m; y++)
				f[1 - i][x][y] = 0x3f3f3f3f;
		for (int x = 1; x <= m; x++)
			for (int y = 1; y <= m; y++) {
				if (x == y || x == p[i_] || y == p[i_]) continue;
				f[1 - i][x][y] = min(f[1 - i][x][y], f[i][x][y] + c[p[i_]][p[i_ + 1]]);
				f[1 - i][p[i_]][y] = min(f[1 - i][p[i_]][y], f[i][x][y] + c[x][p[i_ + 1]]);
				f[1 - i][x][p[i_]] = min(f[1 - i][x][p[i_]], f[i][x][y] + c[y][p[i_ + 1]]);
			}
	}
//	puts("!");
	int ans = 0x3f3f3f3f;
	for (int x = 1; x <= m; x++)
		for (int y = 1; y <= m; y++) {
			if (x == y || x == p[n] || y == p[n]) continue;
			ans = min(ans, f[n & 1][x][y]);
		}
	printf("%d", ans);
	return 0;
}