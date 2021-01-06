#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 200001;
const int MAXM = 200001;
struct edge {
	int to, val, nxt;
} edges[MAXM << 1];
int head[MAXN], tot;
int n, m;
int t0, t1, t2;
int S, E;
void add(int u, int v, int w) {
	edges[++tot].to = v;
	edges[tot].val = w;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
namespace SubTask1 {
	int dist[1001];
	bool vis[1001];
	void Dijk() {
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
		memset(dist, 0x3f, sizeof dist);
		dist[S] = 0;
		pq.push(make_pair(0, S));
		while (!pq.empty()) {
			int u = pq.top().second;
			pq.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (int i = head[u]; i; i = edges[i].nxt) {
				if (dist[edges[i].to] > dist[u] + edges[i].val) {
					dist[edges[i].to] = dist[u] + edges[i].val;
					pq.push(make_pair(dist[edges[i].to], edges[i].to));
				}
			}
		}
	}
}
namespace SubTask3 {
	int sum[MAXN], f[MAXN], id[MAXN];
	bool vis[MAXN];
	int ans = 0x7fffffff;
	void check() {
		int node = E;
		priority_queue<int> pq;
		while (!pq.empty()) pq.pop();
		while (node != S) {
			if (edges[id[node]].val <= t2) {
				pq.push(edges[id[node]].val);
			}
			node = f[node];
		}
		int ans_ = 0;
		int tt0 = t0;
		while (!pq.empty() && t0 >= t1) {
			ans_ += pq.top();
			pq.pop();
			t0 -= t1;
		}
		t0 = tt0;
		ans = min(ans, sum[E] - ans_);
	}
	void dfs(int x, int fa) {
		f[x] = fa;
		vis[x] = 1;
		if (x == E) {
			check();
			vis[x] = 0;
			return;
		}
		for (int i = head[x]; i; i = edges[i].nxt) {
			if (edges[i].to == fa) continue;
			if (vis[edges[i].to]) continue;
			sum[edges[i].to] = sum[x] + edges[i].val;
			id[edges[i].to] = i;
			dfs(edges[i].to, x);
		}
		vis[x] = 0;
	}
}
namespace SubTask4 {
	long long dist[MAXN * 51];
	bool vis[MAXN * 51];
	void Dijkstra() {
		priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
		memset(dist, 0x3f, sizeof dist);
		dist[S] = 0;
		pq.push(make_pair(0, S));
		while (!pq.empty()) {
			int u = pq.top().second;
//			printf("%d\n", u);
			pq.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			int uu = u % (n + 1);
			int k = u / (n + 1);
			for (int i = head[uu]; i; i = edges[i].nxt) {
				int yy = edges[i].to + k * (n + 1);
				if (edges[i].val <= t2 && k < t0 / t1) {
					if (dist[yy + n + 1] > dist[u]) {
						dist[yy + n + 1] = dist[u];
						pq.push(make_pair(dist[yy + n + 1], yy + n + 1));
					}
				}
				if (dist[yy] > dist[u] + edges[i].val) {
					dist[yy] = dist[u] + edges[i].val;
					pq.push(make_pair(dist[yy], yy));
				}
			}
			if (k < t0 / t1) {
				if (dist[u + n + 1] > dist[u]) {
					dist[u + n + 1] = dist[u];
					pq.push(make_pair(dist[u + n + 1], u + n + 1));
				}
			}
		}
	}
}
signed main() {
	#ifdef LEMON_JUDGE
		freopen("camera.in", "r", stdin);
		freopen("camera.out", "w", stdout);
	#endif
	scanf("%lld %lld %lld %lld %lld", &n, &m, &t0, &t1, &t2);
	scanf("%lld %lld", &S, &E);
	if (t0 < t1) {
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%lld %lld %lld", &u, &v, &w);
			add(u, v, w);
			add(v, u, w);
		}
		using namespace SubTask1;
		Dijk();
		printf("%lld", dist[E]);
	}
	else if (n >= m) {
		using namespace SubTask3;
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%lld %lld %lld", &u, &v, &w);
			add(u, v, w);
			add(v, u, w);
		}
		dfs(S, -1);
		printf("%lld", ans);
	}
	else {
		using namespace SubTask4;
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%lld %lld %lld", &u, &v, &w);
			add(u, v, w);
			add(v, u, w);
		}
		Dijkstra();
		printf("%lld", dist[E + (n + 1) * (t0 / t1)]);
	}
	return 0;
}