#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = (1 << 12) + 1;
long long c[MAXN][MAXN];
int n, m;
int lowbit(int x) {
    return x & -x;
}
void add(int x, int y, long long a) {
    for (int i = x; i <= n; i += lowbit(i)) for (int j = y; j <= m; j += lowbit(j)) c[i][j] += a;
}
long long ask(int x, int y) {
    long long ans = 0;
    for (int i = x; i; i -= lowbit(i)) for (int j = y; j; j -= lowbit(j)) ans += c[i][j];
    return ans;
}
int main() {
    scanf("%d %d", &n, &m);
    int a, b, c, d, e;
    while (~scanf("%d %d %d %d", &a, &b, &c, &d)) {
        if (a == 1) {
            add(b, c, (long long)d);
        }
        if (a == 2) {
            scanf("%d", &e);
            printf("%lld\n", ask(d, e) - ask(b - 1, e) - ask(d, c - 1) + ask(b - 1, c - 1));
        }
    }
    return 0;
}