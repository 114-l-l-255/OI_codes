#include <cstdio>
#include <algorithm>
#define int long long
#define mod 1000000007
using namespace std;
const int MAXN = 2001;
const int MAXM = 2001;
const int MAXK = 1000001;
long long Strling[MAXN][MAXN];
long long jie[MAXK], ni[MAXK];
long long qkpow(long long a, int b) {
	long long ans = 1;
	while (b) {
		if (b & 1) {
			ans = (ans * a) % mod;
		}
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}
long long C(int n,int m){return jie[n]*ni[m]%mod*ni[n-m]%mod;}
signed main() {
	int n, m, k;
	scanf("%lld %lld %lld", &n, &m, &k);
//	Strling[1][1] = 1;
	Strling[0][0] = 1;
//	for (int i = 1; i <= n; i++) {
//		Strling[i][i] = 1;
//		Strling[i][0] = 0;
//	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			Strling[i][j] = (Strling[i - 1][j - 1] + Strling[i - 1][j] * j % mod) % mod;
		}
	}
	jie[0] = 1;
	for (int i = 1; i <= k; i++) {
		jie[i] = jie[i - 1] * i % mod;
	}
	ni[k] = qkpow(jie[k], mod - 2);
	for (int i = k - 1; ~i; i--) {
		ni[i] = ni[i + 1] * (i + 1)%mod;
	}
	long long ans = 0;
	for (int i = 1; i <= min(n, k); i++) {
		for (int j = 0; i + j <= n && i + j + j <= k; j++) {
			ans=(ans+C(k,i)%mod*C(k-i,j)%mod*C(k-i-j,j)%mod*qkpow(i,(m-2)*n)%mod*qkpow(Strling[n][i+j]*jie[i+j]%mod,2)%mod)%mod;
//			ans = (ans + jie[k] * ni[k - i] % mod * ni[i] % mod * qkpow(i, (m - 2) * n) % mod * jie[k - i] % mod * ni[k - i - j] % mod * ni[j] % mod * jie[k - i - j] % mod * ni[k - i - j - j] % mod * ni[j] % mod * qkpow(Strling[i + j][n] * jie[i + j] % mod, 2) % mod) % mod;
//			printf("%d %d %lld\n", i, j, ans);
		}
	}
	printf("%lld", ans);
	return 0;
}