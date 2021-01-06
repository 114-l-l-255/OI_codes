#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int N, S, np, tot, Clock, last[MAXN], dep[MAXN], dfn[MAXN * 10];
int mark[MAXN], V[MAXN], Time[MAXN], fa_first[MAXN * 10], vis[MAXN];
struct edge {
	int to, pre;
} E[MAXN];
 
char c;
void scan(int &x) {
	for (c = getchar(); c < '0' || c > '9'; c = getchar());
	for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
} 
void addedge(int u, int v) {
	E[++np] = (edge){v, last[u]};
	last[u] = np;
}
 
void init() {
	memset(last, 0, sizeof(last));
	memset(mark, 0, sizeof(mark));
	memset(vis, 0, sizeof(vis));
	memset(vis, 0, sizeof(vis));
	np = 0;
	tot = 0;
	Clock = 0;
}
void dfs(int i) {
	dfn[++tot] = i;
	fa_first[tot] = 1;
	if (S == i) mark[i] = 1;
	for (int p = last[i]; p; p = E[p].pre) {
		int j = E[p].to;
		dep[j] = dep[i] + 1;
		dfs(j);
		if (mark[j]) mark[i] = 1; 
		dfn[++tot] = i;
		fa_first[tot] = 0;
	}
	if (mark[i]) Time[i] = Clock++;
}
int main() {
	int T, i, u, v;
	scan(T);
	while (T--) {
		init();
		scan(N);
		for (u = 1; u <= N; u++) {
			scan(i);
			for (int k = 1; k <= i; k++) {
				scan(V[k]);
			}
			for(int k = i; k >= 1; k--) {
				addedge(u, V[k]);
			}
		}
		scan(S);
		dep[1] = 1;
		dfs(1);
		int ans = 0;
		for (i = 1; i <= tot; i++) {
			u = dfn[i];
			if (mark[u] && i - Time[u] > 0 && fa_first[i - Time[u]]) {
				v = dfn[i - Time[u]];
				if (mark[v] && dep[v] <= dep[u] && !vis[v]) {
					ans++;
					vis[v] = 1;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}