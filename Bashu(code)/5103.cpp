#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;
const int mod = 1000003,ny2=500002;
ll n, m;
long long power(long long a, long long b) {
	long long t = b, x = 1;
	while (t) {
		if (t % 2 == 1) x = x * a % mod;
		t >>= 1;
		a = a *a % mod;
	}
	return x;
}
int main() {
	scanf("%lld %lld", &n, &m);
	if (log2(m) > n) {
		printf("1 1");
		return 0;
	}
	ll p = power(2, n), b = power(p, m), a = 1;
	for (ll i = 0; i < m; i++) {
		a = a * (p - i) % mod;
		if (!a) break;
	}
	ll yf = n;
	m--;
	for (ll i = 2; i <= m; i <<= 1) yf += m / i;
	b = b * power(ny2, yf) % mod;
	a = a * power(ny2, yf) % mod;
	printf("%lld %lld", (b - a + mod) % mod, b);
}