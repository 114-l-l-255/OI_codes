#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 200001;
const int MAXM = 400001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int fa[MAXN][18];
int depth[MAXN];
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs1(int x) {
	if (x == 1) depth[1] = 1;
	else depth[x] = depth[fa[x][0]] + 1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (x != 1 && edges[i].to == fa[x][0]) continue;
		fa[edges[i].to][0] = x;
		dfs1(edges[i].to);
	}
}
int lca(int u, int v) {
	if (depth[u] < depth[v]) u ^= v ^= u ^= v;
	for (int i = 17; i >= 0; i--) {
		if (depth[u] - (1 << i) >= depth[v]) {
			u = fa[u][i];
//			printf("-----%d %d\n", u, i);
		}
	}
	if (u == v) return u;
	for (int i = 17; i >= 0; i--) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
//			printf("-----%d %d %d\n", u, v, i);
		}
	}
	return fa[u][0];
}
int main() {
//	freopen("light.in", "r", stdin);
//	freopen("light.out", "w", stdout);
	int n, q;
	scanf("%d %d %*d", &n, &q);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	memset(fa, -1, sizeof fa);
	dfs1(1);
	int tmp = int(log(n) / log(2));
	for (int j = 1; j <= tmp; j++) {
		for (int i = 1; i <= n; i++) {
			if (fa[i][j - 1] == -1) fa[i][j] = -1;
			else fa[i][j] = fa[fa[i][j - 1]][j - 1];
//			printf("%d ", fa[i][j]); 
		}
//		printf("\n");
	}
	for (int i = 0; i < q; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		int lcaa = lca(b, c), lcab = lca(a, c), lcac = lca(a, b);
		if (lcaa == lcab && lcac == lcab) {
			printf("%d\n", depth[b] - depth[lcab] + 1);
		}
		else {
			if (lcaa == lcac) {
				printf("%d\n", depth[lcab] - depth[lcaa] + depth[b] - depth[lcaa] + 1);
			}
			else {
				printf("%d\n", depth[b] - max(depth[lcaa], depth[lcac]) + 1);
			}
		}
//		printf("%d %d %d\n", lcaa, lcab, lcac);
	}
	return 0;
}