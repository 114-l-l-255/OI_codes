#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300010;
const int MAXM = 1000010;
int t[MAXM][2];
int a[MAXN];
int s[MAXN];
int mx[MAXN];
int pos[MAXN];
int n, k;
int H;
long long ans;
inline void binary_solve(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	s[mid] = H = mx[0] = 0;
	for (int i = mid + 1 ; i <= r ; ++i) {
		if (a[i] > a[mx[H]]) mx[++H] = i;
		s[i] = (s[i - 1] + a[i] % k) % k,++t[(s[i] - a[mx[H]] % k + k) % k][0],pos[i] = mx[H];
	}
	mx[H + 1] = r + 1;
	int p = 1, z = 0, p1 = mid + 1, mx1 = 0;
	for (int i = mid; i >= l ; --i) {
		z = (z + a[i] % k) % k, mx1 = max(mx1, a[i]);
		while (p <= H && a[mx[p]] <= mx1) ++p;
		while (p1 < mx[p]) --t[(s[p1] - a[pos[p1]] % k + k) % k][0], ++t[s[p1]][1], ++p1;
		ans += t[(k + mx1 % k - z) % k][1];
		if (p <= H) ans += t[(k - z) % k][0];
	}
	for (int i = mid + 1; i < p1; ++i) --t[s[i]][1];
	for (int i = p1; i <= r; ++i) --t[(s[i] - a[pos[i]] % k + k) % k][0];
	binary_solve(l, mid);
	binary_solve(mid + 1, r);
}
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	binary_solve(1, n);
	printf("%lld\n", ans);
	return 0;
}