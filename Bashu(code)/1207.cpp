#include <cstdio>
#include <algorithm>
#define lson (o << 1)
#define rson ((o << 1) | 1)
using namespace std;
const int MAXN = 400001;
struct SegmentTree {
	int l, r;
	int lazy;
} TreeNode[MAXN << 4];
bool Hash[MAXN];
int xc;
void pushdown(int o) {
	if (TreeNode[o].lazy == 0) return;
	TreeNode[lson].lazy += TreeNode[o].lazy;
	TreeNode[rson].lazy += TreeNode[o].lazy;
	TreeNode[o].lazy = 0;
}
void Build(int l, int r, int o) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
	if (l != r) {
		int mid = (l + r) >> 1;
		Build(l, mid, lson);
		Build(mid + 1, r, rson);
	}
}
void Change(int l, int r, int id, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r) {
		TreeNode[o].lazy++;
		return;
	}
	pushdown(o);
	Change(l, r, id, lson);
	Change(l, r, id, rson);
}
int Ask(int l, int r, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return -1;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r) {
		return TreeNode[o].lazy;
	}
	pushdown(o);
	return max(Ask(l, r, lson),
	Ask(l, r, rson));
}
void LazyAll(int o) {
	if (TreeNode[o].l == TreeNode[o].r) return;
	pushdown(o);
	LazyAll(lson);
	LazyAll(rson);
	return;
}
void PrintAll(int o) {
	if (TreeNode[o].l == TreeNode[o].r) {
		printf("%d ", TreeNode[o].lazy);
		return;
	}
	PrintAll(lson);
	PrintAll(rson);
	return;
}
int main() {
	int n;
	scanf("%d %d", &xc, &n);
	xc++;
	int L = -100000, R = 100000;
	Build(1, R - L, 1);
	for (int i = 0; i < n; i++) {
		int l, r, color;
		scanf("%d %d %d", &l, &r, &color);
		if (r < L || l > R) continue;
		l = max(l, L);
		r = min(r, R);
		Change(l - L + 1, r - L, color + 1, 1);
//		LazyAll(1);
//		PrintAll(1);
//		printf("\n");
	}
	int p;
	scanf("%d", &p);
	printf("%d", Ask(p - L + 1, p - L + 1, 1));
	return 0;
}