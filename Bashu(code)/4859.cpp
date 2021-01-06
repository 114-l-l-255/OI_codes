#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 1249577;
const int MAXM = 300001;
const int LUCK = 1048575;
struct edge {
	int to, nxt;
	bool val;
} edges[MAXM];
vector<int> G[LUCK + 1];
int head[MAXN], tot;
int val[MAXN];
int back[LUCK + 1];
//0~1048575, 1048576~1248575 
void add(int u, int v, bool w) {
	edges[++tot].to = v;
	edges[tot].val = w;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
int dist[MAXN];
bool vis[MAXN];
void Dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	memset(dist, 0x3f, sizeof dist);
	dist[LUCK + 1] = 0;
	pq.push(make_pair(0, LUCK + 1));
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (vis[u]) continue;
//		printf("%d\n", u);
		vis[u] = 1;
		if (u > LUCK) {
			for (int i = head[u]; i; i = edges[i].nxt) {
				if (dist[edges[i].to] > dist[u] + edges[i].val) {
					dist[edges[i].to] = dist[u] + edges[i].val;
					pq.push(make_pair(dist[edges[i].to], edges[i].to));
				}
			}
			if (dist[val[u - LUCK]] > dist[u] + 1) {
				dist[val[u - LUCK]] = dist[u] + 1;
				pq.push(make_pair(dist[val[u - LUCK]], val[u - LUCK]));
			}
		}
		else {
			int uu = u;
			while (uu) {
				int lowbit = uu & -uu;
				int nw = u ^ lowbit;
				if (dist[nw] > dist[u]) {
					dist[nw] = dist[u];
					pq.push(make_pair(dist[nw], nw));
				}
				uu -= lowbit;
			}
//			if (back[u]) {
//				if (dist[back[u] + LUCK] > dist[u]) {
//					dist[back[u] + LUCK] = dist[u];
//					pq.push(make_pair(dist[back[u] + LUCK], back[u] + LUCK));
//				}
//			}
			for (int i = 0; i < G[u].size(); i++) {
				if (dist[G[u][i] + LUCK] > dist[u]) {
					dist[G[u][i] + LUCK] = dist[u];
					pq.push(make_pair(dist[G[u][i] + LUCK], G[u][i] + LUCK));
				}
			}
		}
	}
} 
int main() {
//	freopen("walk.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
//	int ans = 0;
//	for (int i = 0; i < (1 << 20); i++) {
//		int ii = i;
//		while (ii) {
//			int lowbit = ii & -ii;
//			add(i, i ^ lowbit, 0);
//			ans++;
//			ii -= lowbit;
//		}
//	}
//	printf("%d", ans);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
//		add(i + LUCK, val[i], 1);
//		add(val[i], i + LUCK, 0);
//		back[val[i]] = i;
		G[val[i]].push_back(i);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u + LUCK, v + LUCK, 1);
	}
	Dijkstra();
	for (int i = LUCK + 1; i <= LUCK + n; i++) {
		printf("%d\n", dist[i] == 0x3f3f3f3f ? -1 : dist[i]);
	}
	return 0;
}