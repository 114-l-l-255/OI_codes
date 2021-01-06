#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
unsigned long long h[MAXN][MAXN], bs[MAXN][MAXN];
struct edge {
	int hd;
	unsigned long long to;
	int nxt;
} edges[MAXN * MAXN];
int head[20090314], tot;
void insert(unsigned long long x) {
	int hed = x % 20090314;
	for (int i = head[hed]; i; i = edges[i].nxt) {
		if (edges[i].to == x) {
			return;
		}
	}
	edges[++tot].hd = hed;
	edges[tot].to = x;
	edges[tot].nxt = head[hed];
	head[hed] = tot;
}
bool find(unsigned long long x) {
	int hed = x % 20090314;
	for (int i = head[hed]; i; i = edges[i].nxt) {
		if (edges[i].to == x) {
			return 1;
		}
	}
	return 0;
}
unsigned long long Hash(int lx, int rx, int ly, int ry) {
	return h[rx][ry] - h[lx - 1][ry] * bs[rx - lx + 1][0] - h[rx][ly - 1] * bs[0][ry - ly + 1] + h[lx - 1][ly - 1] * bs[rx - lx + 1][ry - ly + 1];
}
int main() {
	int n, m, a, b;
	scanf("%d %d %d %d", &n, &m, &a, &b);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 && j == 0) bs[i][j] = 1;
			else if (i && j == 0) bs[i][j] = bs[i - 1][j] * bs[0][m];
			else bs[i][j] = bs[i][j - 1] * 3;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1llu", &h[i][j]);
			h[i][j] += h[i][j - 1] * 3 + h[i - 1][j] * bs[0][m] - h[i - 1][j - 1] * bs[0][m] * 3;
//			printf("%llu ", h[i][j]);
		}
//		printf("\n");
	}
//	printf("All handle That Is Valid:\n");
	for (int i = 1; i + a - 1 <= n; i++) {
		for (int j = 1; j + b - 1 <= m; j++) {
			insert(Hash(i, i + a - 1, j, j + b - 1));
//			printf("%llu\n", Hash(i, i + a - 1, j, j + b - 1));
		}
	}
	int q;
	scanf("%d", &q);
	for (int i_ = 0; i_ < q; i_++) {
		for (int i = 1; i <= a; i++) {
			for (int j = 1; j <= b; j++) {
				scanf("%1llu", &h[i][j]);
				h[i][j] += h[i][j - 1] * 3 + h[i - 1][j] * bs[0][m] - h[i - 1][j - 1] * bs[0][m] * 3;
			}
		}
//		printf("This handle is: %llu\n", h[a][b]);
		printf("%d\n", find(h[a][b]));
	}
	return 0;
}