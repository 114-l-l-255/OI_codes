#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 300001;
int n, m, d[MAXN], head[MAXN], son[MAXN], tot, ans;
struct edge {
    int nxt, to;
} edges[MAXN * 2];
void add(int u, int v) {
    edges[++tot].to = v;
    edges[tot].nxt = head[u];
    head[u] = tot;
    son[v]++;
}
void dfs(int u, int fa) {
    d[u] = 1;
    int maxx = 1, minn = 1;
    for (int i = head[u]; i; i = edges[i].nxt) {
        int v = edges[i].to;
        if (v == fa)
            continue;
        dfs(v, u);
        if (d[v] > maxx) {
            minn = maxx;
            maxx = d[v];
        }
        else if (d[v] > minn) {
            minn = d[v];
        }
        d[u] = max(d[u], d[v] + son[u] - 1);
    }
    ans = max(maxx + minn + son[u] - 1, ans);
}
int main() {
    scanf("%d %d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    printf("%d", ans);
    return 0;
}