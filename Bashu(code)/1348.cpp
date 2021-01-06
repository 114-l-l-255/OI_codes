#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
int n, a[MAXN];
struct node {
	int val, id;
	int nxt, pre;
} p[MAXN];
int tot = 0, b[MAXN], idx[MAXN];
int ans[MAXN][3];
void remove(int pos) {
	p[p[pos].pre].nxt = p[pos].nxt;
	p[p[pos].nxt].pre = p[pos].pre;
}
bool cmp(int i, int j) {
	return a[i] < a[j];
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[i] = i;
	sort(b + 1, b + n + 1, cmp);
	tot = 1;
	p[1].val = a[b[1]];
	p[1].id = b[1];
	idx[b[1]] = 1;
	for (int i = 2; i <= n; ++i) {
		idx[b[i]] = ++tot;
		p[tot].val = a[b[i]];
		p[tot].id = b[i];
		p[tot].pre = tot - 1;
		p[tot - 1].nxt = tot;
	}
	for (int i = n; i >= 2; --i) {
		int pos = idx[i];
		int mp = 0x7fffffff, mn = 0x7fffffff;
		if (p[pos].pre) mp = abs(p[pos].val - p[p[pos].pre].val);
		if (p[pos].nxt) mn = abs(p[pos].val - p[p[pos].nxt].val);
		if (mp <= mn) {
			ans[i][0] = mp;
			ans[i][1] = p[p[pos].pre].id;
		}
		else {
			ans[i][0] = mn;
			ans[i][1] = p[p[pos].nxt].id;
		}
		remove(pos);
	}
	for (int i = 2; i <= n; ++i) printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}