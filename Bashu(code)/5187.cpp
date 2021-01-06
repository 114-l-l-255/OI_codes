#include <iostream>
#include <cstdio>
using namespace std;
#define N 50127
#define B 400
using namespace std;
int n, m, a[N], fa_[N], Log[N], head[N], cnt = 0, dep[N], fa[N][17], dis_[N][B + 1];
struct Edge {
	int to, nxt;
} edges[N << 1];
inline void AddEdge(int x, int y) {
	edges[++cnt].to = y;
	edges[cnt].nxt = head[x];
	head[x] = cnt;
}
void dfs(int x, int prt) {
	int i, y;
	dep[x] = dep[prt] + 1;
	fa_[x] = prt;
	const int u = min(B, dep[x]);
	for(y = fa_[x], i = 1; i <= u; ++i, y = fa_[y]) {
		dis_[x][i] = dis_[y][i];
	}
	for (i = 1; i <= B; ++i) {
		dis_[x][i] += a[x];
	}
	for (i = 1; i <= Log[dep[x]]; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	}
	for (i = head[x]; i; i = edges[i].nxt) {
		if ((y = edges[i].to) != prt) {
			fa[y][0] = x;
			dfs(y, x);
		}
	}
}
inline int jump(int x, int k) {
	while (k) {
		x = fa[x][Log[k & (-k)]];
		k &= (k - 1);
	}
	return x;
}
inline int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = Log[dep[x]]; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y]) {
		x = fa[x][i];	
		}
	}
	if (x == y) return x;
	for (int i = Log[dep[x]]; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}
inline int Get(int x, int p, int k) {
	int res = 0;
	while (dep[x] >= dep[p]) {
		res += a[x];
		x = jump(x, k);
	}
	return res;
}
inline int Ask(int x, int y, int k) {
	int p = LCA(x, y), dis = dep[x] + dep[y] - (dep[p] << 1);
	int Y = jump(y, dis % k), ans = (dis % k) ? a[y] : 0, v = dep[x] - dep[p];
	if (k <= B) {
		ans += dis_[x][k] + dis_[Y][k] - dis_[jump(p, k - v % k)][k] - dis_[jump(p, (k - (dep[Y] - dep[p]) % k) % k)][k];
	}
	else {
		ans += Get(x, p, k) + Get(Y, p, k);
		if (v % k == 0) ans -= a[p];
	}
	return ans;
}
int main() {
	Log[0] = -1;
	for (int i = 1; i < N; i++) {
		Log[i] = Log[i >> 1] + 1;
	}
	scanf("%d %d", &n, &m);
	int i, x, y, k;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		AddEdge(x, y);
		AddEdge(y, x);
	}
	dfs(1, 0);
	while (m--) {
		scanf("%d %d %d", &x, &y, &k);
		printf("%d\n", Ask(x, y, k));
	}
	return 0;
}