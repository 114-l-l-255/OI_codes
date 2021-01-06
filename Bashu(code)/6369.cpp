#include <bits/stdc++.h>
const int N = 105;
const int inf = 0x3f3f3f3f;
int n, m, C, T, A[N], B[N];
int G[N][N][21], p[N], c[N];
int f[N][N * N], D[N][N];
int main() {
	scanf("%d %d %d %d", &n, &m, &C, &T);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &p[i], &c[i]);
		c[i] = std::min(c[i], C);
		for (int j = 1; j <= n; ++j) {
			G[i][j][0] = i == j ? 0 : -inf;
		}
	}
	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		G[a][b][0] = std::max(G[a][b][0], c);
	}
	for (int k = 1; k <= 20; ++k) {
		for (int a = 1; a <= n; ++a) {
			for (int b = 1; b <= n; ++b) {
				G[a][b][k] = -inf;
				for (int s = 1; s <= n; ++s) {
					G[a][b][k] = std::max(G[a][b][k], G[a][s][k - 1] + G[s][b][k - 1]);
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			A[j] = i == j ? 0 : -inf;
		for (int k = 20; k + 1; k--) {
			if ((c[i] >> k) & 1) {
				for (int j = 1; j <= n; ++j) {
					B[j] = -inf;
					for (int d = 1; d <= n; ++d)
						B[j] = std::max(B[j], A[d] + G[d][j][k]);
				}
				for (int j = 1; j <= n; ++j) {
					A[j] = B[j];
				}
			}
		}
		for (int j = 1; j <= n; ++j) {
			D[i][j] = A[j];
		}
	}
	for (int i = 0; i <= n * n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i >= p[j])
				for (int k = 1; k <= n; ++k)
					f[j][i] = std::max(f[j][i], f[k][i - p[j]] + D[j][k]);
		}
	}
	while (T--) {
		int s, q, d;
		scanf("%d %d %d", &s, &q, &d);
		int l = 0, r = q + 1;
		int ans = q + 1;
		while (l + 1 < r) {
			int mid = l + r >> 1;
			if (f[s][mid] >= d) {
				ans = mid;
				r = mid;
			} else l = mid;
		}
		printf("%d\n", q - ans);
	}
	return 0;
}