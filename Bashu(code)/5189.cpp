#include <cstdio>
#include <algorithm>
#define mod 100000007
using namespace std;
const int MAXN = 5000001;
bool vis[MAXN];
int primes[348514];
int tot;
void prime(int a) {
	vis[0] = vis[1] = 1;
	for (int i = 2; i <= a; i++) {
		if (vis[i] == 0) {
			primes[tot++] = i;
		}
		for (int j = 0; j < tot && i * primes[j] <= a; j++) {
			vis[i * primes[j]] = 1;
			if (i % primes[j] == 0) break;
		}
	}
}
/*
非确定性有限状态决策自动机
非确定性有限状态决策自动机
蜚皵掟腥鼬献妝薹孓畟吇棟剂
非确定性有限状态决策自动机
*/ 
long long qkpow(int a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) {
			ans = ans * a % mod;
		}
		a = (long long)a * a % mod;
		b >>= 1;
	}
	return ans;
}
int main() {
//	freopen("number.in", "r", stdin);
//	freopen("number.out", "w", stdout);
	prime(5000000);
	int n;
	scanf("%d", &n);
	long long ans = 1;
//	for (int j = 0; j < 100; j++) {
//		printf("%d\n", primes[j]);
//	}
	for (int j = 0; j < tot && primes[j] <= n; j++) {
		int nn = n;
		long long nums = 0;
		while (nn) {
			nums += nn / primes[j];
			nn /= primes[j];
		}
//		printf("%d %d\n", primes[j], nums);
		ans = ans * qkpow(primes[j], nums / 2 * 2) % mod;
	}
	printf("%lld", ans);
	return 0;
}//99.999444068173016924577745042251