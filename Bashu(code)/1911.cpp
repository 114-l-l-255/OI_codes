#include <iostream>
#include <cstdio>
#define INF 2147483647
#define N 30001
using namespace std;

long dui[N * 2 + 1], top;
void add(long x) {
	long now;
	dui[++top] = x;
	for (now = top; dui[now / 2] > dui[now] && now > 1; now /= 2)
		swap(dui[now], dui[now / 2]);
}
long qu() {
	long ans = dui[1],now;
	bool t = false;
	dui[1] = INF;
	now = 1;
	while (!t) {
		t = true;
		if (now * 2 == top || dui[now * 2] < dui[now * 2 + 1]) {
			if (dui[now] > dui[now * 2]) {
				swap(dui[now], dui[now * 2]);
				now = now * 2;
				t = false;
			}
		} else if (now * 2 + 1 <= top)
			if (dui[now] > dui[now * 2 + 1]) {
				swap(dui[now], dui[now * 2 + 1]);
				now = now * 2 + 1;
				t = false;
			}
	}
	return ans;
}
int main() {
	long n, i, j, k, q, m;
	long ans = 0;
	scanf("%ld %ld", &n, &k);
	for (i = 1; i <= n; i++) {
		scanf("%ld", &q);
		add(q);
	}
	m = n % (k - 1);
	if (m == 0) m = k - 1;
	if (m > 1) {
		q = 0;
		for (i = 1; i <= m; i++)
			q += qu();
		ans += q;
		add(q);
	}
	while (dui[2] != INF || dui[3] != INF) {
		q = 0;
		for (i = 1; i <= k && dui[1] != INF; i++)
			q += qu();
		ans += q;
		add(q);
	}
	printf("%ld\n", ans);
	return 0;
}