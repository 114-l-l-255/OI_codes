#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
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
} Edge[200005];
int n, m, cnt = 0, Head[200005], low[200005], high[200005], vst[200005], Next[200005], step = 0;
void AddEdge(int from, int to) {
    cnt++;
    Edge[cnt].to = to;
    Edge[cnt].next = Head[from];
    Head[from] = cnt;
}
void TreeToLine(int Now) {
    low[Now] = ++step;
    vst[Now] = 1;
    for (int i = Head[Now]; i; i = Edge[i].next) {
        int Next = Edge[i].to;
        if (vst[Next])
            continue;
        TreeToLine(Next);
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
    TreeToLine(1);
    bit.init(step);
    for (int i = 1; i <= n; i++) {
        bit.add(low[i], 1);
        Next[i] = -1;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        char order;
        int x;
        while ((order = getchar()) != 'C' && order != 'Q');
        scanf("%d", &x);
        if (order == 'C') {
            bit.add(low[x], Next[x]);
            Next[x] *= -1;
        }
        else
            printf("%d\n", bit.sum(high[x]) - bit.sum(low[x] - 1));
    }
    return 0;
}