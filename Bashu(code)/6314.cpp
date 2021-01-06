#include <cstdio>
#include <algorithm>
using namespace std;
long long Fac[10000001];
void exgcd(long long a, long long b, long long &d, long long &x, long long &y) {
	if (b) {
		exgcd(b, a % b, d, y, x);
		y -= a / b * x;
	}
	else {
		d = a; x = 1; y = 0;
	}
}
long long inv(long long a, long long p) {
	long long x, y, d;
	exgcd(a, p, d, x, y);
	if (d == 1) return (x % p + p) % p;
	else return -1;
}
long long Com(long long n, long long m, long long p) {
	return Fac[n] * inv(Fac[m], p) % p * inv(Fac[n - m], p) % p;
}
//long long Fac(long long n, long long p) {
//	long long ans = 1;
//	while (n) {
//		ans = (ans * n) % p;
//	}
//	return ans;
//}
int main() {
	Fac[0] = 1;
	for (int i = 1; i <= 10000000; i++) {
		Fac[i] = Fac[i - 1] * i % 998244353;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		long long n, m;
		scanf("%lld %lld", &n, &m);
		long long C = Com(n, m, 998244353);
		printf("%lld\n", C * C % 998244353 * Fac[m] % 998244353);
	}
	return 0;
}