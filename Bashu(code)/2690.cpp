#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ri register int
const int MAXN = 75;
using namespace std;
inline int read() {
	int ret = 0, f = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') f ^= (ch == '-'), ch = getchar();
	while (ch >= '0' && ch <= '9') ret *= 10, ret += ch - '0', ch = getchar();
	return f ? -ret : ret;
}
struct node {
	int v, p, w;
	bool operator < (const node &rhs) const {
		return v < rhs.v;
	}
} a[MAXN];
int n, kk, b[MAXN], sum[MAXN];
int f[MAXN][MAXN][MAXN];
int main() {
	n = read();
	kk = read();
	for (ri i = 1; i <= n; i++) a[i].v = read();
	for (ri i = 1; i <= n; i++) a[i].p = read();
	for (ri i = 1; i <= n; i++) a[i].w = read();
	sort(a + 1, a + n + 1);
	for (ri i = 1; i <= n; i++) b[i] = a[i].p;
	sort(b + 1, b + n + 1);
	int t = unique(b + 1, b + n + 1) - b - 1;
	for (ri i = 1; i <= n; i++) a[i].p = lower_bound(b + 1, b + t + 1, a[i].p) - b;
	for (ri i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].w;
	memset(f, 0x3f, sizeof(f));
	for (ri i = 0; i <= n; i++)
		for (ri k = 0; k <= t; k++) f[k][i + 1][i] = 0;
	for (ri i = 1; i <= n; i++)
		for (ri k = 0; k <= t; k++)
			if (a[i].p > k) f[k][i][i] = a[i].w;
			else f[k][i][i] = a[i].w + kk;
	for (ri len = 1; len < n; len++)
		for (ri l = 1; l + len <= n; l++) {
			int r = l + len;
			for (ri k = t; k >= 0; k--)
				for (ri d = l; d <= r; d++) {
					if (a[d].p > k) f[k][l][r] = min(f[k][l][r], f[a[d].p][l][d - 1] + f[a[d].p][d +1 ][r] + sum[r] - sum[l - 1]);
					f[k][l][r] = min(f[k][l][r], f[k][l][d - 1] + f[k][d + 1][r] + sum[r] - sum[l - 1] + kk);
				}
		}
	printf("%d", f[0][1][n]);
	return 0;
}