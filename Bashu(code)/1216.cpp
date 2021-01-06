#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 200001;
int n, m, v[MAXN];
struct SegmentTree {
	int l, r;
	int maxx, minn, ans1, ans2;
} TreeNode[MAXN << 2];
void pushup(int o) {
	TreeNode[o].maxx = max(TreeNode[o << 1].maxx, TreeNode[o << 1 | 1].maxx);
	TreeNode[o].minn = min(TreeNode[o << 1].minn, TreeNode[o << 1 | 1].minn);
	TreeNode[o].ans1 = max(TreeNode[o << 1 | 1].maxx - TreeNode[o << 1].minn, max(TreeNode[o << 1].ans1, TreeNode[o << 1 | 1].ans1));
	TreeNode[o].ans2 = max(TreeNode[o << 1].maxx - TreeNode[o << 1 | 1].minn, max(TreeNode[o << 1].ans2, TreeNode[o << 1 | 1].ans2));
}
void build(int o, int l, int r) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
	if (l == r) {
		TreeNode[o].maxx = TreeNode[o].minn = v[l];
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}
SegmentTree query(int o, int l, int r) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return (SegmentTree){0, 0, -1, 0x7fffffff, -1, -1};
	if (l <= TreeNode[o].l && r >= TreeNode[o].r) return TreeNode[o];
	SegmentTree temp1 = query(o << 1, l, r);
	SegmentTree temp2 = query(o << 1 | 1, l, r);
	SegmentTree temp;
	temp.ans1 = max(max(temp1.ans1, temp2.ans1), temp2.maxx - temp1.minn);
	temp.ans2 = max(max(temp1.ans2, temp2.ans2), temp1.maxx - temp2.minn);
	temp.minn = min(temp1.minn, temp2.minn);
	temp.maxx = max(temp1.maxx, temp2.maxx);
	return temp;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
	}
	build(1, 1, n);
	scanf("%d", &m);
	while (m--) {
		int f1, f2;
		scanf("%d %d", &f1, &f2);
		if (f1 == f2) puts("0");
		else if (f1 < f2) printf("%d\n", query(1, f1, f2).ans1);
		else printf("%d\n", query(1, f2, f1).ans2);
	}
	return 0;
}