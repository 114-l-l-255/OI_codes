#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN = 100001;
struct edge {
	int to, nxt;
} edges[MAXN]; int head[MAXN], tot;
struct ticket {
	int k, w, nxt;
} tics[MAXN]; int headd[MAXN], tott;
int fa[MAXN], dp[MAXN];
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void addd(int u, int k, int w) {
	tics[++tott].k = k;
	tics[tott].w = w;
	tics[tott].nxt = headd[u];
	headd[u] = tott;
}
void topsort(int S = 1) {
	memset(dp, 0x7f, sizeof dp);
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == S) dp[u] = 0;
		else {
			for (int i = headd[u]; i; i = tics[i].nxt) {
				int ans = 0x7f7f7f7f;
				for (int j = fa[u], k = 0; j && k < tics[i].k; j = fa[j], k++) {
					ans = min(ans, dp[j]);
				}
				if (ans != 0x7f7f7f7f) dp[u] = min(dp[u], tics[i].w + ans);
			}
		}
		for (int i = head[u]; i; i = edges[i].nxt) {
			q.push(edges[i].to);
		}
	}
}
int main() {
//	freopen("party.in", "r", stdin);
//	freopen("party.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int v, u;
		scanf("%d %d", &v, &u);
		fa[v] = u;
		add(u, v);
	}
	for (int i = 1; i <= m; i++) {
		int v, k, w;
		scanf("%d %d %d", &v, &k, &w);
		addd(v, k, w);
	}
	topsort();
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int ask;
		scanf("%d", &ask);
		printf("%d\n", dp[ask]);
	}
	return 0;
}
/*
7 7
3 1
2 1
7 6
6 3
5 3
4 3
7 2 3
7 1 1
2 3 5
3 6 2
4 2 4
5 3 10
6 1 20
3
5
6
7
*/