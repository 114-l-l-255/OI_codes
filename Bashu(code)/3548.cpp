#include <cstdio>
const int MAXN = 1005, MAXX = 50001;
struct node {
	int x, y;
} grass[MAXN];
int c, n, map[MAXN][MAXN];
int cx[MAXX + 5], cy[MAXX + 5], nx[MAXN], ny[MAXN], tx, ty;
int judge(int x) {
	for (int i = cx[x]; i <= tx; ++i)
		for (int j = cy[x]; j <= ty; ++j) {
			int k = 0, l = 0;
			if (nx[i] > x)
				k = cx[nx[i] - x];
			if (ny[j] > x)
				l = cy[ny[j] - x];
			if (map[i][j] - map[k][j] - map[i][l] + map[k][l] >= c)
				return 1;
		}
	return 0;
}
int main() {
	scanf("%d %d", &c, &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &grass[i].x, &grass[i].y);
		++cx[grass[i].x], ++cy[grass[i].y];
	}
	for (int i = 1; i <= MAXX; ++i) {
		if (cx[i])
			nx[++tx] = i;
		cx[i] = tx;
		if (cy[i])
			ny[++ty] = i;
		cy[i] = ty;
	}
	for (int i = 1; i <= n; ++i)
		++map[cx[grass[i].x]][cy[grass[i].y]];
	for (int i = 1; i <= tx; ++i)
		for (int j = 1; j <= ty; ++j)
			map[i][j] += map[i - 1][j] + map[i][j - 1] - map[i - 1][j - 1];
	int l = 0, r = MAXX;
	while (l < r - 1) {
		int mid = (l + r) >> 1;
		if (judge(mid))
			r = mid;
		else
			l = mid;
	}
	printf("%d", r);
	return 0;
}