#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1000001;
int depth[MAXN], size[MAXN], dp[MAXN];
int n;
struct edge {
	int to, nxt;
} edges[MAXN * 2];
int head[MAXN], tot;
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs1(int x, int fa, int dep) {
	depth[x] = dep;
	size[x] = 1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa) continue;
		dfs1(v, x, dep + 1);
		size[x] += size[v];
	}
}
void dfs2(int x, int fa) {
	dp[x] = dp[fa] + n - size[x] - size[x];
	for (int i = head[x]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if (v == fa) continue;
		dfs2(v, x);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs1(1, 0, 0);
	for (int i = 1; i <= n; i++) {
		dp[1] += depth[i];
	}
	dfs2(1, 0);
	int ans = 1;
	for (int i = 2; i <= n; i++) {
		if (dp[ans] < dp[i]) ans = i;
	}
	printf("%d", ans);
	return 0;
}