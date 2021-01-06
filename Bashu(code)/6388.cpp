#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 200001;
struct edge {
	int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int link[MAXN];
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
int size[MAXN], esize[MAXN];
int mini[MAXN], maxi[MAXN], cnt;
bool selfloop[MAXN];
int R[MAXN];
bool dfs(int x, int fa, int id) {
//	printf("%d %d %d\n", x, fa, id);
//	printf("%d", x);
size[x] = 1;
	mini[cnt] = min(mini[cnt], x);
	maxi[cnt] = max(maxi[cnt], x);
	bool ans = 0;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (edges[i].to == x) return 1;
		if (size[edges[i].to]) {
			if (i != id && i != link[id]) return 1;
			continue;
		}
		ans |= dfs(edges[i].to, x, i);
		if (ans) return 1;
	}
	return 0;
}
int main() {
//	freopen("magic.in", "r", stdin);
//	freopen("magic.out", "w", stdout);
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
		link[tot] = tot - 1;
		link[tot - 1] = tot;
	}
	cnt = -1;
	for (int i = 1; i <= n; i++) {
		R[i] = 0x7fffffff;
	}
	for (int i = 1; i <= n; i++) {
		if (size[i] == 0) {
			cnt++;
			mini[cnt] = 0x7fffffff;
//	printf("?");
//			printf("%d %d\n", size[i], esize[i]);
			if (!dfs(i, -1, -1)) {
				R[mini[cnt]] = maxi[cnt];
			}
		}
	}
//	for (int i = 1; i <= n; i++) {
//		printf("%d ", R[i]);
//	}
//	printf("\n");
	for (int i = n - 1; i >= 1; i--) {
		R[i] = min(R[i + 1], R[i]);
	}
//	for (int i = 1; i <= n; i++) {
//		printf("%d ", R[i]);
//	}
//	printf("\n");
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		bool flag = R[l] > r;
		printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}