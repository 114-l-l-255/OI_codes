#include <cstdio>
#include <algorithm>
#define lson (o << 1)
#define rson ((o << 1) | 1)
#define int long long
using namespace std;
const int MAXN = 40001;
struct Building {
	long long l, r, h;
	bool operator < (const Building& sec) const {
		return h < sec.h;
	}
} b[MAXN];
//if do while const extern sizeof static private public volatile int void char long float double bool or xor for and bitor bitand const operator using namespace new union asm try catch delete struct protected inline case switch default virtual goto template enum friend class throw auto signed unsigned continue break typedef register short else true false dynamic_cast static_cast export protected return wchar_t typeid mutable
int Xpos[MAXN << 2], tot;
//int QwQ[MAXN << 2];
struct SegmentTree {
	int l, r;
	long long lazy;
//	long long QvQ;
} TreeNode[MAXN << 4];
//void pushup(int o) {
//	TreeNode[o].val = TreeNode[lson].val + TreeNode[rson].val;
//}
void pushdown(int o) {
	if (TreeNode[o].lazy == 0 || TreeNode[o].lazy == -1) return;
	TreeNode[lson].lazy = TreeNode[o].lazy;
	TreeNode[rson].lazy = TreeNode[o].lazy;
//	TreeNode[lson].val = TreeNode[lson].QvQ * TreeNode[o].lazy;
//	TreeNode[rson].val = TreeNode[rson].QvQ * TreeNode[o].lazy;
	TreeNode[o].lazy = -1;
}
void Build(int l, int r, int o) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
//	if (l == r) {
//		TreeNode[o].QvQ = QwQ[l];
//	}
	if (l != r) {
		int mid = l + r >> 1;
		Build(l, mid, lson);
		Build(mid + 1, r, rson);
//		TreeNode[o].QvQ = TreeNode[lson].QvQ + TreeNode[rson].QvQ;
	}
}
void Change(int l, int r, long long x, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r) {
		TreeNode[o].lazy = x;
//		TreeNode[o].val = TreeNode[o].QvQ * x;
		return; 
	}
	pushdown(o);
	TreeNode[o].lazy = -1;
	Change(l, r, x, lson);
	Change(l, r, x, rson);
//	pushup(o);
}
long long Ask(int l, int r, int o) {
	if (TreeNode[o].l > r || TreeNode[o].r < l) return 0;
	if (TreeNode[o].l >= l && TreeNode[o].r <= r && TreeNode[o].lazy != -1) {
//		printf("!(%lld %lld %lld %lld)\n", TreeNode[o].lazy, TreeNode[o].QvQ, TreeNode[o].l, TreeNode[o].r);
		return TreeNode[o].lazy * (Xpos[TreeNode[o].r] - Xpos[TreeNode[o].l - 1]);
	}
	pushdown(o);
	long long ans = Ask(l, r, lson) + Ask(l, r, rson);
//	pushup(o);
	return ans;
}
void LazyAll(int o) {
	if (TreeNode[o].l == TreeNode[o].r) return;
	pushdown(o);
	LazyAll(lson);
	LazyAll(rson);
}
void PrintAll(int o) {
	if (TreeNode[o].l == TreeNode[o].r) {
//		printf("(%lld %lld)", TreeNode[o].lazy, TreeNode[o].QvQ);
	}
	else {
		PrintAll(lson);
		PrintAll(rson);
	}
}
signed main() {
	int n;
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &b[i].l, &b[i].r, &b[i].h);
		b[i].r--;
		Xpos[tot++] = b[i].l;
		Xpos[tot++] = b[i].l - 1;
		Xpos[tot++] = b[i].r;
		Xpos[tot++] = b[i].r + 1; 
	}
	sort(b, b + n);
	sort(Xpos, Xpos + tot);
	int nn = unique(Xpos, Xpos + tot) - Xpos;
//	for (int i = 1; i < nn; i++) {
//		QwQ[i] = Xpos[i] - Xpos[i - 1] + 1;
//	}
	Build(1, nn, 1);
	for (int i = 0; i < n; i++) {
		b[i].l = lower_bound(Xpos, Xpos + nn, b[i].l) - Xpos + 1;
		b[i].r = lower_bound(Xpos, Xpos + nn, b[i].r) - Xpos + 1;
		Change(b[i].l, b[i].r, b[i].h, 1);
//		printf("%lld %lld %lld\n", b[i].l, b[i].r, b[i].h);
//		LazyAll(1);
//		PrintAll(1);
//		printf("\n");
	}
	printf("%lld", Ask(1, nn, 1));
}