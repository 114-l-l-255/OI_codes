#include <cstdio>
#include <algorithm>
#define lson o << 1
#define rson (o << 1) | 1
using namespace std;
const int MAXN = 50001;
struct SegmentTree {
    int val[MAXN << 4], len[MAXN << 4], lmax[MAXN << 4], rmax[MAXN << 4], lazy[MAXN << 4];
    void pushup(int o) {
        lmax[o] = val[lson] == len[lson] ? len[lson] + lmax[rson] : lmax[lson];
        rmax[o] = val[rson] == len[rson] ? len[rson] + rmax[lson] : rmax[rson];
        val[o] = max(max(val[lson], val[rson]), rmax[lson] + lmax[rson]);
    }
    void pushdown(int o) {
        if (lazy[o]) {
            lmax[lson] = rmax[lson] = val[lson] = lazy[o] == 1 ? 0 : len[lson];
            lmax[rson] = rmax[rson] = val[rson] = lazy[o] == 1 ? 0 : len[rson];
            lazy[lson] = lazy[rson] = lazy[o];
        }
        lazy[o] = 0;
    }
    void build(int l, int r, int o) {
        val[o] = len[o] = lmax[o] = rmax[o] = r - l + 1;
        lazy[o] = 0;
        if (l != r) {
            int mid = (l + r) >> 1;
            build(l, mid, lson);
            build(mid + 1, r, rson);
        }
    }
    int search(int want, int l, int r, int o) {
        pushdown(o);
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (val[lson] >= want) return search(want, l, mid, lson);
        else if (rmax[lson] + lmax[rson] >= want) return mid - rmax[lson] + 1;
        else if (val[rson] >= want) return search(want, mid + 1, r, rson);
        else return 0;
    }
    void change(bool type, int cl, int cr, int l, int r, int o) {
        pushdown(o);
        if (cl <= l and cr >= r) {
            val[o] = lmax[o] = rmax[o] = type ? len[o] : 0;
            lazy[o] = int(type) + 1;
            return;
        }
        if (cr < l or cl > r) return;
        else {
            int mid = (l + r) >> 1;
            change(type, cl, cr, l, mid, lson);
            change(type, cl, cr, mid + 1, r, rson);
            pushup(o);
        }
    }
} seg;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    seg.build(1, n, 1);
    for (int i = 0; i < m; i++) {
        int k, a;
        scanf("%d %d", &k, &a);
        if (k == 1) {
            if (seg.val[1] >= a) {
                int s = seg.search(a, 1, n, 1);
                printf("%d\n", s);
                seg.change(0, s, s + a - 1, 1, n, 1);
            }
            else {
                printf("0\n");
            }
        }
        else {
            int b;
            scanf("%d", &b);
            seg.change(1, a, a + b - 1, 1, n, 1);
        }
    }
    return 0;
}