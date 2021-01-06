#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 300001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
struct node {
	int x, y, z;
	/**
	 * if type is 1, then add opsition-x y.
	 * if type is 2, query all of sum of between x and y.
	 * z is the key word of order judgement.
	 * first type-1 then type-2.
	 */
	int type, id;
	bool operator < (const node& sec) const {
		return z == sec.z ? type < sec.type : z < sec.z;
	}
} action[MAXN << 1];
int head[MAXN], tot;
int low[MAXN], high[MAXN], size[MAXN], dep[MAXN];
long long c[MAXN], ans[MAXN];
int n;
int uu[MAXN], vv[MAXN];
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int x, int fa) {
	low[x] = ++tot;
	dep[x] = dep[fa] + 1;
	size[x] = 1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (edges[i].to == fa) continue;
		dfs(edges[i].to, x);
		size[x] += size[edges[i].to];
	}
	high[x] = tot;
}
int lowbit(int x) { return x & -x; }
void change(int x, int a) {
	for (int i = x; i <= n; i += lowbit(i)) c[i] += a;
}
long long ask(int x) {
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
int main() {
	int m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	tot = 0;
	dfs(1, 1);
	for (int i = 1; i <= n; i++) {
		action[i].x = low[i];
		action[i].y = size[i] - 1;
		action[i].z = dep[i];
		action[i].type = 1;
	}
	for (int i = n + 1; i <= n + m; i++) {
		scanf("%d %d", &uu[i - n], &vv[i - n]);
		action[i].x = low[uu[i - n]] + 1;
		action[i].y = high[uu[i - n]];
		action[i].z = dep[uu[i - n]] + vv[i - n];
		action[i].type = 2;
		action[i].id = i - n;
	}
	sort(action + 1, action + 1 + n + m);
	for (int i = 1; i <= n + m; i++) {
		if (action[i].type == 1) {
			change(action[i].x, action[i].y);
		}
		else {
			ans[action[i].id] = ask(action[i].y) - ask(action[i].x - 1);
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", ans[i] + ((long long)size[uu[i]] - 1) * min(dep[uu[i]] - 1, vv[i]));
	}
	return 0;
}