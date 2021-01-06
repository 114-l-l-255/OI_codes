#include <cstdio>
#include <algorithm>
#include <assert.h>
#define int long long
using namespace std;
const int MAXN = 100001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
struct node {
	int l, r, sum, max;
} tree[3322000];
int head[MAXN], tot;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN];
int top[MAXN], pos[MAXN], idx[MAXN];
int root[MAXN], w[MAXN], c[MAXN];
int n;
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1;
	size[u] = 1;
	son[u] = -1;
	for (int i = head[u]; i; i = edges[i].nxt) {
		if (edges[i].to == fa[u]) continue;
		fa[edges[i].to] = u;
		dfs1(edges[i].to);
		size[u] += size[edges[i].to];
		if (son[u] == -1 || size[edges[i].to] > size[son[u]]) son[u] = edges[i].to;
	}
}
void dfs2(int u, int t) {
	top[u] = t;
	tot++;
	pos[u] = tot;
	idx[tot] = u;
	if (son[u] != -1) dfs2(son[u], t);
	for (int i = head[u]; i; i = edges[i].nxt) {
		if (edges[i].to == fa[u] || edges[i].to == son[u]) continue;
		dfs2(edges[i].to, edges[i].to);
	}
}
void change(int &o, int l, int r, int x, int w) {
	if (x < l || r < x) return;
	if (o == 0) o = ++tot;
	if (l == r) {
		tree[o].max = w;
		tree[o].sum = w;
		return;
	}
	int mid = l + r >> 1;
	change(tree[o].l, l, mid, x, w);
	change(tree[o].r, mid + 1, r, x, w);
	tree[o].sum = tree[tree[o].l].sum + tree[tree[o].r].sum;
	tree[o].max = max(tree[tree[o].l].max, tree[tree[o].r].max);
}
int asksum(int o, int l, int r, int l1, int r1) {
	if (r1 < l || r < l1 || o == 0) return 0;
	if (l1 <= l && r <= r1) return tree[o].sum;
	int mid = l + r >> 1;
	return asksum(tree[o].l, l, mid, l1, r1) + asksum(tree[o].r, mid + 1, r, l1, r1);
}
int askmax(int o, int l, int r, int l1, int r1) {
	if (r1 < l || r < l1 || o == 0) return 0;
	if (l1 <= l && r <= r1) return tree[o].max;
	int mid = l + r >> 1;
	return max(askmax(tree[o].l, l, mid, l1, r1), askmax(tree[o].r, mid + 1, r, l1, r1));
}
int pathsum(int u, int v, int Rt) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += asksum(root[Rt], 1, n, pos[top[u]], pos[u]);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	ans += asksum(root[Rt], 1, n, pos[v], pos[u]);
	// printf("--%d %d %d %d\n", u, v, pos[u], pos[v]);
	return ans;
}
int pathmax(int u, int v, int Rt) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ans = max(ans, askmax(root[Rt], 1, n, pos[top[u]], pos[u]));
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	ans = max(ans, askmax(root[Rt], 1, n, pos[v], pos[u]));
	return ans;
}
signed main() {
	int q;
	scanf("%lld %lld", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &w[i], &c[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%lld %lld", &u, &v);
		add(u, v);
		add(v, u);
	}
	fa[1] = dep[1] = 1;
	dfs1(1);
	tot = 0;
	dfs2(1, 1);
	tot = 0;
	for (int i = 1; i <= n; i++) {
		change(root[c[i]], 1, n, pos[i], w[i]);
		// printf("%d %d %d\n", c[i], pos[i], w[i]);
	}
	// printf("%d %d %d\n", asksum(root[1], 1, n, 1, 1), asksum(root[1], 1, n, 3, 3), asksum(root[1], 1, n, 1, 3));
	for (int i = 1; i <= q; i++) {
		char str[5];
		int a, b;
		scanf("%s %lld %lld", str, &a, &b);
		if (str[1] == 'C') {
			change(root[c[a]], 1, n, pos[a], 0);
			// printf("%d %d %d\n", c[a], pos[a], 0);
			change(root[b], 1, n, pos[a], w[a]);
			// printf("%d %d %d\n", b, pos[a], w[a]);
			c[a] = b;
		}
		if (str[1] == 'W') {
			change(root[c[a]], 1, n, pos[a], b);
			// printf("%d %d %d\n", c[a], pos[a], b);
			w[a] = b;
		}
		if (str[1] == 'S') {
			printf("%lld\n", pathsum(a, b, c[a]));
			assert(c[a] == c[b]);
		}
		if (str[1] == 'M') {
			printf("%lld\n", pathmax(a, b, c[a]));
			assert(c[a] == c[b]);
		}
	}
	return 0;
}