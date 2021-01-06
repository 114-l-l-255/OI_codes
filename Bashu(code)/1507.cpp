#include<bits/stdc++.h>
using namespace std;
int n, a[100001];
int main() {
	scanf("%d", &n);
	long long pos = 0, neg = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		int p = a[i] - a[i - 1];
		if (i == 1) continue;
		if (p > 0) pos += p;
		else neg += p;
	}
	neg *= -1;
	long long ans1 = max(pos, neg);
	long long ans2 = abs(pos - neg) + 1;
	printf("%lld\n%lld", ans1, ans2);
	return 0;
}