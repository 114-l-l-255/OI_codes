#include <cstdio>
#define lson o << 1
#define rson (o << 1) | 1
const int MAXN = 100001;
struct SegmentTree {
    int l, r;
    int val, lazy;
} TreeNode[MAXN << 4];
void pushup(int o) {
    TreeNode[o].val = TreeNode[lson].val + TreeNode[rson].val;
}
void pushdown(int o) {
    if (!TreeNode[o].lazy) return;
    TreeNode[lson].val = TreeNode[lson].r - TreeNode[lson].l + 1 - TreeNode[lson].val;
    TreeNode[rson].val = TreeNode[rson].r - TreeNode[rson].l + 1 - TreeNode[rson].val;
    TreeNode[lson].lazy = 1 - TreeNode[lson].lazy;
    TreeNode[rson].lazy = 1 - TreeNode[rson].lazy;
    TreeNode[o].lazy = 0;
}
void Build(int l, int r, int o) {
    TreeNode[o].lazy = 0;
    TreeNode[o].l = l;
    TreeNode[o].r = r;
    TreeNode[o].val = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    Build(l, mid, lson);
    Build(mid + 1, r, rson);
    return;
}
void Change(int l, int r, int o) {
    if (l <= TreeNode[o].l and r >= TreeNode[o].r) {
        TreeNode[o].lazy = TreeNode[o].lazy xor 1;
        TreeNode[o].val = TreeNode[o].r - TreeNode[o].l + 1 - TreeNode[o].val;
        return;
    }
    if (r < TreeNode[o].l or l > TreeNode[o].r) return;
    pushdown(o);
    Change(l, r, lson);
    Change(l, r, rson);
    pushup(o);
}
int Search(int x, int o) {
    if (TreeNode[o].l == TreeNode[o].r) return TreeNode[o].val;
    pushdown(o);
    int mid = (TreeNode[o].l + TreeNode[o].r) >> 1;
    int ans;
    if (x <= mid) ans = Search(x, lson);
    else ans = Search(x, rson);
    pushup(o);
    return ans;
}
// void LazyAll(int o) {
//     pushdown(o);
//     if (TreeNode[o].l == TreeNode[o].r) return;
//     LazyAll(lson);
//     LazyAll(rson);
//     return;
// }
// void PrintAll(int o) {
//     if (TreeNode[o].l == TreeNode[o].r) {
//         printf("%d ", TreeNode[o].val);
//         return;
//     }
//     PrintAll(lson);
//     PrintAll(rson);
//     return;
// }
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Build(1, n, 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == 1) {
            int c;
            scanf("%d", &c);
            Change(b, c, 1);
        }
        else {
            printf("%d\n", Search(b, 1));
        }
    }
    return 0;
}