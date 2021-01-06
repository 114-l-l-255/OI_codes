#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 10000001;
int a[MAXN];
int b[664599], tot;
int pre[MAXN];
void prime() {
	a[0] = a[1] = 1;
	for (int i = 2; i <= 10000000; i++) {
		if (a[i] == 0) {
			b[tot++] = i;
		}
		for (int j = 0; j < tot && (long long)i * b[j] <= 10000000; j++) {
			a[i * b[j]] = 1;
			if (i % b[j] == 0) break;
		}
	}
//	return tot;
}
int main() {
//	freopen("prime.in", "r", stdin);
//	freopen("prime.out", "w", stdout);
//	printf("%d", prime());
	prime();
	for (int i = 0; i < tot; i++) {
		for (int j = i; j < tot && (long long)b[i] * b[j] <= 10000000; j++) {
			pre[b[i] * b[j]] = 1;
		}
	}
	for (int i = 1; i <= 10000000; i++) {
		a[i] += a[i - 1];
		pre[i] += pre[i - 1];
	}
	int Q;
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", (long long)r - l + 1 - a[r] + a[l - 1] + pre[r] - pre[l - 1]);
	}
	return 0;
}