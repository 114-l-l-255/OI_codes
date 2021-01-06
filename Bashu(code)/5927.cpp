#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 110;
const int MAXK = 6111;
int dp[2][MAXN][MAXK];
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    if (n == 1) {
        printf("0");
        return 0;
    }
    dp[1][1][3100] = 1;
    for (int i = 2; i <= n; i++) {
        int ii = (i & 1), ij = ((i & 1) ^ 1);
        for (int j = i == n ? 0 : 1; j <= n; j++) {
            for (int k = 100; k <= 6000; k++) {
                if (j) dp[ii][j][k] = dp[ij][j - 1][k + i];
                dp[ii][j][k] = ((long long)dp[ii][j][k] + (long long)dp[ij][j + 1][k - i] * (long long)(j + 1)) % 1000000007;
                dp[ii][j][k] = ((long long)dp[ii][j][k] + (long long)dp[ij][j][k]) % 1000000007;
                // printf("dp[%d][%d][%d] = %lld\n", i, j, k, dp[ii][j][k]);
            }
        }
    }
    long long ans = 0;
    for (int i = 3102; i <= min(3101 + k, 6000); i++) {
        ans += dp[n & 1][0][i];
        ans %= 1000000007;
    }
    printf("%lld", ans);
    return 0;
}