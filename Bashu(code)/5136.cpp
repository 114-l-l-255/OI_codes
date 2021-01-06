#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define F(i, a, b) for (int i = a; i <= b; i++)
#define Fd(i, a, b) for (int i = a; i >= b; i--)
#define mem(a, b) memset(a, b, sizeof(a))
#define N 310
using namespace std;
void rd(int &x) {
    x = 0;
    int w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= w;
}
int n, m, c[N], cnt, lf, rg, bz, d[N * N], S, T;
double w[N * N], ks, bs, g[N][N];
struct node {
    int x, y;
} a[N];
struct ft {
    int l, r;
    ft() {}
    ft(int a, int b) {
        l = a, r = b;
    }
} b[N];
long long sqr(long long x) { return x * x; }
double dis(int x, int y) {
    double st = sqr((long long)a[x].x - a[y].x) + sqr((long long)a[x].y - a[y].y);
    return (double)sqrt(st);
}
void A(int x, int y, double z) { g[x][y] = min(g[x][y], z); }
double slp(int x, int y) { return (double)(a[x].y - a[y].y) / (double)(a[x].x - a[y].x); }
int main() {
    rd(n);
    for (int i = 1; i <= n; i++) {
        rd(m);
        b[i] = ft(cnt + 1, cnt + m);
        F(j, 1, m) {
            rd(a[++cnt].x), rd(a[cnt].y);
            c[cnt] = i;
        }
    }
    mem(g, 127);
    for (int k = 1; k <= n; k++) {
        lf = b[k].l, rg = b[k].r;
        for (int i = lf; i <= rg - 1; i++) {
            A(i, i + 1, dis(i, i + 1)), A(i + 1, i, dis(i + 1, i));
        }
        A(lf, rg, dis(lf, rg)), A(rg, lf, dis(lf, rg));
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j <= cnt; j++) {
            if (c[i] != c[j]) {
                ks = slp(i, j), bs = (double)a[i].y - (double)a[i].x * ks, bz = 1;
                int lx = min(a[i].x, a[j].x), rx = a[i].x + a[j].x - lx;
                for (int k = 1; k <= n; k++) {
                    lf = b[k].l, rg = b[k].r;
                    for (int l = lf; l <= rg; l++) {
                        if (l != i && l != j) {
                            for (int l2 = lf; l2 <= rg; l2++)
                            if (l2 != i && l2 != j && l2 != l) {
                                double k2 = slp(l, l2), b2 = (double)a[l].y - (double)a[l].x * k2;
                                double x = (b2 - bs) / (ks - k2);
                                int lx2 = min(a[l].x, a[l2].x), rx2 = a[l].x + a[l2].x - lx2;
                                if (x >= lx2 && x <= rx2 && x >= lx && x <= rx) {
                                    bz = 0;
                                    break;
                                }
                            }
                        }
                        if (!bz) break;
                    }
                }
                if (bz) {
                    A(i, j, dis(i, j)), A(j, i, dis(j, i));
                }
            }
        }
    }
    rd(S), rd(T);
    for (int k = 1; k <= cnt; k++) {
        for (int i = 1; i <= cnt; i++) {
            for (int j = 1; j <= cnt; j++) {
                if (i != j) g[i][j] = min(g[i][j], g[i][k] + g[j][k]);
            }
        }
    }
    printf("%.4lf\n", g[S][T]);
    return 0;
}