#include <cstdio>
#include <algorithm>
#include <cstring>
#include<iostream>
using namespace std;
const int MAXN = 5001;
int depth[MAXN], depthtot[MAXN];
struct edge {
	int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int x, int fa) {
	depth[x] = depth[fa] + 1;
	depthtot[depth[x]]++;
//	printf("(%d %d)\n", depth[x], depthtot[depth[x]]);
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (edges[i].to == fa) continue;
		dfs(edges[i].to, x);
	}
}
//long long dp[MAXN][3];
long long dp1[MAXN], dp2[MAXN];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
//		memset(depthtot, 0, sizeof depthtot);
//		depth[0] = 0;
//		dfs(i, 0);
//		memset(dp, 0, sizeof dp);
//		for (int j = 1; j <= n; j++) {
//			dp[j][0] = 1;
//		}
//		for (int j = 1; j <= n; j++) {
//			for (int k = 3; k >= 1; k--) {
//				dp[j][k] += dp[j][k - 1] * depthtot[j];
//			}
//		}
//		for (int j = 1; j <= n; j++) {
//			ans += dp[j][3];
//			printf("%d ", ans);
//		}
//		printf("\n");
			memset(dp1, 0, sizeof dp1);
			memset(dp2, 0, sizeof dp2);
		for (int j = head[i]; j; j = edges[j].nxt) {
			memset(depthtot, 0, sizeof depthtot);
			depth[i] = 0;
			dfs(edges[j].to, i);
//			for (int k = 1; k <= n; k++) {
//				printf("%d %d\n", k, depthtot[k]);
//			}
			for (int k = 1; k <= n; k++) {
				ans += dp2[k] * depthtot[k];
				dp2[k] += dp1[k] * depthtot[k];
				dp1[k] += depthtot[k];
//				cout<<depthtot[1]<<endl;
//				printf("%d %lld %lld %lld %d\n", k, ans, dp2[k], dp1[k], depthtot[k]);
			}
//			printf("\n");
		}
//		printf("---\n");
	}
	printf("%lld", ans);
	return 0;
}