#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 200005;
int n;
struct Node {
	int num, ps;
} a[MAXN];
int mi[MAXN], mx[MAXN], cnt = 0;
bool cmp(Node x, Node y) {
	if (x.num == y.num) return x.ps < y.ps;
	return x.num < y.num;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].num), a[i].ps = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		if (i == 1 || a[i].num != a[i - 1].num) {
			mx[cnt] = a[i - 1].ps;
			mi[++cnt] = a[i].ps;
		}
	}
	mx[cnt] = a[n].ps;
	bool flag = 0;
	int now = 1<<30, ans = 1;
	for (int i = 1; i <= cnt; ++i) {
		if (flag == 0) {
			if (now > mx[i]) now = mi[i];
			else flag = 1, now = mx[i];
		}
		else {
			if (now < mi[i]) now = mx[i];
			else now = mi[i], flag = 0, ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}