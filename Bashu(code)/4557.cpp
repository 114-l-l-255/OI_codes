#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 500005;
struct BIT {
    int n, c[maxn];
    inline int Lowbit(int x) {
        return x & (-x);
    }
    void init(int n) {
        this->n = n;
        memset(c, 0, sizeof(c));
    }
    void add(int x, int v) {
        for (int i = x; i <= n; i += Lowbit(i))
            c[i] += v;
    }
    int sum(int x) {
        int s = 0;
        for (int i = x; i; i -= Lowbit(i))
            s += c[i];
        return s;
    }
};
struct Edge {
    int to, next;
} Edge[maxn];
int f[maxn];
int n, m, cnt = 0, Head[maxn], low[maxn], high[maxn], vst[maxn], Dp[maxn], step = 0;
void AddEdge(int from, int to) {
    cnt++;
    Edge[cnt].to = to;
    Edge[cnt].next = Head[from];
    Head[from] = cnt;
}
void TreeToLine(int Now, int F) {
    Dp[Now] = Dp[F] + 1;
    f[Now] = F;
    low[Now] = ++step;
    vst[Now] = 1;
    for (int i = Head[Now]; i; i = Edge[i].next) {
        int Next = Edge[i].to;
        if (vst[Next])
            continue;
        TreeToLine(Next, Now);
    }
    high[Now] = ++step;
}
BIT bit;
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        AddEdge(x, y);
        AddEdge(y, x);
    }
    TreeToLine(1, 0);
    bit.init(step);
    scanf("%d", &m);
    for (int i = 1; i < m + n; i++) {
        char order;
        int x, y;
        while ((order = getchar()) != 'W' && order != 'A');
        scanf("%d", &x);
        if (order == 'A') {
            scanf("%d", &y);
            if (f[y] == x) {
                bit.add(low[y], 1);
                bit.add(high[y] + 1, -1);
            }
            else {
                bit.add(low[x], 1);
                bit.add(high[x] + 1, -1);
            }
        }
        else
            printf("%d\n", Dp[x] - bit.sum(low[x]) - 1, bit.sum(low[x]));
    }
    return 0;
}