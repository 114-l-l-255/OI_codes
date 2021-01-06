#include <bits/stdc++.h>
#define N 100005
#define M 262500
int n, B;
int a[M], p[N];
int find_fa(int x) {
	return p[x] == x ? x : (p[x] = find_fa(p[x]));
}
inline bool merge(int x, int y, bool un = false) {
	if ((x = find_fa(x)) == (y = find_fa(y))) return true;
	if (un) p[x] = y;
	return false;
}
int main() {
	int i, j, v;
	long long ans = 0;
	scanf("%d %d", &n, &B);
	for (i = 1; i <= n; ++i) {
		p[i] = i;
		scanf("%d", &v);
		a[v] ? ans += v : (a[v] = i);
	}
	for (i = ~(-1 << B); i; --i) {
		int &u = a[i];
		for (j = 0; j < B && !u; ++j) u = a[i | 1 << j];
		for (; j < B; ++j)
			if ((v = a[i | 1 << j]) && !merge(u, v, true)) ans += i;
	}
	printf("%lld\n", ans);
	return 0;
}