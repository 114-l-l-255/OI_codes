#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 30001;
const int INF = 2147483647;
inline int read() {
	int X = 0, w = 0;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		w |= ch == '-';
		ch = getchar();
	}
	while (ch>='0'&&ch<='9') X = (X << 3) + (X << 1) + (ch ^ 48),ch = getchar();
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
int val[N], sum[N << 2], maxn[N << 2];
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
void dfs2(int u,int anc) {
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
void build(int a, int l, int r) {
	if (l == r) {
		sum[a] = maxn[a] = val[idx[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(a << 1, l, mid);
	build(a << 1 | 1, mid + 1, r);
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	maxn[a] = max(maxn[a << 1], maxn[a << 1 | 1]);
	return;
}
int querysum(int a, int l, int r, int l1, int r1) {
	if (r1 < l || l1 > r) return 0;
	if (l1 <= l && r <= r1) return sum[a];
	int mid = (l + r) >> 1;
	return querysum(a << 1, l, mid, l1, r1) + querysum(a << 1 | 1, mid + 1, r, l1, r1);
}
int querymax(int a, int l, int r, int l1, int r1) {
	if (r1 < l || l1 > r) return -INF;
	if (l1 <= l && r <= r1) return maxn[a];
	int mid = (l + r) >> 1;
	return max(querymax(a << 1, l, mid, l1, r1), querymax(a << 1 | 1, mid + 1, r, l1, r1));
}
void modify(int a, int l, int r, int p, int v) {
	if (p < l || r < p)return;
	if (l == r) {
		sum[a] = maxn[a] = v;
		return;
	}
	int mid = (l + r) >> 1;
	modify(a << 1, l, mid, p, v);
	modify(a << 1 | 1, mid + 1, r, p, v);
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	maxn[a] = max(maxn[a << 1], maxn[a << 1 | 1]);
	return;
}
int pathsum(int u, int v) {
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
	return querysum(1, 1, n, pos[u], pos[v]);
}
int pathmax(int u, int v) {
	if (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		return max(pathmax(fa[top[u]], v), querymax(1, 1, n, pos[top[u]], pos[u]));
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	return querymax(1, 1, n, pos[u], pos[v]);
}
int main() {
	n = read();
	for (int i = 2; i <= n; i++) {
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++) val[i] = read();
	dep[1] = fa[1] = 1;
	dfs1(1);
	top[1] = idx[1] = pos[1] = 1;
	tot = 0;
	dfs2(1, 1);
	build(1, 1, n);
	int q = read();
	while (q--) {
		char op[6];
		scanf("%s", op);
		int u = read();
		int v = read();
		if (op[0] == 'C') modify(1, 1, n, pos[u], v);
		else if (op[1] == 'S') printf("%d\n", pathsum(u, v));
		else printf("%d\n", pathmax(u, v));
//		for (int i = 1; i <= 7; i++) printf("%d ", maxn[i]);
//		printf("\n");
	}
	return 0;
}