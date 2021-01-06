#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
struct Block {
	int l, r, v;
} block[MAXN]; int tot;
int val[MAXN << 2];
int v[MAXN];
int Lst[MAXN];
void pushup(int o) {
	val[o] = max(val[o << 1], val[o << 1 | 1]);
}
void build(int o, int l, int r) {
	if (l == r) val[o] = block[l].r - block[l].l + 1;
	if (l != r) {
		int mid = l + r >> 1;
		build(o << 1, l, mid);
		build(o << 1 | 1, mid + 1, r);
		pushup(o);
	}
}
int search(int o, int l, int r, int a, int b) {
	if (a <= l && r <= b) {
		return val[o];
	}
	else {
		int mid = l + r >> 1;
		int ret = -0x7fffffff - 1;
		if (a <= mid) ret = max(ret, search(o << 1, l, mid, a, b));
		if (b > mid) ret = max(ret, search(o << 1 | 1, mid + 1, r, a, b));
		return ret;
	}
}
int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	int lst = -0x7fffffff - 1;
	for (int i = 1; i <= n; i++) {
		int V;
		scanf("%d", &V);
		if (lst == V) block[tot].r = i;
		else {
			block[++tot].l = i;
			block[tot].v = V;
			lst = V;
			v[tot] = V;
		}
		Lst[i] = tot;
	}
	build(1, 1, tot);
	while (q--) {
		int a, b;
		scanf("%d %d", &a, &b);
		int Lft = Lst[a], Rght = Lst[b];
		if (Lft == Rght) {
			printf("%d\n", b - a + 1);
			continue;
		}
		int ans = max(block[Lft].r - a + 1, b - block[Rght].l + 1);
		if (Lft + 1 == Rght) {
			printf("%d\n", ans);
			continue;
		}
		printf("%d\n", max(search(1, 1, tot, Lft + 1, Rght - 1), ans));
	}
	return 0;
}