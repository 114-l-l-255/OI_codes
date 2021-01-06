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
int val[N], valtmp[N], nodetmp[N], maxx[N << 2], lazy1[N << 2], lazy2[N << 2];
void dfs1(int u) {
	size[u] = 1;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fa[u]) continue;
		nodetmp[(i + 1) >> 1] = v;
		val[edge[i].to] = valtmp[(i + 1) >> 1];
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
	if (lazy1[a]) {
		maxx[a << 1] = 0;
		lazy1[a << 1] = 1;
		lazy2[a << 1] = 0;
		maxx[a << 1 | 1] = 0;
		lazy1[a << 1 | 1] = 1;
		lazy2[a << 1 | 1] = 0;
		lazy1[a] = 0;
	}
	if (lazy2[a]) {
		maxx[a << 1] += lazy2[a];
		lazy2[a << 1] += lazy2[a];
		maxx[a << 1 | 1] += lazy2[a];
		lazy2[a << 1 | 1] += lazy2[a];
		lazy2[a] = 0;
	}
}
void up(int a, int l, int r, int mid) {
	maxx[a] = max(maxx[a << 1], maxx[a << 1 | 1]);
}
void build(int a, int l, int r) {
	if (l == r) {
		maxx[a] = val[idx[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(a << 1, l, mid);
	build(a << 1 | 1, mid + 1, r);
	up(a, l, r, mid);
	return;
}
int query(int a, int l, int r, int l1, int r1) {
	if (r1 < l || l1 > r) return -0x7fffffff;
	if (l1 <= l && r <= r1) return maxx[a];
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	return max(query(a << 1, l, mid, l1, r1), query(a << 1 | 1, mid + 1, r, l1, r1));
}
void modify1(int a, int l, int r, int l1, int r1, int v) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		maxx[a] = v;
		lazy1[a] = 1;
		lazy2[a] = v;
		return;
	}
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	modify1(a << 1, l, mid, l1, r1, v);
	modify1(a << 1 | 1, mid + 1, r, l1, r1, v);
	up(a, l, r, mid);
	return;
}
void modify2(int a, int l, int r, int l1, int r1, int v) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		maxx[a] += v;
		lazy2[a] += v;
		return;
	}
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	modify2(a << 1, l, mid, l1, r1, v);
	modify2(a << 1 | 1, mid + 1, r, l1, r1, v);
	up(a, l, r, mid);
	return;
}
void pathmodify1(int u, int v, int w) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		modify1(1, 1, n, pos[top[u]], pos[u], w);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	if (pos[u] != pos[v]) modify1(1, 1, n, pos[u] + 1, pos[v], w);
}
void pathmodify2(int u, int v, int w) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		modify2(1, 1, n, pos[top[u]], pos[u], w);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	if (pos[u] != pos[v]) modify2(1, 1, n, pos[u] + 1, pos[v], w);
}
int pathquery(int u, int v) {
	int ans = -0x7fffffff;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		ans = max(ans, query(1, 1, n, pos[top[u]], pos[u]));
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	if (pos[u] != pos[v]) ans = max(ans, query(1, 1, n, pos[u] + 1, pos[v]));
	return ans;
}
int main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read();
		int v = read();
		valtmp[i] = read();
		add(u, v);
		add(v, u);
	}
	dep[1] = fa[1] = 1;
	dfs1(1);
	tot = 0;
	dfs2(1, 1);
	build(1, 1, n);
	while (1) {
		char op[6];
		scanf("%s", op);
		if (op[0] == 'S') break;
		int u = read(), v = read(), w;
		if (op[0] == 'A') w = read(), pathmodify2(u, v, w);
		else if (op[0] == 'M') printf("%d\n", pathquery(u, v));
		else if (op[1] == 'h') modify1(1, 1, n, pos[nodetmp[u]], pos[nodetmp[u]], v);
		else if (op[1] == 'o') w = read(), pathmodify1(u, v, w);
	}
	return 0;
}