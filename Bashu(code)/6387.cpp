#include <cctype>
#include <cstdio>
#define LL long long
#define N 100010
#define mod 1000000007
using namespace std;
int n, head[N], k, tot, fa[N];
struct edge {
	int next, to;
} edges[N << 1];
inline void add(int u, int v) {
	edges[++tot] = (edge){head[u], v};
	head[u] = tot;
	return;
}
inline int read() {
	register int x = 0;
	register char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}
LL f[N], g[N], siz[N][11], mul[N][11], crs[N];
LL ksm(LL x, LL y) {
    LL ans = 1;
	while (y) {
		if (y & 1) {
			ans = (ans * x) % mod;
		}
		x = (x * x) % mod;
		y >>= 1;
	}
    return ans;
}
void dp(int x) {
    for (register int i = 0; i <= k; i++) {
    	siz[x][i] = mul[x][i] = 1;
	}
    for (register int i = head[x]; i; i = edges[i].next) {
        int y = edges[i].to;
        if (y == fa[x]) continue;
        fa[y] = x;
        dp(y);
        for (register int j = 1; j <= k; j++) {
        	siz[x][j] += siz[y][j - 1];
			(mul[x][j] *= mul[y][j - 1] * siz[y][j - 1] % mod) %= mod;
		}
    }
    return;
}
void dfs(int x) {
    int now = x;
	f[x] = crs[k] = siz[x][k];
    for (register int i = k - 1; i && fa[now]; i--, now = fa[now]) {
		f[x] += siz[fa[now]][i] - siz[now][i - 1];
		crs[i] = f[x];
	}
    if (fa[now]) f[x]++;
    now = x;
	g[x] = mul[x][k] * f[x] % mod;
    for (register int i = k - 1; i && fa[now]; i--, now = fa[now]) {
		(g[x] *= mul[fa[now]][i] * ksm(mul[now][i - 1] * siz[now][i - 1] % mod, mod - 2) % mod) %= mod;
		(g[x] *= f[x] - crs[i + 1]) %= mod;
	}
    for (register int i = head[x]; i; i = edges[i].next) {
        int y = edges[i].to;
        if (y == fa[x]) continue;
        dfs(y);
    }
    return;
}
signed main() {
    n = read();
    k = read();
    for (register int i = 1; i < n; i++) {
    	int x, y;
        x = read();
        y = read();
        add(x, y);
		add(y, x);
    }
    dp(1);
	dfs(1);
    for (register int i = 1; i <= n; i++) printf("%lld ", f[i]);
    printf("\n");
    for (register int i = 1; i <= n; i++) printf("%lld ", g[i]);
}