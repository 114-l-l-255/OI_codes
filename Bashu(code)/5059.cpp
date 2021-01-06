#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 100001;
struct node {
    int lz, l, r, sum[26];
} a[MAXN * 4];
int n, q;
char ch[MAXN];
int chuan[MAXN], tot[26];

inline void pushup(int xv) {
    for(int i = 0; i <= 25; i++) {
    	a[xv].sum[i] = a[xv * 2].sum[i] + a[xv * 2 + 1].sum[i];
	}
}
inline void pushdown(int xv, int x, int y) {
    if (a[xv].lz) {
        a[xv].lz = 0;
        for (int i = 0; i <= 25; i++) {
            if (a[xv].sum[i] == 0) a[xv * 2].sum[i] = a[xv * 2 + 1].sum[i] = 0;
            else a[xv * 2].sum[i] = x, a[xv * 2 + 1].sum[i] = y;
        }
        a[xv * 2].lz = a[xv * 2 + 1].lz = 1;
    }
}

inline void build(int xv, int l, int r) {
    if (l == r) {
        a[xv].l = l, a[xv].r = r, a[xv].lz = 0;
        memset(a[xv].sum, 0, sizeof(a[xv].sum));
        a[xv].sum[chuan[l]] = 1;
        return;
    }
    a[xv].l = l, a[xv].r = r;
    int mid = (l + r) / 2;
    build(xv * 2, l, mid), build(xv * 2 + 1, mid + 1, r);
    pushup(xv);
}

inline int ask(int xv, int l, int r, int k) {
    int L = a[xv].l, R = a[xv].r, mid = (L + R) / 2;
    if (L == l && R == r) {
        return a[xv].sum[k];
    }
    pushdown(xv, mid - L + 1, R - mid);
    if (r <= mid) return ask(xv * 2, l, r, k);
    else if (l > mid) return ask(xv * 2 + 1, l, r, k);
    else return ask(xv * 2, l, mid, k) + ask(xv * 2 + 1, mid + 1, r, k);
}

inline void update(int xv, int l, int r, int k) {
    int L = a[xv].l, R = a[xv].r, mid = (L + R) / 2;
    if (l == L && R == r) {
        memset(a[xv].sum, 0, sizeof(a[xv].sum));
        a[xv].sum[k] = r - l + 1;
        a[xv].lz = 1;
        return;
    }
    pushdown(xv, mid - L + 1, R - mid);
    if (r <= mid) update(xv * 2, l, r, k);
    else if (l > mid) update(xv * 2 + 1, l, r, k);
    else update(xv * 2, l, mid, k), update(xv * 2 + 1, mid + 1, r, k);
    pushup(xv);
}

inline int ask2(int xv, int ps) {
    int L = a[xv].l, R = a[xv].r, mid = (L + R) / 2;
    if (L == R) {
        for (int i = 0; i <= 25; i++)
            if (a[xv].sum[i]) return i;
    }
    pushdown(xv, mid - L + 1, R - mid);
    if (ps <= mid) return ask2(xv * 2, ps);
    else return ask2(xv * 2 + 1, ps);
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", ch + 1);
    for (int i = 1; i <= n; i++) chuan[i] = ch[i] - 'a';
    build(1, 1, n);
    while (q--) {
        int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
        if (l > r) swap(l, r);
        memset(tot, 0, sizeof(tot));
        for (int i = 0; i <= 25; i++) tot[i] += ask(1, l, r, i);
        if (x == 1) {
            int ll = l, rr = l - 1;
            for (int i = 0; i <= 25; i++) {
                if (tot[i] != 0) {
                    rr += tot[i];
                    update(1, ll, rr, i);
                    ll = rr + 1;
                }
            }
        }
        else {
            int ll = l, rr = l - 1;
            for (int i = 25; i >= 0; i--) {
                if (tot[i] != 0) {
                    rr += tot[i];
                    update(1, ll, rr, i);
                    ll = rr + 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%c", ask2(1, i) + 'a');
    }
    return 0;
}