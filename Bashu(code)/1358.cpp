#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
struct edge {
	int to, val, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int Xor[MAXN];
int son[MAXN][2], cnt;
void add(int u, int v, int w) {
	edges[++tot].to = v;
	edges[tot].val = w;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int x, int fa, int w) {
	Xor[x] = Xor[fa] ^ w;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (edges[i].to == fa) continue;
		dfs(edges[i].to, x, edges[i].val);
	}
}
void adda(int str) {
	int root = 1;
	for (int i = 20; ~i; i--) {
		int kk = bool(str & (1 << i));
		if (son[root][kk] == 0) son[root][kk] = ++cnt;
		root = son[root][kk];
	}
}
int ask_YIW(int str) {
	int root = 1, ans = 0;
	for (int i = 20; ~i; i--) {
		int kk = bool(str & (1 << i));
		if (son[root][1 - kk] == 0) ans += (1 << i), root = son[root][kk];
		else root = son[root][1 - kk];
	}
	return ((1 << 21) - 1) ^ ans;
}
int main() {
	cnt = 1;
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
	}
	dfs(0, 0, 0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		adda(Xor[i]);
		ans = max(ans, ask_YIW(Xor[i]));
//		printf("%d %d\n", Xor[i], ask_YIW(Xor[i]));
	}
	printf("%d", ans);
	return 0;
}