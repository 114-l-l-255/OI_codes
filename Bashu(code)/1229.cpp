#include <cstdio>
using namespace std;
const int MAXN = 100001;
long long a[MAXN];
long long sum[318], tag[318];
int l[MAXN], r[MAXN], pos[MAXN];
double f(double x, int n) { return x * x - n; }
double f_(double x) { return 2 * x; }
double qksqrt(int n) {
	double tmp1 = n / 2 + 1;
	for (int i = 0; i < 30; i++) {
		tmp1 = tmp1 - f(tmp1, n) / f_(tmp1);
	}
	return tmp1 < 0 ? -tmp1 : tmp1;
}
int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	int sqrtn = qksqrt(n);
	int t = sqrtn;
	for (int i = 1; i <= t; i++) {
		l[i] = r[i - 1] + 1;
		r[i] = l[i] + sqrtn - 1;
	}
	if (r[t] < n) t++, l[t] = r[t - 1] + 1, r[t] = n;
	for (int i = 1; i <= t; i++) {
		for (int j = l[i]; j <= r[i]; j++) {
			sum[i] += a[j];
			pos[j] = i;
		}
	}
	for (int i = 0; i < q; i++) {
		char op;
		int aa, bb;
		long long cc;
		while ((op = getchar()) != 'C' && op != 'Q');
		scanf("%d %d", &aa, &bb);
		if (op == 'Q') {
			int p = pos[aa], q = pos[bb];
			long long ans = 0;
			for (int i = p + 1; i < q; i++)
				ans += sum[i] + tag[i] * (r[i] - l[i] + 1);
			if (p == q) {
				for (int i = aa; i <= bb; i++) ans += a[i];
				ans += tag[p] * (bb - aa + 1);
			}
			else {
				for (int i = aa; i <= r[p]; i++) ans += a[i];
				ans += tag[p] * (r[p] - aa + 1);
				for (int i = l[q]; i <= bb; i++) ans += a[i];
				ans += tag[q] * (bb - l[q] + 1);
			}
			printf("%lld\n", ans);
		}
		if (op == 'C') {
			scanf("%lld", &cc);
			int p = pos[aa], q = pos[bb];
			for (int i = p + 1; i < q; i++) tag[i] += cc;
			if (p == q) {
				for (int i = aa; i <= bb; i++) a[i] += cc;
				sum[p] += (bb - aa + 1) * cc;
			}
			else {
				for (int i = aa; i <= r[p]; i++) a[i] += cc;
				sum[p] += (r[p] - aa + 1) * cc;
				for (int i = l[q]; i <= bb; i++) a[i] += cc;
				sum[q] += (bb - l[q] + 1) * cc;
			}
		}
	}
	return 0;
}