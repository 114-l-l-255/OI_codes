#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>
#include <iostream>
#include <iomanip>
#define int long long
using namespace std;
const int MAXN = 300001;
struct edge {
	int to, nxt;
} edges[MAXN], edges2[MAXN];
int head[MAXN], head2[MAXN], tot;
int w[MAXN], w2[MAXN], color[MAXN], nums[MAXN], colors;
int dfn[MAXN], low[MAXN], timet;
stack<int> sta; bool instack[MAXN];
int ind[MAXN], dp[MAXN];
long long n;
void add1(int u, int v) { edges[++tot].to = v; edges[tot].nxt = head[u]; head[u] = tot; }
void add2(int u, int v) { edges2[++tot].to = v; edges2[tot].nxt = head2[u]; head2[u] = tot; }
void tarjan(int x) {
	dfn[x] = low[x] = ++timet;
	sta.push(x); instack[x] = 1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (!dfn[edges[i].to]) {
			tarjan(edges[i].to);
			low[x] = min(low[x], low[edges[i].to]);
		}
		else if (instack[edges[i].to]) {
			low[x] = min(low[x], low[edges[i].to]);
		}
	}
	if (dfn[x] == low[x]) {
		int y, col = ++colors;
		do {
			y = sta.top();
			sta.pop();
			instack[y] = 0;
			color[y] = col;
			w2[col] += w[y];
			nums[col]++; 
		} while (y != x);
	}
}
void make_graph() {
	//反向建图
	tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = head[i]; j; j = edges[j].nxt) {
			if (color[i] != color[edges[j].to]) {
				add2(color[edges[j].to], color[i]);
				ind[color[i]]++;
//				printf("%d\n", color[i]);
			}
		}
	} 
}
long long topsort() {
	queue<int> que;
	for (int i = 1; i <= colors; i++) {
		if (ind[i] == 0) que.push(i); 
		dp[i] = w2[i];
	}
	long long ans = 0;
	while (!que.empty()) {
//	printf("F***\n");
		int u = que.front();
		que.pop();
		ans += dp[u] * nums[u];
//		printf("%lld %lld %lld %lld\n", u, ans, dp[u], nums[u]);
		for (int i = head2[u]; i; i = edges2[i].nxt) {
			if (--ind[edges2[i].to] == 0) {
				dp[edges2[i].to] += dp[u];
//				printf("%d %d\n", dp[edges2[i].to], dp[u]);
				que.push(edges2[i].to);
			}
		}
	}
	return ans;
}
signed main() {
//	freopen("meaning.in", "r", stdin);
//	freopen("meaning.out", "w", stdout);
	scanf("%lld", &n);
//	printf("%lld\n", n);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%lld", &a);
		add1(i, a);
	}
//	printf("F***\n");
//	printf("%lld\n", n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
	}
//	printf("%lld\n", n);
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) tarjan(i);
	}
//	printf("%lld\n", n);
//	for (int i = 1; i <= n; i++) {
//		printf("%lld ", color[i]);
//	}
//	printf("\n");
	make_graph();
	long long ans = topsort();
//	printf("%lld\n", ans);
//	printf("%.6lf\n", ans * 1.0 / n);
	cout << fixed << setprecision(6) << ans * 1.0 / n;
	return 0;
}