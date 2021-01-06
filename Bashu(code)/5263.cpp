#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;
const int MAXN = 1000001;
struct edge {
    int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int low[MAXN], high[MAXN], times;
long long pt[MAXN], c[MAXN];
int n;
void add(int u, int v) {
    edges[++tot].to = v;
    edges[tot].nxt = head[u];
    head[u] = tot;
}
void dfs(int x, int f) {
    low[x] = ++times;
    for (int i = head[x]; i; i = edges[i].nxt) {
        if (edges[i].to == f) continue;
        dfs(edges[i].to, x);
    }
    high[x] = times;
}
int lowbit(int x) { return x & -x; }
void add_(int x, long long a) {
    for (int i = x; i <= n; i += lowbit(i)) c[i] += a;
}
long long ask(int x) {
    long long ans = 0;
    for (int i = x; i; i -= lowbit(i)) ans += c[i];
    return ans;
}
signed main() {
    int q, rt;
    scanf("%lld %lld %lld", &n, &q, &rt);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &pt[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%lld %lld", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(rt, 0);
    for (int i = 1; i <= n; i++) {
        add_(low[i], (long long)pt[i]);
    }
    // printf("---\n");
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d ", low[i], high[i]);
    // }
    // printf("\n---\n");
    // int LnN = int(floor(log2(n)));
    // for (int i = 1; i <= LnN; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         if (fa[j][i - 1] == -1) fa[j][i] = -1;
    //         else fa[j][i] = fa[fa[j][i - 1]][i - 1];
    //     }
    // }
    // int rt = 1;
    for (int i = 0; i < q; i++) {
        int a, b, c;
        scanf("%lld %lld", &a, &b);
        if (a == 1) {
            scanf("%lld", &c);
            add_(low[b], (long long)c);
        }
        else {
            printf("%lld\n", ask(high[b]) - ask(low[b] - 1));
        }
    }
    return 0;
}