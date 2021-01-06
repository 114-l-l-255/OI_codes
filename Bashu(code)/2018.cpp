#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 100001;
struct edge {
    int to, nxt;
} edges[MAXN << 1];
int head[MAXN], tot;
int depth[MAXN], fa[MAXN][17];
int low[MAXN], high[MAXN], times;
int wol[MAXN];
int pt[MAXN], c[MAXN << 2];
void add(int u, int v) {
    edges[++tot].to = v;
    edges[tot].nxt = head[u];
    head[u] = tot;
}
void build(int l, int r, int o) {
    if (l == r) c[o] = pt[wol[l]];
    else {
        int mid = l + r >> 1;
        build(l, mid, o << 1);
        build(mid + 1, r, o << 1 | 1);
        c[o] = min(c[o << 1], c[o << 1 | 1]);
    }
}
void change(int x, int a, int l, int r, int o) {
    if (l > x || r < x) return;
    if (l == r && l == x) { c[o] = a; return; }
    int mid = l + r >> 1;
    change(x, a, l, mid, o << 1);
    change(x, a, mid + 1, r, o << 1 | 1);
    c[o] = min(c[o << 1], c[o << 1 | 1]);
}
int ask(int x, int y, int l, int r, int o) {
    if (l > y || r < x) return 0x7fffffff;
    if (l >= x && r <= y) return c[o];
    int mid = l + r >> 1;
    return min(ask(x, y, l, mid, o << 1), ask(x, y, mid + 1, r, o << 1 | 1));
}
void dfs(int x, int f) {
    if (x != 1) fa[x][0] = f;
    depth[x] = depth[f] + 1;
    low[x] = ++times;
    wol[times] = x;
    for (int i = head[x]; i; i = edges[i].nxt) {
        if (edges[i].to == f) continue;
        dfs(edges[i].to, x);
    }
    high[x] = times;
}
int main() {
    int tmp;
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%d %d", &tmp, &pt[1]);
    for (int i = 2; i <= n; i++) {
        int u;
        scanf("%d %d", &u, &pt[i]);
        add(u, i);
    }
    memset(fa, -1, sizeof fa);
    dfs(1, 0);
    build(1, n, 1);
    // printf("---\n");
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d ", low[i], high[i]);
    // }
    // printf("\n---\n");
    int LnN = int(floor(log2(n)));
    for (int i = 1; i <= LnN; i++) {
        for (int j = 1; j <= n; j++) {
            if (fa[j][i - 1] == -1) fa[j][i] = -1;
            else fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    int rt = 1;
    for (int i = 0; i < q; i++) {
        char op;
        int a, b;
        while ((op = getchar()) != 'V' && op != 'E' && op != 'Q');
        if (op == 'V') {
            scanf("%d %d", &a, &b);
            change(low[a], b, 1, n, 1);
        }
        if (op == 'E') {
            scanf("%d", &a);
            rt = a;
        }
        if (op == 'Q') {
            scanf("%d", &a);
            if (rt == a) {
                printf("%d\n", ask(1, n, 1, n, 1));
            }
            else {
                int x = rt;
                int y = a;
                if (depth[x] < depth[y]) swap(x, y);
                for (int i = LnN; ~i; i--) if (depth[x] - (1 << i) > depth[y]) x = fa[x][i];
                int xx = x;
                x = fa[x][0];
                if (x != y) {
                    printf("%d\n", ask(low[a], high[a], 1, n, 1));
                }
                else {
                    if (x != a) {
                        printf("%d\n", ask(low[a], high[a], 1, n, 1));
                    }
                    else {
                        int A = low[xx] == 1 ? 0x7fffffff : ask(1, low[xx] - 1, 1, n, 1);
                        int B = high[xx] == n ? 0x7fffffff : ask(high[xx] + 1, n, 1, n, 1);
                        printf("%d\n", min(A, B));
                    }
                }
            }
        }
        // printf("---\n");
        // for (int i = 1; i <= 8; i++) {
        //     printf("%d ", c[i]);
        // }
        // printf("\n---\n");
    }
    return 0;
}