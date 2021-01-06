#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 200001;
const int INF = 2147483647;
inline int read() {
	int X = 0, w = 0;
	char ch = 0;
	while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
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
int querysum(int a, int l, int r, int l1, int r1) {
	if (r1 < l1) return 0;
	if (r1 < l || l1 > r) return 0;
	if (l1 <= l && r <= r1) return sum[a];
	int mid = (l + r) >> 1;
	sum[a << 1] += lazy[a] * (mid - l + 1);
	sum[a << 1 | 1] += lazy[a] * (r - mid);
	lazy[a << 1] += lazy[a];
	lazy[a << 1 | 1] += lazy[a];
	lazy[a] = 0;
	return querysum(a << 1, l, mid, l1, r1) + querysum(a << 1 | 1, mid + 1, r, l1, r1);
}
void modify(int a, int l, int r, int p, int p2) {
//	printf("-%d\n", a);
	if (p2 < p) return;
	if (p2 < l || r < p) return;
	if (p <= l && r <= p2) {
		sum[a] += r - l + 1;
		lazy[a]++;
//		printf("%d %d %d\n", a, sum[a], lazy[a]);
		return;
	}
	int mid = (l + r) >> 1;
	sum[a << 1] += lazy[a] * (mid - l + 1);
	sum[a << 1 | 1] += lazy[a] * (r - mid);
	lazy[a << 1] += lazy[a];
	lazy[a << 1 | 1] += lazy[a];
	lazy[a] = 0;
	modify(a << 1, l, mid, p, p2);
	modify(a << 1 | 1, mid + 1, r, p, p2);
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	return;
}
int pathsum(int u, int v) {
//	printf("%d %d %d %d %d %d\n", u, v, pos[u], pos[v], top[u], top[v]);
	if (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		return pathsum(fa[top[u]], v) + querysum(1, 1, n, pos[top[u]], pos[u]);
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	return pos[u] == pos[v] ? 0 : querysum(1, 1, n, pos[u] + 1, pos[v]);
}
void pathmodify(int u, int v) {
//	printf("%d %d %d %d %d %d %d\n", u, v, pos[u], pos[v], top[u], top[v], pos[top[u]]);
	if (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
//		printf("---%d %d\n", pos[top[u]], pos[u]);
		pathmodify(fa[top[u]], v);
		modify(1, 1, n, pos[top[u]], pos[u]);
		return;
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
//	printf("%d %d\n", u, v);
	if (u != v) /*printf("!"), */modify(1, 1, n, pos[u] + 1, pos[v]);
}
int main() {
	n = read();
	int q = read();
	for (int i = 2; i <= n; i++) {
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dep[1] = fa[1] = 1;
	dfs1(1);
	top[1] = idx[1] = pos[1] = 1;
	tot = 0;
	dfs2(1, 1);
	while (q--) {
//		printf("cao\n");
		char op[6];
		scanf("%s", op);
		int u = read();
		int v = read();
		if (op[0] == 'P') pathmodify(u, v);
		else printf("%d\n", pathsum(u, v));
//		for (int i = 1; i <= 7; i++) printf("%d ", sum[i]);
//		printf("\n");
	}
	return 0;
}
/*
4 10000
1 2
1 3
1 4
P 1 2
P 1 3
P 1 4
C 2 3
P 1 2
P 2 3
C 2 3
*/