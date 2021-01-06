#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#pragma GCC optimize(2, 3, 5)
#define lson k << 1
#define rson k << 1 | 1
const int MAXN = 500001;
using namespace std;
int n, ed, Ypos[MAXN << 1], f[MAXN << 1][2], t;
int tr[MAXN << 3];
struct rectangle {
    int a, b, c, d;
} s[MAXN];
bool cmp(rectangle A, rectangle B) {
    return A.a < B.a;
}
void add(int k, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
		tr[k] = v;
		return;
	}
    if (li <= (l + r >> 1)) add(lson, l, l + r >> 1, li, ri, v);
    if (ri > (l + r >> 1)) add(rson, (l + r >> 1) + 1, r, li, ri, v);
}
void ask(int k, int l, int r, int pl) {
    t = max(t, tr[k]);
    if (l == r) return;
    if (pl <= (l + r >> 1)) return ask(lson, l, l + r >> 1, pl);
    return ask(rson, (l + r >> 1) + 1, r, pl);
}
int main() {
    scanf("%d %d", &n, &ed);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", &s[i].a, &s[i].b, &s[i].c, &s[i].d);
        if (s[i].a > s[i].c) swap(s[i].a, s[i].c);
        if (s[i].b > s[i].d) swap(s[i].b, s[i].d);
        Ypos[i] = s[i].d, Ypos[i + n] = s[i].b;
    }
    int N = n + n + 1;
	Ypos[N] = 0;
    sort(Ypos + 1, Ypos + N + 1); int m = unique(Ypos + 1, Ypos + N + 1) - Ypos - 1;
    s[++n] = (rectangle){ed, 0, ed, 0};
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        t = 0;
		ask(1, 1, m, lower_bound(Ypos + 1, Ypos + m + 1, s[i].b) - Ypos);
        f[i][0] = min(f[t][0] + abs(s[t].b - s[i].b),
		              f[t][1] + abs(s[t].d - s[i].b));
        t = 0;
		ask(1, 1, m, lower_bound(Ypos + 1, Ypos + m + 1, s[i].d) - Ypos);
        f[i][1] = min(f[t][0] + abs(s[t].b - s[i].d),
		              f[t][1] + abs(s[t].d - s[i].d));
        add(1, 1, m, lower_bound(Ypos + 1, Ypos + m + 1, s[i].b) - Ypos, lower_bound(Ypos + 1, Ypos + m + 1, s[i].d) - Ypos, i);
    }
    printf("%d", f[n][0] + ed);
    return 0;
}