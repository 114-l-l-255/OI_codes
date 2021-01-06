#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXV = 90001;
const int MAXN = 301;
const int MAXM = 100001;
int dp[MAXV];
struct buy {
	int c, v, t;
	bool operator < (const buy& sec) const {
		return t < sec.t;
	}
} b[MAXN];
struct Shop {
	int t, m, id;
	bool operator < (const Shop& sec) const {
		return this->t < sec.t;
	}
} s[MAXM];
int ans[MAXM];
int main() {
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	int n, m;
	scanf("%d %d", &n, &m);
	int limit = n * 300;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &b[i].c, &b[i].v, &b[i].t);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &s[i].t, &s[i].m);
		s[i].id = i;
	}
	sort(b + 1, b + n + 1);
	sort(s + 1, s + m + 1);
	for (int i = 1, j = 1; i <= m; i++) {
		while (b[j].t <= s[i].t && j <= n) {
			for (int i = limit; i >= b[j].v; i--) {
				dp[i] = min(dp[i], dp[i - b[j].v] + b[j].c);
			}
			for (int i = limit - 1; i >= 0; i--) {
				dp[i] = min(dp[i], dp[i + 1]);
			}
			j++;
		}
		int l = 0, r = limit, mid, t;
		while (l <= r) {
			if (dp[mid = (l + r) >> 1] <= s[i].m) {
				l = (ans[s[i].id] = mid) + 1;
			}
			else {
				r = mid - 1;
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}