#include <cstdio>
#include <algorithm>
using namespace std;
int t[15], v[105], w[40005], a[40005], f[(1 << 21) + 5];
inline int log2(int k) {
	int l = 0, r = 21, mid;
	while (l < r) {
		mid = (l + r) >> 1;
		if (k >> mid != 0)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}
int main() {
	int n, k, l, p = 0;
	scanf("%d %d %d", &n, &k, &l);
	int qqq;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &qqq);
		a[qqq] ^= 1;
		a[qqq + 1] ^= 1;
	}
	for (int i = 1; i <= n + 1; i++)
		if (a[i])
			t[++p] = i;
	for (int i = 1; i <= l; i++)
		scanf("%d", v + i);
	for (int i = 1; i <= n; i++)
		w[i] = 0x3f3f3f3f;
	for (int i = 1; i <= l; i++)
		for (int j = v[i]; j <= n; j++)
			w[j] = min(w[j], w[j - v[i]] + 1);
	for (int i = 1; i <= l; i++)
		for (int j = n - v[i]; j >= 0; j--)
			w[j] = min(w[j], w[j + v[i]] + 1);
	int s = (1 << p) - 1;
	for (int i = 1; i <= s; i++)
		f[i] = 0x3f3f3f3f;
	for (int i = 0; i < s; i++) {
		int q = i ^ s;
		for (int j = q & (-q); j <= q && q; q -= j, j = q & (-q)) {
			int qq = q - j;
			for (int x = qq & (-qq); x <= qq && qq; qq -= x, x = qq & (-qq)) {
				f[i | j | x] = min(f[i | j | x], f[i] + w[abs(t[log2(x)] - t[log2(j)])]);
			}
		}
	}
	if (f[s] != 0x3f3f3f3f)
		printf("%d\n", f[s]);
	else 
		puts("-1");
}