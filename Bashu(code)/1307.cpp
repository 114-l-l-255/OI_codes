#include <cstdio>
#include <algorithm>
using namespace std;
long long qkpow(long long a, long long b, long long p) {
	a %= p;
	a += p;
	a %= p;
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ((ans * a) % p + p) % p;
		a = ((a * a) % p + p) % p;
		b >>= 1;
	}
	return ans;
}
int main() {
	long long a, n, p;
	scanf("%lld %lld %lld", &a, &n, &p);
	printf("%lld", (qkpow(a, n, p) % p + p) % p);
	return 0;
}