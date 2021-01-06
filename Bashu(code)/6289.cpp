#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#define mod 998244353
using namespace std;
const int MAXN = 100001;
struct edge {
	int to;
	double val;
	int org;
	int nxt;
} edges[MAXN * 10], edges2[MAXN];
int head[MAXN], tot;
int head2[MAXN];
void add(int u, int v, double w, int org) {
	edges[++tot].to = v;
	edges[tot].val = w;
	edges[tot].org = org;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void add2(int u, int v, int w) {
	edges2[++tot].to = v;
	edges2[tot].org = w;
	edges2[tot].nxt = head2[u];
	head2[u] = tot;
}
double dist[MAXN];
bool vis[MAXN];
int pre[MAXN], cao[MAXN];
long long realdist[MAXN];
void SPFA(int S) {
	for (int i = 0; i < MAXN; i++) {
		dist[i] = 21e8;
	}
	priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
	pq.push(make_pair(0, S));
	dist[S] = 0;
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		add2(pre[u], u, cao[u]);
		for (int i = head[u]; i; i = edges[i].nxt) {
			if (dist[edges[i].to] > dist[u] + edges[i].val) {
				pre[edges[i].to] = u;
				cao[edges[i].to] = edges[i].org;
				dist[edges[i].to] = dist[u] + edges[i].val;
				pq.push(make_pair(dist[edges[i].to], edges[i].to));
			}
		}
	}
}
void dfs(int x, int fa) {
	for (int i = head2[x]; i; i = edges2[i].nxt) {
		if (edges2[i].to == fa) continue;
		realdist[edges2[i].to] = realdist[x] * edges2[i].org % mod;
		dfs(edges2[i].to, x);
	}
} 
int main() {
//	freopen("duliu.in", "r", stdin);
//	freopen("duliu.out", "w", stdout);
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, log(w) / log(2), w);
		add(v, u, log(w) / log(2), w);
	}
	tot = 0;
	SPFA(s);
	realdist[s] = 1;
	dfs(s, 0);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int T;
		scanf("%d", &T);
		printf("%lld\n", realdist[T]);
	}
	return 0;
} 