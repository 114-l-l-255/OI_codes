#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
//dp[1024][100][101]: 还剩i(状压)饮料，做到第j道题(已做)，上一个影响是第k题的总得分(做了j) 
double dp[1024][101][101];
double high[1024];
int x[10], y[10];
int c[500001];
struct node {
	int a, s, z;
} pro[500001];
struct edge {
	int to, nxt;
} edges[1024*1024];
int head[1024], tot;
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
int main() {
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	if (n == 0) {
		int oops = -1;
		for (int i = 0; i < m; i++) {
			scanf("%d", &y[i]);
		}
		for (int i = 0; i < k - 1; i++) {
			scanf("%d", &c[i]);
		}
		long double score = 0;
		for (int i = 0; i < k; i++) {
			scanf("%d %d %d", &pro[i].a, &pro[i].s, &pro[i].z);
			long double pra = 0;
			if (oops == -1) {
				pra = y[pro[i].s - 1];
			} 
			else {
				pra = y[pro[i].s - 1] * (1.0 - c[i - oops - 1] / 100.0);
			}
//			printf("%.2Lf %d\n", pra, y[pro[i].s - 1]); 
			long double proscore = 1.0 - max((long double)0.0, 1.0 - pra * 1.0 / pro[i].z) * max((long double)0.0, 1.0 - pra * 1.0 / pro[i].z);
			if (proscore < 0.64) oops = i;
			score += proscore * pro[i].a;
		}
//		printf("%.2Lf", score);
		cout << fixed << setprecision(2) << score;
	}
	else {
//		printf("SHIK");
		for (int i = 0; i < n; i++) {
			scanf("%d", &x[i]);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &y[i]);
		}
		for (int i = 0; i < k - 1; i++) {
			scanf("%d", &c[i]);
		}
		int n2 = (1 << n);
		high[0] = 1;
		add(0, 0);
		for (int i = 1; i < n2; i++) {
			int LLog = log(i) / log(2);
			high[i] = high[i - (1 << LLog)] * (1.0 + x[LLog] * 1.0 / 100.0);
//			int ii = i;
			for (int j = 0; j < i; j++) {
				if ((i & j) == j) add(i, j);
			}
			add(i, i);
		}
//		for (int i = 0; i < n2; i++) {
//			printf("%d %.2lf\n", i, high[i]);
//		}
//		printf("\n-----------------------------\n");
		for (int i = 0; i < n2; i++) {
			for (int j = 0; j <= k; j++) {
				for (int l = 0; l <= k; l++) {
					dp[i][j][l] = -1;
				}
			}
		} 
		dp[n2 - 1][0][0] = 0;
		for (int i = 1; i <= k; i++) {
			scanf("%d %d %d", &pro[i].a, &pro[i].s, &pro[i].z);
			for (int j = 0; j < n2; j++) {
				for (int l = 0; l < i; l++) {
					if (dp[j][i - 1][l] == -1) continue;
					for (int o = head[j]; o; o = edges[o].nxt) {
						double pra = high[j - edges[o].to], proscore = 0;
						if (l == 0) {
							pra *= y[pro[i].s - 1];
						} 
						else {
							pra *= y[pro[i].s - 1] * (1.0 - c[i - l - 1] / 100.0);
						}
						proscore = 1.0 - max(0.0, 1.0 - pra / pro[i].z) * max(0.0, 1.0 - pra / pro[i].z);
//						if (fabs(dp[j][i - 1][l] + proscore * pro[i].a - 705906) <= 2) printf("%d %d %d---%d %d %d:%.2lf %.2lf\n", j, i - 1, l, edges[o].to, i, proscore < 0.64 ? i : l, dp[j][i - 1][l], proscore < 0.64 ? dp[edges[o].to][i][i] : dp[edges[o].to][i][l]);
						if (proscore < 0.64) {
							dp[edges[o].to][i][i] = max(dp[edges[o].to][i][i], dp[j][i - 1][l] + proscore * pro[i].a);
						}
						else {
							dp[edges[o].to][i][l] = max(dp[edges[o].to][i][l], dp[j][i - 1][l] + proscore * pro[i].a);
						}
					}
				}
			}
		}
//		for (int j = 0; j <= k; j++) {
//			for (int i = 0; i < n2; i++) {
//				for (int l = 0; l <= k; l++) {
////					if (dp[i][j][l] != -1) printf("dp[%d][%d][%d] = %.2lf\n", i, j, l, dp[i][j][l]);
////					if (fabs(dp[i][j][l] - 685513.67) <= 1) printf("%d %d %d\n", i, j, k);
//				}
////				printf("\n");
//			}
////			printf("\n------------------------\n");
//		}
		double ans = 0;
		for (int i = 0; i <= k; i++) {
			ans = max(ans, dp[0][k][i]);
		}
		cout << fixed << setprecision(2) << ans;
	}
	return 0;
}
