#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXN = 200001;
int n, m, v[MAXN];
struct SegmentTree {
	int l, r;
	int sum, lans, rans, ans;
	int lans2, rans2, ans2;
	SegmentTree() {
		l = r = sum = lans = rans = ans = 0;
		lans2 = rans2 = ans2 = 0;
	}
	SegmentTree(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
		l = a;
		r = b;
		sum = c;
		lans = d;
		rans = e;
		ans = f;
		lans2 = g;
		rans2 = h;
		ans2 = i;
	}
} TreeNode[MAXN << 2];
void pushup(int o) {
	TreeNode[o].sum = TreeNode[o << 1].sum + TreeNode[o << 1 | 1].sum;
	TreeNode[o].lans = max(TreeNode[o << 1].lans, TreeNode[o << 1 | 1].lans + TreeNode[o << 1].sum);
	TreeNode[o].rans = max(TreeNode[o << 1 | 1].rans, TreeNode[o << 1].rans + TreeNode[o << 1 | 1].sum);
	TreeNode[o].ans = max(max(TreeNode[o << 1].ans, TreeNode[o << 1 | 1].ans), TreeNode[o << 1].rans + TreeNode[o << 1 | 1].lans);
	TreeNode[o].lans2 = min(TreeNode[o << 1].lans2, TreeNode[o << 1 | 1].lans2 + TreeNode[o << 1].sum);
	TreeNode[o].rans2 = min(TreeNode[o << 1 | 1].rans2, TreeNode[o << 1].rans2 + TreeNode[o << 1 | 1].sum);
	TreeNode[o].ans2 = min(min(TreeNode[o << 1].ans2, TreeNode[o << 1 | 1].ans2), TreeNode[o << 1].rans2 + TreeNode[o << 1 | 1].lans2);
}
void build(int o, int l, int r) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
	if (l == r) {
		TreeNode[o].sum = TreeNode[o].lans = TreeNode[o].rans = TreeNode[o].ans = v[l];
		TreeNode[o].lans2 = TreeNode[o].rans2 = TreeNode[o].ans2 = v[l];
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
		TreeNode[o].lans2 = TreeNode[o].rans2 = TreeNode[o].ans2 = a;
		return;
	}
	//2 2 2 2 + -3 -3 -3 -3
	change(o << 1, p, a);
	change(o << 1 | 1, p, a);
	pushup(o);
}
SegmentTree query(int o, int l, int r) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return SegmentTree(-114514, 0, 0, 0, 0, 0, 0, 0, 0);
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
	temp.lans2 = min(temp1.lans2, temp2.lans2 + temp1.sum);
	temp.rans2 = min(temp2.rans2, temp1.rans2 + temp2.sum);
	temp.ans2 = min(min(temp1.ans2, temp2.ans2), temp1.rans2 + temp2.lans2);
	return temp;
}
int main() {
	int SUM = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
		SUM += v[i];
	}
	build(1, 1, n);
	scanf("%d", &m);
	while (m--) {
		int b, c;
		scanf("%d %d", &b, &c);
		change(1, b, c);
		SUM = SUM - v[b] + c;
		v[b] = c;
		int QwQ = max(TreeNode[1].ans, SUM - TreeNode[1].ans2);
		printf("%d\n", QwQ);
		// for (int i = 1; i <= 15; i++) {
		// 	printf("%d %d %d %d %d %d\n", TreeNode[i].l, TreeNode[i].r, TreeNode[i].sum, TreeNode[i].lans, TreeNode[i].rans, TreeNode[i].ans);
		// }
	}
	return 0;
}