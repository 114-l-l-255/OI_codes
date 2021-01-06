#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int ans;
struct Node {
	int l, r;
} a[10010];
bool cmp1(Node a, Node b) {
	return a.r == b.r ? a.l < b.l : a.r < b.r;
}
struct Abcd {
	int val;
	int num;
} b[10010];
bool cmp2(Abcd a, Abcd b) {
	return a.val < b.val;
}
inline bool check(int i, int j) {
	if (a[i].l <= b[j].val && a[i].r >= b[j].val && b[j].num) return true;
	return false;
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].l, &a[i].r);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &b[i].val, &b[i].num);
	}
	sort(a + 1, a + n + 1, cmp1);
	sort(b + 1, b + m + 1, cmp2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (check(i, j)) {
				ans++;
				b[j].num--;
				break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}