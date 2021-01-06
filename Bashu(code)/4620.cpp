#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 100001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN];
int top[MAXN], pos[MAXN], idx[MAXN], high[MAXN];
long long a[MAXN], minx[MAXN << 2], lazy[MAXN << 2];
int _fa[MAXN][17], n;
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
	pos[u] = ++tot;
	idx[tot] = u;
	if (son[u] != -1) dfs2(son[u], t);
	for (int i = head[u]; i; i = edges[i].nxt) {
		if (edges[i].to == fa[u] || edges[i].to == son[u]) continue;
		dfs2(edges[i].to, edges[i].to);
	}
	high[u] = tot;
}
void pushdown(int o, int l, int r, int mid) {
	if (lazy[o]) {
		lazy[o << 1] = lazy[o];
		minx[o << 1] = lazy[o];
		lazy[o << 1 | 1] = lazy[o];
		minx[o << 1 | 1] = lazy[o];
		lazy[o] = 0;
	}
}
void pushup(int o, int l, int r, int mid) {
	minx[o] = min(minx[o << 1], minx[o << 1 | 1]);
}
void build(int o, int l, int r) {
	if (l == r) {
		minx[o] = a[idx[l]];
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
		minx[o] = w;
		lazy[o] = w;
		return;
	}
	int mid = l + r >> 1;
	pushdown(o, l, r, mid);
	change(o << 1, l, mid, l1, r1, w);
	change(o << 1 | 1, mid + 1, r, l1, r1, w);
	pushup(o, l, r, mid);
	return;
}
long long ask(int o, int l, int r, int l1, int r1) {
	if (r1 < l || r < l1) return 0x7fffffffffffffffll;
	if (l1 <= l && r <= r1) return minx[o];
	int mid = l + r >> 1;
	pushdown(o, l, r, mid);
	return min(ask(o << 1, l, mid, l1, r1), ask(o << 1 | 1, mid + 1, r, l1, r1));
}
void pathchange(int u, int v, int w) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		change(1, 1, n, pos[top[u]], pos[u], w);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	change(1, 1, n, pos[v], pos[u], w);
}
int main() {
	scanf("%d", &n);
	int m;
	scanf("%d", &m);
	for (int i = 2; i <= n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	int r;
	scanf("%d", &r);
	fa[r] = r;
	dfs1(r);
	for (int i = 1; i <= n; i++) {
		_fa[i][0] = fa[i];
	}
	int Logn = log2(n);
	for (int i = 1; i <= Logn; i++) {
		for (int j = 1; j <= n; j++) {
			_fa[j][i] = _fa[_fa[j][i - 1]][i - 1];
		}
	}
	tot = 0;
	dfs2(r, r);
	build(1, 1, n);
	for (int i = 0; i < m; i++) {
//		printf("-----\n");
//		for (int i = 1; i <= 9; i++) {
//			printf("%d %d\n", sum[i], lazy[i]);
//		}
//		printf("-----\n");
		int aa, bb, cc, dd;
		scanf("%d %d", &aa, &bb);
		if (aa == 1) {
			r = bb;
		}
		if (aa == 2) {
			scanf("%d %d", &cc, &dd);
			pathchange(bb, cc, (long long)dd);
		}
		if (aa == 3) {
			if (bb == r) {
				printf("%lld\n", ask(1, 1, n, 1, n));
			}
			else if (dep[bb] == dep[r]) {
				printf("%lld\n", ask(1, 1, n, pos[bb], high[bb]));
			}
			else {
				int jp1 = bb, jp2 = r;
				if (dep[jp1] < dep[jp2]) swap(jp1, jp2);
				for (int j = Logn; ~j; j--) {
					if (dep[jp1] - (1 << j) > dep[jp2]) {
						jp1 = _fa[jp1][j];
					}
				}
				if (fa[jp1] != jp2) {
					printf("%lld\n", ask(1, 1, n, pos[bb], high[bb]));
				}
				else if (jp2 == r) {
					printf("%lld\n", ask(1, 1, n, pos[bb], high[bb]));
				}
				else {
					long long ans = 0x7fffffffffffffffll;
//					printf("%d %d %d %d\n", pos[jp1] - 1, high[jp1] + 1, ask(1, 1, n, 1, pos[jp1] - 1), ask(1, 1, n, high[jp1] + 1, n));
					if (pos[jp1] != 1) ans = min(ans, ask(1, 1, n, 1, pos[jp1] - 1));
					if (high[jp1] != n) ans = min(ans, ask(1, 1, n, high[jp1] + 1, n));
					printf("%lld\n", ans);
				}
			}
		}
	}
	return 0;
}