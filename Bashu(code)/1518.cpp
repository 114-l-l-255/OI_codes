#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
// #define NDEBUG
#include <assert.h>
#define int long long
using namespace std;
const int N = 200001;
const int INF = 2147483647000000000ll;
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
int val[N], sum[N << 2], tott[N << 2], maxx[N << 2], lazy[N << 1];
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
		sum[a << 1] += (mid - l + 1 - tott[a << 1] * 2) * lazy[a];
		if (maxx[a << 1] != -INF) maxx[a << 1] += lazy[a];
		if (maxx[a << 1] >= 0) puts("shik"), assert(0);
		lazy[a << 1 |1] += lazy[a];
		sum[a << 1 | 1] += (r - mid - tott[a << 1 | 1] * 2) * lazy[a];
		if (maxx[a << 1 | 1] != -INF) maxx[a << 1 | 1] += lazy[a];
		if (maxx[a << 1] >= 0) puts("shik"), assert(0);
		lazy[a] = 0;
	}
}
void up(int a, int l, int r, int mid) {
	sum[a] = sum[a << 1] + sum[a << 1 | 1];
	tott[a] = tott[a << 1] + tott[a << 1 | 1];
	maxx[a] = max(maxx[a << 1], maxx[a << 1 | 1]);
}
void build(int a, int l, int r) {
	if (l == r) {
		sum[a] = val[idx[l]] < 0 ? -val[idx[l]] : val[idx[l]];
		tott[a] = val[idx[l]] < 0 ? 1 : 0;
		maxx[a] = val[idx[l]] < 0 ? val[idx[l]] : -INF;
		return;
	}
	int mid = (l + r) >> 1;
	build(a << 1, l, mid);
	build(a << 1 | 1, mid + 1, r);
	up(a, l, r, mid);
	return;
}
int query(int a, int l, int r, int l1, int r1) {
	if (r1 < l || l1 > r) return 0;
	if (l1 <= l && r <= r1) return sum[a];
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	return query(a << 1, l, mid, l1, r1) + query(a << 1 | 1, mid + 1, r, l1, r1);
}
void modify(int, int, int, int, int, int);
void brutemodify(int a, int l, int r, int l1, int r1, int v) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		if (maxx[a] + v < 0 || maxx[a] == -INF) modify(a, l, r, l1, r1, v);
		else if (l == r) {
			sum[a] = v - sum[a];
			maxx[a] = -INF;
			lazy[a] += v;
			tott[a] = 0;
		}
		else {
			int mid = (l + r) >> 1;
			down(a, l, r, mid);
			brutemodify(a << 1, l, mid, l1, r1, v);
			brutemodify(a << 1 | 1, mid + 1, r, l1, r1, v);
			up(a, l, r, mid);
		}
		return;
	}
	puts("shik");
	assert(0);
}
void modify(int a, int l, int r, int l1, int r1, int v) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		if (maxx[a] != -INF && maxx[a] + v >= 0) brutemodify(a, l, r, l1, r1, v);
		else if (l == r) {
			sum[a] += (1 - tott[a] * 2) * v;
			maxx[a] = maxx[a] == -INF ? -INF : maxx[a] + v;
			lazy[a] += v;
		}
		else {
			sum[a] += (r - l + 1 - tott[a] * 2) * v;
			maxx[a] = maxx[a] == -INF ? -INF : maxx[a] + v;
			lazy[a] += v;
		}
		return;
	}
	int mid = (l + r) >> 1;
	down(a, l, r, mid);
	modify(a << 1, l, mid, l1, r1, v);
	modify(a << 1 | 1, mid + 1, r, l1, r1, v);
	up(a, l, r, mid);
	return;
}
void pathmodify(int u, int v, int w) {
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
int pathquery(int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int t = u;
			u = v;
			v = t;
		}
		ans += query(1, 1, n, pos[top[u]], pos[u]);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int t = u;
		u = v;
		v = t;
	}
	ans += query(1, 1, n, pos[u], pos[v]);
	return ans;
}
signed main() {
	// freopen("1518.in", "r", stdin);
	// freopen("1518.out", "w", stdout);
	n = read();
	int q = read();
	for (int i = 1; i <= n; i++) {
		val[i] = read();
	}
	for (int i = 1; i < n; i++) {
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
		// for (int i = 1; i <= 15; i++) {
		// 	printf("%lld %lld %lld %lld\n", sum[i], tott[i], maxx[i], lazy[i]);
		// 	// assert(maxx[i] < 0);
		// }
		// printf("\n");
		char op[6];
		scanf("%s", op);
		int u = read(), v = read(), w;
		if (op[0] == '1') w = read(), pathmodify(u, v, w);
		else if (op[0] == '2') printf("%lld\n", pathquery(u, v));
	}
	// for (int i = 1; i <= 15; i++) {
	// 	printf("%lld %lld %lld %lld\n", sum[i], tott[i], maxx[i], lazy[i]);
	// }
	// printf("\n");
	return 0;
}