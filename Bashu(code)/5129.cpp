#include <cstdio>
#include <algorithm>
#include <cstring>
#pragma GCC optimize(2, 3, "inline", "Ofast")
#define int long long
using namespace std;
const int MAXN = 401;
const int MAXK = 1000001;
int pre[MAXN][MAXN];
int a[MAXN][MAXN];
int TONG[MAXK], mod[MAXN];
int read() {
	int aaaa = 0;
	char ch;
	do {
		ch = getchar();
	} while (ch < '0');
	while (ch >= '0') {
		aaaa = aaaa * 10 + ch - '0';
		ch = getchar();
	}
	return aaaa;
}
signed main() {
	int n, m, k_;
	n = read(), m = read(), k_ = read();
	for (register int i = 1; i <= n; ++i) {
		for (register int j = 1; j <= m; j++) {
			a[i][j] = read();
			pre[i][j] = pre[i - 1][j] + a[i][j];
			pre[i][j]>=k_?pre[i][j]-=k_:0;
		}
	}
	int ans = 0;
	for (register int i = 1; i <= n; ++i) {
		for (register int j = 1; j <= i; ++j) {
//			memset(TONG, 0, sizeof TONG);
			int sum = 0; TONG[0] = 1;
			for (register int k = 1; k <= m; ++k) {
				sum = (sum+pre[i][k]-pre[j - 1][k]);
				if (sum < 0) sum += k_;
				if (sum >= k_) sum -= k_;
				ans += TONG[sum];
				++TONG[sum];
				mod[k] = sum;
			}
			for (register int k = m; k >= 1; k--) TONG[mod[k]] = 0;
		}
	}
	printf("%lld", ans);
	return 0;
}