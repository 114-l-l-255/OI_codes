#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 100001;
long long Tree[MAXN + 5], v[MAXN + 5];
int fa[MAXN + 5];
int n;
void build() {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
}
int find_fa(int a) {
	return fa[a] == a ? a : fa[a] = find_fa(fa[a]);
}
int lowbit(int a) {
	return a & -a;
}
void change(int a, long long b) {
	while (a <= n) {
		Tree[a] += b;
		a += lowbit(a);
	}
}
long long search(int a) {
	long long ans = 0;
	while (a) {
		ans += Tree[a];
		a -= lowbit(a);
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	build();
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &v[i]);
		change(i, v[i]);
		if (v[i] <= 1) {
			fa[i] = i + 1;
		}
	}
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int k, l, r;
		scanf("%d %d %d", &k, &l, &r);
		if (k == 0) {
			l = find_fa(l);
			while (l <= r) {
				long long Q = (long long)(sqrt(v[l]));
				change(l, Q - v[l]);
				// printf("%d:%d->%d\n", l, v[l], Q);
				v[l] = Q;
				if (v[l] <= 1) {
					fa[l] = l + 1;
				}
				int ll = l;
				l = find_fa(l);
				if (l == ll) l++;
			}
		}
		if (k == 1) {
			printf("%lld\n", l == 1 ? search(r) : search(r) - search(l - 1));
		}
		// for (int i = 1; i <= n; i++) {
		// 	printf("%d ", fa[i]);
		// }
		// printf("\n");
	}
	return 0;
}