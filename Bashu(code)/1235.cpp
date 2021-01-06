#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1000001;
long long c[MAXN];
int n;
int lowbit(int x) {
	return x & -x;
}
void add(int a, long long x) {
	for (int i = a; i <= n; i += lowbit(i)) c[i] += x;
}
long long ask(int x) {
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
int main() {
	int q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		add(i, (long long)a);
	}
	for (int i = 0; i < q; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			add(b, (long long)c);
		}
		if (a == 2) {
			printf("%lld\n", ask(c) - ask(b - 1));
		}
	}
	return 0;
}