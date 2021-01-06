#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXM = 100001;
struct seq {
	int l, r;
} s[MAXM];
struct edge {
	int to, nxt;
} edges[MAXM];
int head[MAXM * 2], ttt;
int size[MAXM * 2];
bool vis[MAXM * 2];
int n, m;
int nums[MAXM * 2], tot;
void add(int u, int v) {
	edges[++ttt].to = v;
	edges[ttt].nxt = head[u];
	head[u] = ttt;
}
void dfs(int x) {
	vis[x] = 1;
	size[x] = 1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		if (vis[edges[i].to]) continue;
		dfs(edges[i].to);
		size[x] += size[edges[i].to];
	}
}
long long qkpow(int b) {
	long long ans = 1;
	long long a = 2;
	while (b) {
		if (b & 1) ans = (ans * a) % 1000000007;
		b >>= 1;
		a = (a * a) % 1000000007;
	}
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(vis, 0, sizeof vis);
		memset(head, 0, sizeof head);
		ttt = 0;
		tot = 0;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &s[i].l, &s[i].r);
			s[i].r++;
			nums[tot++] = s[i].l;
			nums[tot++] = s[i].r;
		}
		sort(nums, nums + tot);
		int nn = unique(nums, nums + tot) - nums;
		for (int i = 0; i < m; i++) {
			s[i].l = lower_bound(nums, nums + nn, s[i].l) - nums;
			s[i].r = lower_bound(nums, nums + nn, s[i].r) - nums;
//			printf("%d %d---\n", s[i].l, s[i].r);
			add(s[i].l, s[i].r);
			add(s[i].r, s[i].l);
		}
		long long ans = 1;
		for (int i = 0; i < nn; i++) {
			if (!vis[i]) dfs(i), ans = (ans * qkpow(size[i] - 1)) % 1000000007;
//			printf("%lld\n", ans);
//			printf("!");
		}
		printf("%lld\n", ans);
	}
}