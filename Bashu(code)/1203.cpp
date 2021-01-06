#include <cstdio>
#include <algorithm>
#define lson o << 1
#define rson (o << 1) | 1
using namespace std;
const int MAXN = 100001;
struct SegmentTree {
	int l, r;
	int val, lazy;
} TreeNode[MAXN << 4];
void pushup(int o) {
//	TreeNode[o].val = TreeNode[lson].val + TreeNode[rson].val;
	TreeNode[o].val = max(TreeNode[lson].val, TreeNode[rson].val);
}
void pushdown(int o) {
	if (!TreeNode[o].lazy) return;
	TreeNode[lson].val += TreeNode[o].lazy;
	TreeNode[rson].val += TreeNode[o].lazy;
	TreeNode[lson].lazy += TreeNode[o].lazy;
	TreeNode[rson].lazy += TreeNode[o].lazy;
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
void Change(int l, int r, int o, int nums) {
	if (l <= TreeNode[o].l and r >= TreeNode[o].r) {
//		TreeNode[o].lazy = TreeNode[o].lazy xor 1;
//		TreeNode[o].val = TreeNode[o].r - TreeNode[o].l + 1 - TreeNode[o].val;
		TreeNode[o].lazy += nums;
		TreeNode[o].val += nums;
		return;
	}
	if (r < TreeNode[o].l or l > TreeNode[o].r) return;
	pushdown(o);
	Change(l, r, lson, nums);
	Change(l, r, rson, nums);
	pushup(o);
}
int Ask(int l, int r, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return 0;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r) return TreeNode[o].val;
	else {
		pushdown(o);
		return max(Ask(l, r, lson), Ask(l, r, rson));
		pushup(o);
	}
}
void PrintAll(int);
void LazyAll(int o) {
//	printf("%d: ", o);
//	PrintAll(1);
//	printf("\n");
	if (TreeNode[o].l == TreeNode[o].r) return;
	pushdown(o);
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
	int n, m, k;
	scanf("%d %d %d", &n, &k, &m);
	Build(1, n, 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (Ask(a, b - 1, 1) + c <= k) {
			printf("YES\n");
			Change(a, b - 1, 1, c);
		}
		else printf("NO\n");
//		LazyAll(1);
//		PrintAll(1);
//		printf("\n");
	}
//	printf("%d", Ask(1, n - 1, 1));
	return 0;
}