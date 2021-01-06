#include <cstdio>
#include <algorithm>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN];
int top[MAXN], pos[MAXN], idx[MAXN], high[MAXN];
int sum[MAXN << 2], lazy[MAXN << 2];
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
	high[u] = tot;
}
void pushdown(int o, int l, int r, int mid) {
	if (lazy[o] != -1) {
		lazy[o << 1] = lazy[o];
		sum[o << 1] = (mid - l + 1) * lazy[o];
		lazy[o << 1 | 1] = lazy[o];
		sum[o << 1 | 1] = (r - mid) * lazy[o];
		lazy[o] = -1;
	}
}
void pushup(int o, int l, int r, int mid) {
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
void build(int o, int l, int r) {
	if (l == r) {
		sum[o] = 0;
		lazy[o] = -1;
	}
	else {
		int mid = l + r >> 1;
		build(o << 1, l, mid);
		build(o << 1 | 1, mid + 1, r);
		pushup(o, l, r, mid);
	}
}
void change(int o, int l, int r, int l1, int r1, long long w) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		sum[o] = (r - l + 1) * w;
		lazy[o] = w;
		return;
	}
	int mid = l + r >> 1;
	pushdown(o, l, r, mid);
	change(o << 1, l, mid, l1, r1, w);
	change(o << 1 | 1, mid + 1, r, l1, r1, w);
	pushup(o, l, r, mid);
}
long long ask(int o, int l, int r, int l1, int r1) {
	if (r1 < l || r < l1) return 0;
	if (l1 <= l && r <= r1) return sum[o];
	int mid = l + r >> 1;
	pushdown(o, l, r, mid);
	return ask(o << 1, l, mid, l1, r1) + ask(o << 1 | 1, mid + 1, r, l1, r1);
}
long long pathinstall(int u, int v) {
	long long ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		ans += pos[u] - pos[top[u]] + 1 - ask(1, 1, n, pos[top[u]], pos[u]);
		change(1, 1, n, pos[top[u]], pos[u], 1);
		u = fa[top[u]];
		// printf("%d %d\n", u, v);
	}
	if (dep[u] < dep[v]) u ^= v ^= u ^= v;
	ans += pos[u] - pos[v] + 1 - ask(1, 1, n, pos[v], pos[u]);
	change(1, 1, n, pos[v], pos[u], 1);
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int f;
		scanf("%d", &f);
		add(f, i);
	}
	dep[0] = fa[0] = 0;
	dfs1(0);
	tot = 0;
	dfs2(0, 0);
	build(1, 1, n);
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		char str[10];
		int b;
		scanf("%s %d", str, &b);
		if (str[0] == 'i') printf("%lld\n", pathinstall(0, b));
		else printf("%lld\n", ask(1, 1, n, pos[b], high[b])), change(1, 1, n, pos[b], high[b], 0);
	}
	return 0;
}