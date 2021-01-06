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
	TreeNode[lson].val = TreeNode[lson].r - TreeNode[lson].l + 1;
	TreeNode[rson].val = TreeNode[rson].r - TreeNode[rson].l + 1;
	TreeNode[lson].lazy = TreeNode[rson].lazy = 1; 
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
//		TreeNode[o].lazy = TreeNode[o].lazy xor 1;
//		TreeNode[o].val = TreeNode[o].r - TreeNode[o].l + 1 - TreeNode[o].val;
		TreeNode[o].lazy = 1;
		TreeNode[o].val = TreeNode[o].r - TreeNode[o].l + 1;
		return;
	}
	if (r < TreeNode[o].l or l > TreeNode[o].r) return;
	pushdown(o);
	Change(l, r, lson);
	Change(l, r, rson);
	pushup(o);
}
int Ask(int l, int r, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return 0;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r) return TreeNode[o].val;
	else {
		pushdown(o);
		return Ask(l, r, lson) + Ask(l, r, rson);
		pushup(o);
	}
}
void LazyAll(int o) {
	pushdown(o);
	if (TreeNode[o].l == TreeNode[o].r) return;
	LazyAll(lson);
	LazyAll(rson);
	return;
}
void PrintAll(int o) {
	if (TreeNode[o].l == TreeNode[o].r) {
		printf("%d ", TreeNode[o].val);
		return;
	}
	PrintAll(lson);
	PrintAll(rson);
	return;
}
int main() {
	int m;
	int L, R;
	scanf("%d %d %d", &L, &R, &m);
	Build(1, R - L, 1);
	for (int i = 0; i < m; i++) {
		int b, c;
		scanf("%d %d", &b, &c);
		b = b > L ? b : L;
		c = c > R ? R : c;
		Change(b - L + 1, c - L, 1);
//		LazyAll(1);
//		PrintAll(1);
//		printf("\n");
	}
	printf("%d", Ask(1, R - L, 1));
	return 0;
}