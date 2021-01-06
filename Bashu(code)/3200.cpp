#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 1000001;
const int MOD = 20090314+1;
char str[MAXN], QwQ[MAXN];
int Mp[MOD];
int hash1, hash2;
int Pow131[MAXN], Pow13331[MAXN];
int Hash() {
	return ((long long)hash1 * MOD + hash2) % MOD;
}
signed main() {
	scanf("%s", str);
	int n = strlen(str);
	Pow131[0] = Pow13331[0] = 1;
	for (int i = 1; i <= n; i++) {
		Pow131[i] = (long long)Pow131[i - 1] * 131 % MOD;
		Pow13331[i] = (long long)Pow13331[i - 1] * 13331 % MOD;
	}
	long long ans = 0;
	Mp[Hash()]++;
	for (int i = 0, j = 0; i < n; i++) {
		// QwQ = QwQ + str[i];
		if (j == 0 || QwQ[j - 1] != str[i]) {
			QwQ[j++] = str[i];
			hash1 += Pow131[j - 1] * (str[i] - 'a' + 1) % MOD;
			hash1 %= MOD;
			hash2 += Pow13331[j - 1] * (str[i] - 'a' + 1) % MOD;
			hash2 %= MOD;
		}
		else {
			j--;
			hash1 += MOD - Pow131[j] * (str[i] - 'a' + 1) % MOD;
			hash1 %= MOD;
			hash2 += MOD - Pow13331[j] * (str[i] - 'a' + 1) % MOD;
			hash2 %= MOD;
		}
		ans += Mp[Hash()];
		Mp[Hash()]++;
	}
	printf("%lld", ans);
	return 0;
}