#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 500001;
int n, m, v[MAXN];
struct SegmentTree {
	int l, r;
	int sum, lans, rans, ans;
	SegmentTree() {
		l = r = sum = lans = rans = ans = 0;
	}
	SegmentTree(int a, int b, int c, int d, int e, int f) {
		l = a;
		r = b;
		sum = c;
		lans = d;
		rans = e;
		ans = f;
	}
} TreeNode[MAXN << 2];
void pushup(int o) {
	TreeNode[o].sum = TreeNode[o << 1].sum + TreeNode[o << 1 | 1].sum;
	TreeNode[o].lans = max(TreeNode[o << 1].lans, TreeNode[o << 1 | 1].lans + TreeNode[o << 1].sum);
	TreeNode[o].rans = max(TreeNode[o << 1 | 1].rans, TreeNode[o << 1].rans + TreeNode[o << 1 | 1].sum);
	TreeNode[o].ans = max(max(TreeNode[o << 1].ans, TreeNode[o << 1 | 1].ans), TreeNode[o << 1].rans + TreeNode[o << 1 | 1].lans);
}
void build(int o, int l, int r) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
	if (l == r) {
		TreeNode[o].sum = TreeNode[o].lans = TreeNode[o].rans = TreeNode[o].ans = v[l];
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}
void change(int o, int p, int a) {
	if (TreeNode[o].l > p || TreeNode[o].r < p) return;
	if (TreeNode[o].l == TreeNode[o].r) {
		TreeNode[o].sum = TreeNode[o].lans = TreeNode[o].rans = TreeNode[o].ans = a;
		return;
	}
	//2 2 2 2 + -3 -3 -3 -3
	change(o << 1, p, a);
	change(o << 1 | 1, p, a);
	pushup(o);
}
SegmentTree query(int o, int l, int r) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return SegmentTree(-114514, 0, 0, 0, 0, 0);
	if (l <= TreeNode[o].l && r >= TreeNode[o].r) return TreeNode[o];
	SegmentTree temp1 = query(o << 1, l, r);
	SegmentTree temp2 = query(o << 1 | 1, l, r);
	SegmentTree temp;
	if (temp1.l == -114514) return temp2;
	if (temp2.l == -114514) return temp1;
	temp.sum = temp1.sum + temp2.sum;
	temp.lans = max(temp1.lans, temp2.lans + temp1.sum);
	temp.rans = max(temp2.rans, temp1.rans + temp2.sum);
	temp.ans = max(max(temp1.ans, temp2.ans), temp1.rans + temp2.lans);
	return temp;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
	}
	build(1, 1, n);
	while (m--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) printf("%d\n", query(1, b < c ? b : c, b < c ? c : b).ans);
		else change(1, b, c);
		// for (int i = 1; i <= 15; i++) {
		// 	printf("%d %d %d %d %d %d\n", TreeNode[i].l, TreeNode[i].r, TreeNode[i].sum, TreeNode[i].lans, TreeNode[i].rans, TreeNode[i].ans);
		// }
	}
	return 0;
}