#include <cstdio>
#include <algorithm>
#define lson (o << 1)
#define rson ((o << 1) | 1)
using namespace std;
const int MAXN = 100001;
struct TreeNode {
	int val, l, r;
} seg[MAXN << 2];
void push_up(int o) {
	seg[o].val = seg[lson].val + seg[rson].val;
}
void Build(int o, int l, int r) {
	seg[o].l = l;
	seg[o].r = r;
	if (l != r) {
		int mid = l + r >> 1;
		Build(lson, l, mid);
		Build(rson, mid + 1, r);
	}
}
void Add(int o, int x, int a) {
	if (seg[o].l > x || seg[o].r < x) return;
	if (seg[o].l >= x && seg[o].r <= x) seg[o].val += a;
	else {
		Add(lson, x, a);
		Add(rson, x, a);
		push_up(o);
	}
}
int Ask(int o, int l, int r) {
	if (seg[o].l > r || seg[o].r < l) return 0;
	if (seg[o].l >= l && seg[o].r <= r) return seg[o].val;
	else {
		return Ask(lson, l, r) + Ask(rson, l, r);
	}
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Build(1, 1, n);
	for (int i = 0; i < m; i++) {
		char ch = getchar();
		while (ch != 'd' && ch != 'u' && ch != 's') {
			ch = getchar();
		}
		int a, b;
		scanf("%*c %d %d", &a, &b);
		if (ch == 'd') {
			Add(1, a, b);
		}
		if (ch == 'u') {
			Add(1, a, -b);
		}
		if (ch == 's') {
			printf("%d\n", Ask(1, a, b));
		}
	}
	return 0;
}