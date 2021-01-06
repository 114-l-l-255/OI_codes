#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1000001;
struct edge {
    int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int low[MAXN], high[MAXN], times;
long long pt[MAXN], c1[MAXN], c2[MAXN];
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
int lowbit(int x) {
    return x & (-x);
}
void add_(int x, long long w) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c1[i] += w;
        c2[i] += w * (x - 1);
    }
}
long long ask(int x) {
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        ans += x * c1[i] - c2[i];
    }
    return ans;
}
int main() {
    int q, rt;
    scanf("%d %d %d", &n, &q, &rt);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &pt[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(rt, 0);
    for (int i = 1; i <= n; i++) {
        add_(low[i], (long long)pt[i]);
        add_(low[i] + 1, -(long long)pt[i]);
    }
    for (int i = 0; i < q; i++) {
        int a, b, c;
        scanf("%d %d", &a, &b);
        if (a == 1) {
            scanf("%d", &c);
            add_(low[b], (long long)c);
            add_(high[b] + 1, -(long long)c);
        }
        else {
            printf("%lld\n", ask(high[b]) - ask(low[b] - 1));
        }
    }
    return 0;
}