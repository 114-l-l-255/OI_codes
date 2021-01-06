#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 100005;
const int maxm = 200005;
struct e {
	int u, v, nxt;
} edge[maxm];
struct node {
	int u, d;
	node() {}
	node(int u_, int d_) {
		u = u_;
		d = d_;
	}
	bool operator < (const node &a) const {
		return d < a.d;
	}
	bool operator > (const node &a) const {
		return d > a.d;
	}
};
int n, k, t, cnt, ans;
int head[maxn], dep[maxn], fa[maxn];
bool vis[maxn];
priority_queue<node> q;
void adde(int u, int v) {
	edge[++cnt] = (e) {
		u, v, head[u]
	};
	head[u] = cnt;
}
void dfs1(int u) {
	int v;
	for (int i = head[u]; i; i = edge[i].nxt) {
		v = edge[i].v;
		if (!dep[v]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v);
		}
	}
}
int find(int x) {
	int stp = 1;
	while (stp <= k) {
		stp++;
		x = fa[x];
	}
	return x;
}
void dfs2(int u, int rt, int stp) {
	int v;
	vis[u] = true;
	if(stp == k) return ;
	for (int i = head[u]; i; i = edge[i].nxt) {
		v = edge[i].v;
		if (v != rt) dfs2(v, u, stp + 1);
	}
}
int main() {
	int x, y, u, v;
	scanf("%d %d %d", &n, &k, &t);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		adde(x, y);
		adde(y, x);
	}
	dep[1] = 1;
	fa[1] = 1;
	dfs1(1);
	for (int i = 1; i <= n; i++) q.push(node(i, dep[i]));
	while (q.size()) {
		u = q.top().u;
		q.pop();
		if (vis[u]) continue;
		ans++;
		v = find(u);
		dfs2(v, v, 0);
	}
	printf("%d", ans);
	return 0;
}