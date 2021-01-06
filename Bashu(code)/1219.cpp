#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
bool val[MAXN << 2][31];
short lazy[MAXN << 2];
bool ans[31];
void pushup(int o) {
	for (int i = 1; i <= 30; i++) {
		val[o][i] = val[o << 1][i] | val[o << 1 | 1][i];
	}
}
void pushdown(int o) {
	if (lazy[o]) {
		for (int i = 1; i <= 30; i++) {
			val[o << 1][i] = val[o << 1 | 1][i] = 0;
		}
		val[o << 1][lazy[o]] = val[o << 1 | 1][lazy[o]] = 1;
		lazy[o << 1] = lazy[o << 1 | 1] = lazy[o];
		lazy[o] = 0;
	}
}
void change(int o, int l, int r, int a, int b, short c) {
	if (a <= l && r <= b) {
		for (int i = 1; i <= 30; i++) {
			val[o][i] = 0;
		}
		val[o][c] = 1;
		lazy[o] = c;
	}
	else {
		pushdown(o);
		int mid = l + r >> 1;
		if (a <= mid) change(o << 1, l, mid, a, b, c);
		if (b > mid) change(o << 1 | 1, mid + 1, r, a, b, c);
		pushup(o);
	}
}
void search(int o, int l, int r, int a, int b) {
	if (a <= l && r <= b) {
		for (int i = 1; i <= 30; i++) {
			ans[i] |= val[o][i];
		}
	}
	else {
		pushdown(o);
		int mid = l + r >> 1;
		if (a <= mid) search(o << 1, l, mid, a, b);
		if (b > mid) search(o << 1 | 1, mid + 1, r, a, b);
	}
}
int main() {
	int l, t, m;
	scanf("%d %d %d", &l, &t, &m);
	change(1, 1, l, 1, l, 1);
	while (m--) {
		char ch;
		do {
			ch = getchar();
		} while (ch != 'C' && ch != 'P');
		int a, b;
		short c;
		if (ch == 'C') {
			scanf("%d %d %hd", &a, &b, &c);
			change(1, 1, l, a, b, c);
		}
		if (ch == 'P') {
			scanf("%d %d", &a, &b);
			for (int i = 1; i <= 30; i++) {
				ans[i] = 0;
			}
			search(1, 1, l, a, b);
			int ret = 0;
			for (int i = 1; i <= 30; i++) {
				ret += ans[i];
			}
			printf("%d\n", ret);
		}
	}
	return 0;
}