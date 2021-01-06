#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long
#define mod 9901
using namespace std;
void exgcd(LL a, LL b, LL &x, LL &y, LL &d) {
	if (b == 0) {
		x = 1, y = 0, d = a;
		return;
	}
	exgcd(b, a % b, y, x, d);
	y -= a / b * x;
}
LL Inv(LL a) {
	LL x, y, d;
	exgcd(a, mod, x, y, d);
	if (a == mod)
	if (d != 1) return -1;
	return (x % mod + mod) % mod;
}
LL pow2(LL x, LL y) {
	LL ans = 1;
	while (y) {
		if (y & 1) {
			ans = (ans * x) % mod;
		}
		y >>= 1;
		x = (x * x) % mod;
	}
	return ans;
}
LL work(LL x, LL y) {
	if (x == 1) return (y + 1) % mod;
	if (x == 0) return 1;
	LL ret = (pow2(x, y + 1) - 1) * Inv(x - 1) % mod;
	return ret;
}
int a[100], b[100];
int main(){
	LL A, B;
	scanf("%lld %lld", &A, &B);
	int top = 0;
	memset(b, 0, sizeof(b));
	for (int i = 2; i * i <= A; i++) {
		if (A % i == 0) a[++top] = i;
		while (A % i == 0) A /= i, b[top]++;
	}
	if (A != 1) a[++top] = A, b[top]++, A = 1;
	LL ans = 1;
	for (int i = 1; i <= top; i++) {
		LL sum = work(a[i] % mod, B * b[i]);
		ans *= sum;
		ans %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}