#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 50001;
const int INF = 2147483647;
inline int read() {
	int X = 0, w = 0;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		w |= ch == '-';
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + (ch ^ 48),ch = getchar();
	return w ? -X : X;
}
struct node {
	int to;
	int nxt;
} edge[N << 1];
int head[N], cnt = 0, n;
inline void add(int u, int v) {
	cnt++;
	edge[cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
	return;
}
int fa[N], dep[N], size[N], son[N], top[N], pos[N], idx[N];
int val[N], sum[N << 2], lazy[N << 2];
void dfs1(int u) {
	size[u] = 1;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fa[u]) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v);
		size[u] += size[v];
		if (!son[u] || size[v] > size[son[u]]) son[u] = v;
	}
	return;
}
int tot;
void dfs2(int u, int anc) {
	tot++;
	pos[u] = tot;
	idx[tot] = u;
	top[u] = anc;
	if (!son[u]) return;
	dfs2(son[u], anc);
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}
void down(int a, int l, int r, int mid) {
	if (lazy[a]) {
		lazy[a << 1] += lazy[a];
		lazy[a << 1 | 1] += lazy[a];
		sum[a << 1] += (mid - l + 1) * lazy[a];
		sum[a << 1 | 1] += (r - mid) * lazy[a];
		lazy[a] = 0;
	}
}
void build(int a, int l, int r) {
	if (l == r) {
		sum[a] = val[idx[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(a << 1, l, mid);
	build(a << 1 | 1, mid + 1, r);
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	return;
}
int querysum(int a, int l, int r, int l1, int r1) {
	if (r1 < l || l1 > r) return 0;
	if (l1 <= l && r <= r1) return sum[a];
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	return querysum(a << 1, l, mid, l1, r1) + querysum(a << 1 | 1, mid + 1, r, l1, r1);
}
void modify(int a, int l, int r, int p, int p2, int v) {
	if (p2 < l || r < p) return;
	if (p <= l && r <= p2) {
		sum[a] += v * (r - l + 1);
		lazy[a] += v;
		return;
	}
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	modify(a << 1, l, mid, p, p2, v);
	modify(a << 1 | 1, mid + 1, r, p, p2, v);
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	return;
}
void pathmodify(int u, int v, int w) {
//	if (top[u] != top[v]) {
//		if (dep[top[u]] < dep[top[v]]) {
//			int t = u;
//			u = v;
//			v = t;
//		}
//		pathmodify(fa[top[u]], v, w);
//		modify(1, 1, n, pos[top[u]], pos[u], w);
//		return;
//	}
//	if (dep[u] > dep[v]) {
//		int t = u;
//		u = v;
//		v = t;
//	}
//	modify(1, 1, n, pos[u], pos[v], w);
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		modify(1, 1, n, pos[top[u]], pos[u], w);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	modify(1, 1, n, pos[u], pos[v], w);
}
int main() {
	n = read();
	read();
	int q = read();
	for (int i = 1; i <= n; i++) val[i] = read();
	for (int i = 2; i <= n; i++) {
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dep[1] = fa[1] = 1;
	dfs1(1);
	tot = 0;
	dfs2(1, 1);
	build(1, 1, n);
	while (q--) {
		char op[6];
		scanf("%s", op);
		int u = read();
		int v, w;
		if (op[0] == 'I') v = read(), w = read(), pathmodify(u, v, w);
		else if (op[0] == 'D') v = read(), w = read(), pathmodify(u, v, -w);
		else printf("%d\n", querysum(1, 1, n, pos[u], pos[u]));
//		for (int i = 1; i <= 7; i++) printf("%d ", maxn[i]);
//		printf("\n");
	}
	return 0;
}