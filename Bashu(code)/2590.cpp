/*
555555
544555
544445

0  0  0  0  0  0
0 -1  0  1  0  0
0 -1  0  0  0  1
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 10001;
struct node {
	int a, b;
} s[MAXN];
bool cmp(node x, node y) {
	if (x.a == y.a)
		return x.b < y.b;
	return x.a < y.a;
}
int ans[MAXN];
int main() {
	int n, p, h, m;
	cin >> n >> p >> h >> m;
	for (int i = 1; i <= m; i++) {
		cin >> s[i].a >> s[i].b;
		if (s[i].a > s[i].b)
			swap(s[i].a, s[i].b);
	}
	sort(s + 1, s + n + 1, cmp);
	s[0].a = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i].a == s[i - 1].a && s[i].b == s[i - 1].b) continue;
		ans[s[i].a + 1]--;
		ans[s[i].b]++;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt += ans[i];
		cout << cnt + h << endl;
	}
	return 0;
}