#pragma GCC optimize("O3")
#pragma G++ optimize("O3")
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define d(k) (1<<(k))
#define N 802
using namespace std;
int n, m, q, s[N][N];
char op[10];
short mx[10][10][N][N], mn[10][10][N][N], lg[N];
inline int rd(int& X) {
	char ch = X = 0;
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) X = (X << 3) + (X << 1) + ch - '0';
	return X;
}
inline short gMax(int x1, int y1, int x2,int y2) {
	short k1 = lg[x2 - x1 + 1], k2 = lg[y2 - y1 + 1];
	x2 -= d(k1) - 1;
	y2 -= d(k2) - 1;
	return max(max(mx[k1][k2][x1][y1], mx[k1][k2][x2][y1]), max(mx[k1][k2][x1][y2], mx[k1][k2][x2][y2]));
}
inline short gMin(int x1,int y1,int x2,int y2) {
	short k1 = lg[x2 - x1 + 1], k2 = lg[y2-y1+1];
	x2 -= d(k1) - 1;
	y2 -= d(k2) - 1;
	return min(min(mn[k1][k2][x1][y1], mn[k1][k2][x2][y1]), min(mn[k1][k2][x1][y2], mn[k1][k2][x2][y2]));
}
int main() {
	rd(n);
	rd(m);
	*lg = -1;
	for (int i = 1; i < N; ++i)
		lg[i] = lg[i - 1] + (!(i & (i - 1)));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			rd(s[i][j]);
			mx[0][0][i][j] = mn[0][0][i][j] = s[i][j];
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	for (int r = 0; r <= lg[n]; ++r)
		for (int c = 0; c <= lg[m]; ++c)
			if (r + c)
				for (int i = 1; i + (1 << r) - 1 <= n; ++i)
					for (int j = 1; j + (1 << c) - 1 <= m; ++j)
						if (r) {
							mn[r][c][i][j] = min(mn[r - 1][c][i][j], mn[r - 1][c][i + d(r - 1)][j]);
							mx[r][c][i][j] = max(mx[r - 1][c][i][j], mx[r - 1][c][i + d(r - 1)][j]);
						} else {
							mn[r][c][i][j] = min(mn[r][c - 1][i][j], mn[r][c - 1][i][j + d(c - 1)]);
							mx[r][c][i][j] = max(mx[r][c - 1][i][j], mx[r][c - 1][i][j + d(c - 1)]);
						}
	for (int x, y, dx, dy, k = rd(q); q--;) {
		scanf("%s", op);
		rd(x);
		rd(y);
		rd(dx);
		rd(dy);
		++dx;
		++dy;
		if (*op == 'S') printf("%d\n", s[dx][dy] - s[x][dy] - s[dx][y] + s[x][y]);
		else {
			++x;
			++y;
			if (op[1] == 'A')
				printf("%d\n", gMax(x, y, dx, dy));
			else printf("%d\n", gMin(x, y, dx, dy));
		}
	}
}