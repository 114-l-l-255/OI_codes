#include <bits/stdc++.h>
#define L(x) x << 1
#define R(x) x << 1 | 1
using namespace std;
struct rec {
	int nxt, to;
} e[150000];
struct node {
	int x, y, v;
	pair<int, int> p;
} sta[70001];
int head[70001], cnt;
int n, m, t;
int f[70001], dep[70001];
pair<int, int> st[70001];
int fa[70001], depth[70001], top[70001], size[70001], son[70001];
vector<pair<int, int> > pos[500000];
int ans[70001];
void add(int x, int y) {
	e[++cnt].nxt = head[x];
	e[cnt].to = y;
	head[x] = cnt;
}
int find(int x) {
	return x == f[x] ? x : find(f[x]);
}
void dfs1(int x) {
	size[x] = 1;
	for (int i = head[x]; i; i = e[i].nxt)
		if (e[i].to != fa[x]) {
			fa[e[i].to] = x;
			depth[e[i].to] = depth[x] + 1;
			dfs1(e[i].to);
			size[x] += size[e[i].to];
			if (size[e[i].to] > size[son[x]]) son[x] = e[i].to;
		}
}
void dfs2(int x, int tp) {
	top[x] = tp;
	if (!son[x]) return;
	dfs2(son[x], tp);
	for (int i = head[x]; i; i = e[i].nxt)
		if (!top[e[i].to]) dfs2(e[i].to, e[i].to);
}
int LCA(int x, int y) {
	while (top[x] != top[y]) {
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return depth[x] < depth[y] ? x : y;
}
int dis(int x, int y) {
	return depth[x] + depth[y] - (depth[LCA(x, y)] << 1);
}
void build(int x, int l, int r, int L, int R, int u, int v) {
	if (r < L || R < l)return;
	if (L <= l && r <= R) {
		pos[x].push_back(make_pair(u, v));
		return;
	}
	int mid = (l + r) >> 1;
	build(L(x), l, mid, L, R, u, v);
	build(R(x), mid + 1, r, L, R, u, v);
}
void merge(int x, int y, int &flag) {
	x = find(x);
	y = find(y);
	int res = 0, d;
	pair<int, int> mzz;
	if (res < (d = dis(st[x].first, st[x].second))) res = d, mzz = make_pair(st[x].first, st[x].second);
	if (res < (d = dis(st[x].first, st[y].first))) res = d, mzz = make_pair(st[x].first, st[y].first);
	if (res < (d = dis(st[x].first, st[y].second))) res = d, mzz = make_pair(st[x].first, st[y].second);
	if (res < (d = dis(st[x].second, st[y].first))) res = d, mzz = make_pair(st[x].second, st[y].first);
	if (res < (d = dis(st[x].second, st[y].second))) res = d, mzz = make_pair(st[x].second, st[y].second);
	if (res < (d = dis(st[y].first, st[y].second))) res = d, mzz = make_pair(st[y].first, st[y].second);
	flag = max(flag, res);
	if (dep[x] < dep[y]) swap(x, y);
	sta[++t] = (node) {
		x, y, 0, st[x]
	};
	if (dep[x] == dep[y]) {
		dep[x]++;
		sta[t].v = 1;
	}
	f[y] = x;
	st[x] = mzz;
}
void del(int x) {
	while (x < t) {
		dep[sta[t].x] -= sta[t].v;
		f[sta[t].y] = sta[t].y;
		st[sta[t].x] = sta[t].p;
		t--;
	}
}
void solve(int x, int l, int r, int res) {
	int now = t;
	for (int i = 0; i < pos[x].size(); i++)
		merge(pos[x][i].first, pos[x][i].second, res);
	if (l == r) {
		ans[l] = res;
		del(now);
		return;
	}
	int mid = (l + r) >> 1;
	solve(L(x), l, mid, res);
	solve(R(x), mid + 1, r, res);
	del(now);
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v, l, r;
		scanf("%d %d %d %d", &u, &v, &l, &r);
		add(u, v);
		add(v, u);
		build(1, 1, n, l, r, u, v);
	}
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		st[i] = make_pair(i, i);
	}
	solve(1, 1, n, 0);
	while (m--) {
		int x;
		scanf("%d", &x);
		printf("%d\n", ans[x]);
	}
	return 0;
}