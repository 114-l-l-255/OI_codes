#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int read() {
    int q = 0;
	char ch = ' ';
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return q;
}
const int MAXN = 100005;
int n, m, maxa, ans1, ans2, cn;
int a[MAXN], b[MAXN], pre[MAXN], suf[MAXN], bin[33];
int tr[MAXN * 33][2];
void ins(int x) {
    int from = 0, t;
    for (int i = n; i >= 1; --i) {
        if (bin[i] & x) t = 1;
        else t = 0;
        if (tr[from][t]) from = tr[from][t];
        else ++cn, tr[from][t] = cn, from = cn;
    }
}
void dfs(int x, int d, int num) {
    if (tr[x][0] && tr[x][1])
        dfs(tr[x][0], d - 1, num), dfs(tr[x][1], d - 1, num);
    else if (!tr[x][0] && !tr[x][1]) {
        if (num > ans1) ans1 = num, ans2 = 1;
        else if (num == ans1) ++ans2;
        return;
    }
    else if (tr[x][0]) dfs(tr[x][0], d - 1, num + bin[d - 1]);
    else dfs(tr[x][1], d - 1, num + bin[d - 1]);
}
int main() {
//    freopen("big.in", "r", stdin);
//    freopen("big.out", "w", stdout);
    n = read(), m = read();
    maxa = 1 << n;
	bin[1] = 1;
    for (int i = 2; i <= n; i++) bin[i] = bin[i - 1] << 1;
    for (int i = 1; i <= m; i++) a[i] = read(), b[i] = (2 * a[i] / maxa + 2 * a[i]) % maxa;
    for (int i = 1; i <= m; i++) pre[i] = pre[i - 1] ^ b[i];
    for (int i = m; i >= 1; i--) suf[i] = suf[i + 1] ^ a[i];
    for (int i = 0; i <= m; i++) ins(pre[i] ^ suf[i + 1]);
    dfs(0, n + 1, 0);
	printf("%d\n%d\n", ans1, ans2);
    return 0;
}